# This program will calculate and display the distance (d)
# an object free falls as a function of time in seconds (t)
# where gravity = 9.8 (g).
#
# Formula used: d = 0.5 * g * t^2

# Establish global constants.
# Only change if you are experimenting with a different gravity.
GRAVITY = 9.8

def main():

    # Get the number of seconds the object traveled.
    time = get_time()
    
    # Calculate and print the distance traveled over time.
    print("Time\t| Distance")
    print("------------------")
    for seconds in range(1, time + 1):
        distance = falling_distance(seconds)
        print(str(seconds) + '\t| {:>8.2f}'.format(distance))

# Data validation loop.
def data_validation(entry):
    if entry < 0:
        status = True
    else:
        status = False
    return status
    
# Obtain the amount of time the object traveled.
def get_time():
    time = int(input("Please enter the whole number of\n" +
        "seconds the object was in free fall: "))
    
    # Validate the entry.
    while data_validation(time):
        print("\nYou are calculating escape, not free fall.\n" +
            "Please use a different function or")
        time = int(input("please enter a number zero or greater: "))
    
    # Return the value.
    return time

# Calculate the distance the object traveled while in free fall.
def falling_distance(seconds):
    return 0.5 * GRAVITY * seconds * seconds

main()
