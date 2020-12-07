def main():

    # This infinite loop prompts user for a valid number which comprises of only digits 0-9.
    while True:
        number = input("Number: ")

        # If the user input contains a char then reprompt else break from loop.
        if number.isdigit():
            break

    # Size of the input string.
    n = len(number)

    # Printing "INVALID" for all credit card number which do not satisfy the given size constraints.
    if n < 13 or n > 16:
        print("INVALID")

    # Checking for AMEX card.
    elif n == 15:
        if number[0] == '3' and (number[1] == '4' or number[1] == '7'):
            v = luhn(number)

            if v == 1:
                print("AMEX")
            else:
                print("INVALID")

        else:
            print("INVALID")

    elif n == 16:
        # Checking for MASTERCARD.
        if number[0] == '5' and int(number[1]) in range(1, 6, 1):
            v = luhn(number)
            if v == 1:
                print("MASTERCARD")
            else:
                print("INVALID")

        # Checking for VISA card with 16 digit number.
        elif number[0] == '4':
            v = luhn(number)

            if v == 1:
                print("VISA")
            else:
                print("INVALID")

        else:
            print("INVALID")

    # Checking for VISA card with 13 digit number.
    elif n == 13:
        if number[0] == '4':
            v = luhn(number)

            if v == 1:
                print("VISA")
            else:
                print("INVALID")

        else:
            print("INVALID")


# Function to implement Luhn's Algorithm on a credit card number which passes all other checks.
def luhn(number):
    n = len(number)
    sum = 0
    even = []
    odd = []

    # Converting every other char of credit card number starting from last second into int and storing it into "even" list.
    for i in range(n - 2, -1, -2):
        even.append(int(number[i]))

    # Converting every other char of credit card number starting from last into int and storing it into "odd" list.
    for i in range(n - 1, -1, -2):
        odd.append(int(number[i]))

    # For odd no. of digits in creadit card number making even list same size as odd list.
    if len(even) < len(odd):
        even.append(0)

    for i in range(len(odd)):
        # Multiplying every other number by 2 starting from last second.
        even[i] *= 2

        # Adding the digits of doubled numbers as well as adding remaining numbers.
        sum += even[i] // 10 + even[i] % 10 + odd[i]

    if sum % 10 == 0:
        return 1
    else:
        return 0


# Calling "main" function first
main()
