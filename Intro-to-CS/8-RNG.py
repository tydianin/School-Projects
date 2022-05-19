# This program will write a prompted quantity of random numbers
# to file, then report the list of numbers, total, and quantity
# of numbers in the file.

import random

def main():

    # Get the quantity of random numbers the user wants to use.
    num = int(input("How many numbers would you like to use: "))
    
    # Assign the file name to a variable that will be used later.
    filename = 'random.txt'
    
    # Write the random numbers to the file.
    fileOut(num, filename)
    
    # Display the list, total, and quantity to the user.
    stdOut(filename)

# Function to generate and write random numbers to file.
def fileOut(num, filename):
    file = open(filename, 'w')
    
    for i in range(num):
        number = random.randint(1, 500)
        file.write(str(number)+'\n')
    
    file.close()

# Function to read and display contents, total, and count.
def stdOut(filename):
    file = open(filename, 'r')
    
    total = 0
    count = 0
    
    line = file.readline()
    print("\n--List--")
    while line != '':
        print(line, end='')
        total += int(line)
        count += 1
        line = file.readline()
    
    print("\nTotal:", total)
    print("\nCount:", count)
    
    file.close()

# Call the main function.
main()
