import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get a list of user's owned stocks
    portfolios = db.execute("SELECT symbol, shares FROM portfolios WHERE user_id = :user_id ORDER BY symbol DESC",
                        user_id=session["user_id"])

    cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                    user_id=session["user_id"])

    user_balance = cash[0]["cash"]

    print(user_balance)

    # If not portfolio for the user then show only total cash
    if not portfolios:
        return render_template("index.html", flag=1, total_balance=usd(user_balance))

    # Initializing a total variable to 0 to calculate total stock value
    total = 0

    # Iterating over the portfolios dict
    for portfolio in portfolios:
        name = lookup(portfolio["symbol"])["name"]
        portfolio.update({ "name": name })
        price = lookup(portfolio["symbol"])["price"]
        portfolio.update({ "price": usd(price) })
        stock_value = price * portfolio["shares"]
        portfolio.update({ "value": usd(stock_value) })
        total = total + stock_value

    # Setting the new total balance
    total_balance = total + user_balance

    return render_template("index.html", portfolios=portfolios, total_balance=usd(total_balance), user_balance=usd(user_balance))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Getting user input from symbol column
        symbol = request.form.get("symbol")
        # Getting user input from number of shares column
        shares = int(request.form.get("shares"))

        # Ensure symbol is provided
        if not symbol:
            return apology("must provide symbol for stock", 403)

        # Retrieving the information about the share
        share = lookup(symbol)

        # Checking if share is found or not
        if not share:
            return apology("stock not found, check if symbol is correct", 403)

        # Checking if user has not given negative value for number of shares
        if shares <= 0:
            return apology("you should buy atleast 1 share", 403)

        # Getting the cash field of the user from users table
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                        user_id=session["user_id"])

        # Getting the numeric value of the cash
        total_balance = cash[0]["cash"]

        # Calculating the total value for given number of required shares
        value = share["price"] * shares

        # Checking if user has enough balance to buy required number of shares
        if total_balance < value:
            return apology("insufficient funds", 403)

        # Inserting the details of the transaction into the transaction table
        db.execute("INSERT INTO transactions (user_id, type, symbol, shares, value) VALUES (:user_id, :ttype, :symbol, :shares, :value)",
                        user_id=session["user_id"],
                        ttype="buy",
                        symbol=symbol,
                        shares=shares,
                        value=format(value, '0.2f'))

        # Calculating the new balance user has left
        new_balance = total_balance - value

        # Updating the balance left with the user into the users table
        db.execute("UPDATE users SET cash = :new_balance WHERE id = :user_id",
                        new_balance=new_balance,
                        user_id=session["user_id"])

        # Getting the portfolio of the current user for the inputted shares(if it exists)
        data = db.execute("SELECT * FROM portfolios WHERE user_id = :user_id AND symbol = :symbol",
                        user_id=session["user_id"],
                        symbol=symbol)

        # Checking if portfolio for the inputted shares already exists
        if len(data) == 1:

            # In case user already has the inputted shares then setting new value to the share count for that share
            new_shares = data[0]["shares"] + shares

            # Updating the database with the new count for inputted share
            db.execute("UPDATE portfolios SET shares = :new_shares WHERE user_id = :user_id AND symbol = :symbol",
                        new_shares=new_shares,
                        user_id=session["user_id"],
                        symbol=symbol)

        # If portfolio does not exist for the current share
        else:

            # Inserting the portfolio for inputted share into the portfolios table
            db.execute("INSERT INTO portfolios (user_id, symbol, shares) VALUES (:user_id, :symbol, :shares)",
                        user_id=session["user_id"],
                        symbol=symbol,
                        shares=shares)

        # Flash info for the user
        flash(f"Bought!")

        # Redirect user to homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Getting the list of all transactions from the transactions table
    transactions = db.execute("SELECT date, type, symbol, shares, value FROM transactions WHERE user_id = :user_id ORDER BY date DESC, time DESC",
                          user_id=session["user_id"])

    # Iterating over the transactions dict
    for transaction in transactions:
        price = float(transaction["value"]) / float(transaction["shares"])
        transaction.update({ "price": usd(price) })

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Ensure symbol is provided
        if not symbol:
            return apology("please provide symbol", 403)

        # Get quote of the input share
        quote = lookup(symbol)

        # Checking if quote is found or not
        if not quote:
            return apology("stock not found, check if symbol is correct", 403)

        # Formatting the price of stock as USD
        quote["price"] = usd(quote["price"])

        # Rendering quote.html with the price of stock
        return render_template("quote.html", symbol=symbol, price=quote["price"], flag=1)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Rendering quote.html with the form to input stock symbol
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username is given
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password is given
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password is confirmed
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 418)

        # Ensure passwords match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 418)

        # Storing username and passwords in variables
        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Checking if username already in database
        if len(rows) == 1:
            return apology("username already taken, choose something else", 403)

        # Inserting user into database
        user = db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)", username=username, password=password)

        # Remember which user has logged in
        session["user_id"] = user

        # Flash user is registered
        flash(f"Registered!")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Getting the selected value of shares and symbol
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # Checking if user has selected a symbol
        if not symbol:
            return apology("please provide symbol", 403)

        # Checking if user has input a positive integer for shares
        if shares <= 0:
            return apology("you should sell atleast 1 share", 403)

        # Getting the user's portfolio for the given stock
        portfolio = db.execute("SELECT shares FROM portfolios WHERE user_id = :user_id AND symbol = :symbol",
                            user_id=session["user_id"],
                            symbol=symbol)

        # Checking if user has enough shares to sell
        if portfolio[0]["shares"] < shares:
            return apology("you do not have enough shares")

        # Getting the current total value of the stock
        value = lookup(symbol)["price"] * shares

        # Inserting the transaction details into the transactions table
        db.execute("INSERT INTO transactions (user_id, type, symbol, shares, value) VALUES (:user_id, :ttype, :symbol, :shares, :value)",
                            user_id=session["user_id"],
                            ttype="sell",
                            symbol=symbol,
                            shares=shares,
                            value=format(value, ".2f"))

        # Getting the cash column from the users table for current balance
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                            user_id=session["user_id"])

        # Extracting the integer cash value of the user
        balance = cash[0]["cash"]

        # Setting the new balance after selling the shares
        new_balance = balance + value

        # Updating the user's balance in the users table
        db.execute("UPDATE users SET cash = :new_balance WHERE id = :user_id",
                            new_balance=new_balance,
                            user_id=session["user_id"])

        # Setting the new value for the number of shares of the given type after selling
        new_shares = portfolio[0]["shares"] - shares

        # If no shares of the symbol left then delete record from portfolio
        if new_shares == 0:
            db.execute("DELETE FROM portfolios WHERE user_id = :user_id AND symbol = :symbol",
                            user_id=session["user_id"],
                            symbol=symbol)

        # If some shares left then update the record in portfolios
        else:
            # Updating the number of shares of the type for the user in the portfolios table
            db.execute("UPDATE portfolios SET shares = :new_shares WHERE user_id = :user_id AND symbol = :symbol",
                                new_shares=new_shares,
                                user_id=session["user_id"],
                                symbol=symbol)

        # Flashing the message to indicate the transaction was successfull
        flash(f"Sold!")

        # Return the user to the homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Getting the list of symbols for the stocks owned by the user
        symbols = db.execute("SELECT symbol FROM portfolios WHERE user_id = :user_id ORDER BY symbol",
                            user_id=session["user_id"])

        # Rendering the sell form
        return render_template("sell.html", symbols=symbols)

@app.route("/pchange", methods=["GET", "POST"])
@login_required
def pchange():
    """ Change User Password """

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Getting the values from the form
        opass = request.form.get("password")
        npass = request.form.get("npassword")
        cpass = request.form.get("confirmation")

        # Checking if old password is given
        if not opass:
            return apology("please provide old password", 403)

        # Checking if new password is given
        if not npass:
            return apology("please provide new password", 403)

        # Checking if new password is confirmed
        if not cpass:
            return apology("please confirm new password", 403)

        # Getting the hash of the current password
        uhash = db.execute("SELECT hash FROM users WHERE id = :user_id",
                        user_id=session["user_id"])

        # Checking if old password matches the hash in the database
        if not check_password_hash(uhash[0]["hash"], opass):
            return apology("old password does not match the database, please check again", 403)

        # Generating new password hash
        password = generate_password_hash(npass)

        # Updating the new password in the users table
        db.execute("UPDATE users SET hash = :password WHERE id = :user_id",
                        password=password,
                        user_id=session["user_id"])

        # Flashing the password changed message
        flash(f"Password Changed Successfully!")

        # Redirecting user to the homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("pchange.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)