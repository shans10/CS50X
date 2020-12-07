# From opening students.db database file
from cs50 import SQL
# For commandline arguments in python
from sys import argv

# Checking if the correct no. of arguments gives if not then exit
if len(argv) < 2:
    print("Usage: python roster.py HOUSE_NAME")
    exit()

# Extracting the house name from the commanline arguments
house = argv[1]

# Opening the students.db database file
db = SQL("sqlite:///students.db")

# Storing the data of students in the given house inside a list
students = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", house)

# Iterating over each student in the students list
for student in students:

    # Storing required student details in variables for printing
    first = student["first"]
    middle = student["middle"]
    last = student["last"]
    birth = student["birth"]

    # If no middle name then print only first and last names
    if middle == None:
        print(f"{first} {last}, born {birth}")

    # If middle name exists then print first middle and then last name
    else:
        print(f"{first} {middle} {last}, born {birth}")
