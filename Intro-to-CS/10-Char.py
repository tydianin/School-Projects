""" Ok, this was very last-minute. Let me know if
anything in here breaks. I tried a few new things.

This program will take a specified text file and
read the contents to determine and return the:
Number of UPPERCASE letters in the file;
Number of lowercase letters in the file;
Number of digits in the file (1,2,3);
Number of whitespace characters in the file ( )."""

# The brains. The brawns. The main.
def main():

    # Establish the file being read.
    filename = 'Activity10.txt'

    # Check that the user is reading the right file.
    filename = filecheck(filename)
    while not filename.endswith('.txt'):
        print()
        print('Please use this program with text files only.')
        filename = checkCheck()

    # Get the file.
    try:
        inFile = open(filename, 'rt')
        data = inFile.read()
    except FileNotFoundError:
        print()
        print('This file was not found. Please try again')
        filename = checkCheck()

    # Initialize.
    countUpper = 0
    countLower = 0
    countDigit = 0
    countSpace = 0
    
    # Begin the counting.
    for char in data:
        if char.isupper():
            countUpper += 1
        elif char.islower():
            countLower += 1
        elif char.isdigit():
            countDigit += 1
        elif char.isspace():
            countSpace += 1
    
    # Provide the data to the user.
    print()
    print('The file provided includes...')
    print('*****************************')
    print(format(countUpper, '>7'), 'UPPERCASE characters;')
    print(format(countLower, '>7'), 'lowercase characters;')
    print(format(countDigit, '>7'), 'numerical characters;')
    print(format(countSpace, '>7'), 'whitespace characters')

# Checking the checker.
def checkCheck():
    # Tell the user to leave of give us a new file.
    print()
    prompt = input('Would you like to exit the program? Y/N: ')

    # Why do they play me like this?
    while not (prompt.upper() == 'Y' or prompt.upper() == 'N'):
        print()
        print('Please use either the Y or N key.')
        print()
        prompt = input('Would you like to exit the program? Y/N: ')

    # lol byeeeee
    if prompt.upper() == 'Y':
        print()
        exit('User exited the program.')

    else:
        print()
        filename = input('Please enter the name and extension '\
        'of the file you would like to read: ')

    return filename

# The checker to be checked.
def filecheck(filename):
    # Prompt the user to confirm the file to be read.
    print()
    print('The file currently selected is "' + filename + '".')
    print()
    check = input('Is this the file you would like to read today? Y/N: ')

    # Prompt the user to follow directions.
    while not (check.upper() == 'Y' or check.upper() == 'N'):
        print()
        print('Please use either the Y or N key.')
        print()
        check = input('Is this the file you would like to read today? Y/N: ')

    # Ask the user if they want to leave or give us a new file.
    if check.upper() == 'N':
        filename = checkCheck()
        filecheck(filename)

    # The user may continue
    return filename
    
main()
