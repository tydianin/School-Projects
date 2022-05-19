# This program will determine the number of miles
# traveled by a vehicle using a specified speed and time.

# Establish reused input prompts.
speedPrompt = "What is the speed of the vehicle in mph? "
timePrompt = "How many hours has the vehicle traveled? "

# Priming read for speed.
speed = int(input(speedPrompt))

# Data validation for speed.
while speed < 0:
    print("Negative speed is an illusion.")
    print("Please enter a positive value.")
    speed = int(input(speedPrompt))

# Priming read for time.
time = int(input(timePrompt))

# Data validation for time.
while time < 0:
    print("Do you have future technology?")
    print("Would you like to share with us?")
    print("(Please enter a positive value).")
    time = int(input(timePrompt))

# Create template for our table
print("Hour\t\tDistance Traveled")

# Perform calculations and prepare output.
for time in range(1, time + 1):
    distance = speed * time
    print(time, "\t\t\t", distance)
