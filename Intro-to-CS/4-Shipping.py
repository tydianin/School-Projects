# This program will determine the charges for shipping
# based on weight information provided by the user.

# Establish the constants and variables.
tier1 = 1.80    # weight <= 2
tier2 = 3.20    # 2 < weight <= 6
tier3 = 4.50    # 6 < weight <= 10
tier4 = 5.00    # weight > 10
weightPrompt = "Please enter the weight of the package: "
charges = 0

# Prompt the user to enter the item's weight.
weight = float(input(weightPrompt))

# Error check for invalid weight.
if weight <= 0:
    print("Please enter a weight greater than zero.")
    weight = float(input(weightPrompt))

# Perform calculation on the provided weight.
if weight > 10:
    charge = tier4
elif weight > 6:
    charge = tier3
elif weight > 2:
    charge = tier2
else:
    charge = tier1

# Print the output to the user.
print("The shipping charge for this package is $",
    format(charge * weight, ',.2f'), ".", sep='')
