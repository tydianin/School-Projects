"""
This program will return class information to a user when provided a course number.
The class information provided will be the 1. Room number, 2. Instructor, and 3. Meeting time.
Presumably this program will later be used integrated in database queries or the like.
"""

# The brains. The brawns. The main.
def main():
    
    # Establish the dictionaries.
    room = {'CS101':'3004',
            'CS102':'4501',
            'CS103':'6755',
            'NT110':'1244',
            'CM241':'1411'}
            
    inst = {'CS101':'Haynes',
            'CS102':'Alvarado',
            'CS103':'Rich',
            'NT110':'Burke',
            'CM241':'Lee'}
            
    time = {'CS101':'8:00 a.m.',
            'CS102':'9:00 a.m.',
            'CS103':'10:00 a.m.',
            'NT110':'11:00 a.m.',
            'CM241':'1:00 p.m.'}
    
    # Obtain user search.
    search = prompt()
    search = attempt(search, room)

    # Create our output data.
    r = room[search]
    i = inst[search]
    t = time[search]
    
    # Display the information to the user.
    print()
    print("Course: \t", search)
    print("Room Number: \t", r)
    print("Instructor: \t", i)
    print("Meeting Time: \t", t)

# Request the input for searching.
def prompt():

    # Get the input.
    print("What course would you like to look up?")
    print("Please use the form 'AA###'. Ex: CS101")
    print()
    search = input("Course: ")
    search = search.upper()
    
    # Check the input.
    flag = checker(search)
    while flag == False:
        print()
        print("Please use the form 'AA###'. Ex: CS101")
        print()
        search = input("Course: ")
        search = search.upper()
        flag = checker(search)
    
    return search

# Check to make sure search input is valid format.
def checker(search):

    # Set the expectations.
    alpha, numer = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', '1234567890'
    courseFormat = [alpha, alpha, numer, numer, numer]
    
    # Test the input.
    if len(search) != len(courseFormat):
        return False
    
    for test in range(len(search)):
        if search[test] not in courseFormat[test]:
            return False
    
    return True
    
    while search not in room:
        print()
        print("This record does not exist in the database.")
        check = input("Would you like to try a different search? Y/N: ")
        print()
        search = checkCheck(check)

    return search

# Check to see if user wants to try again.
def checkCheck(check):

    # Check if user put in Y or N.
    while not (check.upper() == 'Y' or check.upper() == 'N'):
        print()
        print("Please use either the Y or N key.")
        check = input("Would you like to try a different search? Y/N: ")
        print()

    # lol byeeeee
    if check.upper() == 'N':
        print()
        exit('User exited the program.')
    
    # Run it again
    search = prompt()
    return search

main()
