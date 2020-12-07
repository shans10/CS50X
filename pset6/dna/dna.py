# For python command line arguments.
from sys import argv
# For handling csv files.
from csv import DictReader

# Checking if the user has input the correct number of arguments.
if len(argv) < 3:
    print("Usage: python dna.py data.csv sequence.txt")

# Opening csv DNA database file in read mode.
database = open(argv[1], "r")
# Using DictReader to map the data to a dict.
datadict = DictReader(database)

# Opening the text dna sequence file in read mode.
sequence = open(argv[2], "r")
# Loading the DNA sequence to be matched into a string.
seq = sequence.read()

# Declaring empty list for storing various STRs to be checked from database file.
strs = []
# Itearating over fieldnames in datadict to get the names of all STRs skipping the first field i.e. "name".
for j in range(1, len(datadict.fieldnames)):
    strs.append(datadict.fieldnames[j])

# Empty list to store counts of consecutive repeats in longest run for each STR.
counts = []
for i in range(len(strs)):
    # Setting the pattern to be matched to the DNA sequence as ith STR.
    pattern = strs[i]
    # For each STR appending a 0 in the counts list initially.
    counts.append(0)
    # Checking if pattern occurs in "seq" string which contains the DNA sequence to be matched.
    while pattern in seq:
        # If pattern occurs we increment 1 to the count associated with the same index as "strs" list.
        counts[i] += 1
        # Adding the STR at index i to the "pattern" string to get the longest substring with consecutive repeats of STR at index i.
        # This checks each time if the new pattern exists in the string or not and incrementing count for each match.
        # In the end pattern contains the longest run of consecutive repeats of STR and we get the the no. of repeats from counts[i] for strs[i].
        pattern += strs[i]

# Iterating over each row of the DNA database dict.
for row in datadict:
    # Initializing a counter variable to 0.
    count = 0
    # Iterating over the list of counts list to get the no. of repeats for each STR in the longest run.
    for i in range(len(counts)):
        # Comparing the counts for each STR with the DNA database to see if it matches teh database.
        if int(counts[i]) == int(row[strs[i]]):
            # Counting the no. of matches for the STR to check if all STRs match or not.
            count += 1

    # If count is equal to no. of STRs in the database then there is a match.
    # Here I have used len(row - 1) because a row contains one "name" column and rest STR columns so it gives total no. of STRs to be matched.
    if count == len(row) - 1:
        print(row['name'])
        # Exiting the program after printing the name of the match.
        exit()

# If the program reaches this point then it means no match found hence printing "No match".
print("No match")

# Closing csv file containing DNA database.
database.close()

# Closing text file containing DNA sequence to be matched.
sequence.close()
