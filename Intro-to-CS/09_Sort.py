"""
This program will take a list of 20 numbers
provided by the user and return the lowest,
highest, and total of the list, without using
built-in functions.
"""

def main():
    
    # Initialize
    numbers = []
    
    # Request the input from the user.
    getList(numbers)
    print()
    
    # Return the lowest value of the list.
    print("The lowest value of these numbers is", findLowest(numbers))
    
    # Return the highest value of the list.
    print("The highest value of these numbers is", findHighest(numbers))
    
    # Return the total of the list.
    total = calculateTotal(numbers)
    print("The total of these numbers is", total)
    
    # Return the average of the list.
    print("The average of these numbers is", calculateAverage(numbers, total))
    
def getList(userList):
    entries = 0
    prompt = 20
    while entries < prompt:
        userList.append(int(input("Please enter a number: ")))
        entries += 1

def findLowest(userList):
    userList.sort()
    return userList[0]

def findHighest(userList):
    userList.sort()
    return userList[-1]

def calculateTotal(userList):
    total = 0
    for value in userList:
        total += value
    return total

def calculateAverage(userList, listTotal):
    return listTotal / len(userList)

main()
