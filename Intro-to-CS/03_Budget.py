# This program will take a user's provided budget and
# determine if it is over, under, or even on budget.

# Establish reused input prompts.
budgetPrompt = "Enter the allocated budget for this month: "
costPrompt = "Enter a cost. A negative value stops this loop: "

# Priming read for budget.
budget = float(input(budgetPrompt))

# Data validation for budget.
while budget < 0:
    print("Please enter a number greater than 0.")
    print("If your budget is less than 0, reconsider.")
    budget = float(input(budgetPrompt))

# Priming read for expenses.
cost = float(input(costPrompt))

# Data validation for expenses.
if cost < 0:
    liar = input("Are you sure you don't have any expenses this month? (y/n): ")
    if liar != 'y':
        cost = float(input(costPrompt))
    else:
        print("I don't believe you, but here are your numbers anyway:")
        cost = -1

# Expenses loop.
while cost >= 0:
    budget -= cost
    cost = float(input(costPrompt))

# Output intimdating messages.
if budget < 0:
    budget = abs(budget)
    print("You are $" + format(budget, ',.2f'), "over budget! Shocker.")
elif budget > 0:
    print("You are $" + format(budget, ',.2f'), "under budget! Actual shocker.")
else:
    print("You broke even... for now...")
