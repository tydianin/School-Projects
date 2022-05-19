# This program will print a user-defined number of rows in a
# predetermined format of alternating asterisks and periods.

# Establish reused input prompts.
rowsPrompt = "How many rows do you want to print? "

# Priming read for number of rows.
rows = int(input(rowsPrompt))

# Data validation for number of rows.
while rows < 0:
    print("Unfortunately, this program is not interested in displaying in reverse.")
    print("Please provide a positive number.")
    rows = int(input(rowsPrompt))

# Display the weird programmer's triangle.
for r in range(rows):
    while r >= 0:
        print('*', end='')
        r -= 1
        if r >= 0:
            print('.', end='')
        r -= 1
    print()
