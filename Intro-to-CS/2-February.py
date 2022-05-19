# This program will determine if a provided year is a leap year.
# This program will also display that year's number of days in February.

# Establish the constants.
year = int(input('Please enter a year: '))
leapYear = 29
commonYear = 28
answer = commonYear

# Determine if the provided year is a leap year.
if year % 100 == 0:
    if year % 400 == 0:
        answer = leapYear
elif year % 4 == 0:
        answer = leapYear

# Display the number of days in February.
print('In', year, 'February has', answer, 'days.')
