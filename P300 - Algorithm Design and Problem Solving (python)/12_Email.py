"""
This program will do the following:
If provided a text file, read the file.
If not, read or create the file specified by the user.
Store the names and email addresses of the file in a dictionary, then
  provide the user various options:
    1) Look up an email address.
    2) Add a new name and email address.
    3) Change an email address.
    4) Delete a name and email address.
    5) Save and exit the address book.
"""

# Global constants for menu choices
SEARCH = 1
ADD = 2
CHANGE = 3
DELETE = 4
SAVE = 5

# The brains. The brawns. The main.
def main():

    # Establish the current file.
    # Provide user a chance to provide a different file.
    file = "in_phonebook.txt"
    file = get_file(file)

    # Get the file contents as a dictionary.
    addressBook = get_address_book(file)

    # Get user menu selection.
    choice = 0
    choice = menu()
    while choice != SAVE:

        # Execute user selection.
        print()
        name = input('Enter a first and last name. Ex: Harry Potter: ')
        if choice == SEARCH:
            print()
            print(addressBook.get(name, 'No contact exists under that name.'))
        elif choice == ADD:
            add(addressBook, name)
        elif choice == CHANGE:
            change(addressBook, name)
        elif choice == DELETE:
            delete(addressBook, name)

        # Send the user back to the menu.
        choice = menu()

    # Save the dictionary and exit.
    file = "out_phonebook.txt"
    put_file(addressBook, file)

# Check to see if the user wants to use the provided
# file or specify a new file to be used.
def get_file(file):

    # Prompt the user to confirm the file to be read.
    print()
    print('The file currently selected is "' + file + '"')
    check = input('Is this the file you would like to use? Y/N: ')

    # Prompt the user to follow directions.
    while not (check.upper() == "Y" or check.upper() == "N"):
        print()
        print('Please use either the Y or N key.')
        print()
        print('The file currently selected is "' + file + '"')
        check = input('Is this the file you would like to use? Y/N: ')

    # Ask the user if they want to leave or give us a new file.
    if check.upper() == "N":
        print()
        checkcheck = input('Would you like to use a different file? Y/N: ')
        
        # Prompt the user to follow directions.
        while not (checkcheck.upper() == "Y" or checkcheck.upper() == "N"):
            print()
            print('Please use either the Y or N key.')
            checkcheck = input('Would you like to use a different file? Y/N: ')
        
        if checkcheck.upper() == "N":
            exitcheck()
        
        print()
        print('Please provide the file you would like to use.')
        file = input('Make sure to include the file extension: ')

    # Make sure the user is working with the correct filetype.
    while not file.endswith(".txt"):
        print()
        print('Please use this program with text files only.')
        file = get_file(file)

    # The user may continue.
    return file

# Tell the user to leave or give us a new file.
def exitcheck():

    # Ask if the user wants to leave.
    print()
    print('Warning: Changes have not been saved.')
    check = input('Would you like to exit the program? Y/N: ')

    # Prompt the user to follow directions.
    while not (check.upper() == "Y" or check.upper() == "N"):
        print()
        print('Please use either the Y or N key.')
        check = input('Would you like to exit the program? Y/N: ')

    # Exit the program.
    if check.upper() == "Y":
        print()
        exit('User exited the program. Changes were not saved.')

# Attempt to read the information from the file as a dictionary.
def get_address_book(file):

    # Initialize a working dictionary
    dictionary = {}

    # Attempt to convert the file. Provide exception handling.
    try:
        with open(file) as f:
            line = f.readline()
            while line != '':
                key = line.rstrip()
                line = f.readline()
                val = line.rstrip()
                dictionary[key] = val
                line = f.readline()
    except FileNotFoundError:
        print()
        print('The file was not found. Please try again')
        file = get_file(file)
        dictionary = get_address_book(file)

    # Return the lines to the program.
    return dictionary

# User interaction menu.
def menu():

    # Print the options.
    # 'Address Book' is centered on the longest option (2).
    # The dashed line separator is also based on the longest option (2).
    print()
    print(format('Address Book', "^36"))
    print('-' * 36)
    print('1. Look up an email address.')
    print('2. Add a new name and email address.')
    print('3. Change an email address.')
    print('4. Delete a name and email address.')
    print('5. Save address book and exit.')

    # Get user interaction w/ exception handling.
    print()
    print('What would you like to do?')
    flag = True
    while flag == True:
        choice = input('Please use a whole number 1-5: ')
        try:
            choice = int(choice)
            flag = False
            if choice < 1 or choice > 5:
                flag = True
        except ValueError:
            flag = True
            print()

    return choice

# Add to the dictionary.
def add(dictionary, name):

    # Check to see if the key is in the dictionary.
    # If not, have user provide value. Check value syntax.
    if name not in dictionary:
        print()
        address = input('Enter an email: ')
        at = address.find('@')
        dot = address.rfind('.')
        while at == -1 or dot < (at + 1):
            address = input('Please enter a valid email: ')
            at = address.find('@')
            dot = address.rfind('.')
        dictionary[name] = address
        print('"' + name + '" has been added to the address book '\
            'with address "' + address + '"')
    else:
        print()
        print('That name already exists in the address book.')

# Change an entry in the dictionary.
def change(dictionary, name):

    # Check to see if the key is in the dictionary.
    # If yes, have user provide value. Check value syntax.
    if name in dictionary:
        print()
        address = input('Enter an email: ')
        at = address.find('@')
        dot = address.rfind('.')
        while at == -1 or dot < (at + 1):
            address = input('Please enter a valid email: ')
            at = address.find('@')
            dot = address.rfind('.')
        print('"' + name + '" has been changed in the address book '\
            'to address "' + address + '"')
    else:
        print()
        print('No contact exists under that name.')

# Delete an entry from the dictionary.
def delete(dictionary, name):

    # Check to see if the key is in the dictionary.
    # If yes, delete the key-value pair.
    if name in dictionary:
        print()
        print('Warning: This action cannot be undone.')
        print('You have selected "' + name +'".')
        check = input('Would you like to delete this record? Y/N: ')

    # Prompt the user to follow directions.
    while not (check.upper() == "Y" or check.upper() == "N"):
        print()
        print('Please use either the Y or N key.')
        check = input('Would you like to delete this record? Y/N: ')

    # Delete the record or exit the function.
    if check.upper() == "Y":
        del dictionary[name]
        print()
        print('"' + name + '" has been deleted from the address book.')
    else:
        print()
        print('Action canceled.')

# Save the dictionary to the output file.
def put_file(dictionary, file):
    
    get_file(file)
    with open(file, 'w') as f:
        for key, value in sorted(dictionary.items()):
            f.write('Name:    ' + key + '\n')
            f.write('Address: ' + value + '\n')
        print()
        print('Address Book saved successfully!')
        print()
        print(file)
        print()
        exit('See you next time!')

main()
