# This program will assist in the filing of monthly sales tax
# reports, displaying the amount county, state, and total tax
# to be remitted.

# Establish global constants.
# DO NOT CHANGE WITHOUT CHECKING LOCAL/STATE RESOURCES FIRST.
COUNTY = 0.025
STATE = 0.050

def main():

    # Get the total gross sales for the month.
    sales = get_sales()
    
    # Calculate the county, state, and total sales tax.
    county, state, total = calculate_tax(sales)
    
    # Print the county, state, and total sales tax.
    # Print formatting uses projected maximum taxes in the trillions.
    # Modify formatting if scientific notation or >=$10T
    print(
        '{:^30}\n'.format("Total Sales Entered") +
        '{:^30}\n\n'.format('${:,.2f}'.format(sales)) +
        '{:^30}\n'.format("Given Tax Rates") +
        '{:^30}\n'.format("County: " + '{:.2f}%'.format(COUNTY * 100)) +
        '{:^30}\n\n'.format("State : " + '{:.2f}%'.format(STATE * 100)) +
        "Tax\t|  " + '{:>20}\n'.format("Amount") +
        "-------------------------------\n" +
        "County\t| " + '${:.>20,.2f}\n'.format(county) +
        "State\t| " + '${:.>20,.2f}\n'.format(state) +
        "Total\t| " + '${:.>20,.2f}\n'.format(total))
    

# Data validation loop.
def data_validation(entry):
    if entry < 0:
        status = True
    else:
        status = False
    return status
    
# Obtain the total gross sales values from the user.
def get_sales():
    sales = float(input("Please enter the total gross sales for the month: "))
    
    # Validate the entry.
    while data_validation(sales):
        print("Please enter a number zero or greater.")
        sales = float(input("Please enter the total gross sales for the month: "))
    
    # Return the value.
    return sales

# Calculate the sale taxes collected.
def calculate_tax(sales):
    county = sales * COUNTY
    state = sales * STATE
    total = county + state
    return county, state, total

main()
