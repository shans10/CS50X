# For commandline arguments in python
from sys import argv
# For opening sqlite3 database file
from cs50 import SQL
# For reading csv file
from csv import DictReader

# Checking if the no. of arguments is correct
if len(argv) < 2:
    print("Usage: python import.py characters.csv")
    exit()

# Opening students database file
db = SQL("sqlite:///students.db")

# Extracting csv filename from commandline arguments
csv_file = argv[1]

# Opening csv file to load students into database
with open(csv_file, "r", encoding="utf-8") as characters:

    # Reading the csv file as dict
    reader = DictReader(characters)

    # Iterating over the dict
    for row in reader:

        # Loading the full name in the name variable and splitting in into separate strings
        name = row["name"].split()
        first = name[0]
        house = row["house"]
        birth = row["birth"]

        # Checking if student has a middle name or not
        if len(name) == 3:
            middle = name[1]
            last = name[2]

        # If no middle name then set middle name as None
        else:
            # Setting middle name to none so it becomes NULL in the database
            middle = None
            last = name[1]

        # Inserting the student details in the students table in the students.db database file
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                   first, middle, last, house, birth)
