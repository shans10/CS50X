# Infinite Loop
while True:
    # Taking user input
    height = input("Height: ")
    # Breaking out of loop if the input satisfies the constraints else reprompt
    if height.isdigit() and int(height) > 0 and int(height) < 9:
        break

# Outer loop for changing the line
for i in range(int(height)):
    # Printing the spaces before the hash
    for j in reversed(range(int(height) - (i + 1))):
        print(" ", end="")

    # Printing the first set of hashes
    for j in range(i + 1):
        print("#", end="")

    # Adding space between the hashes
    print("  ", end="")

    # Printing the next set of hashes
    for j in range(i + 1):
        print("#", end="")

    # Changin the line
    print()
