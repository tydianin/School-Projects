// taxi.cpp
// Weston Gibson, CISP 360
// 20 September 2021

#include <iomanip>
#include <iostream>
#include <map>
#include <string>

using namespace std;

// Global constants.
const float FLAG_DROP = 5.70f;
const float PER_MILE_COST = 2.65f;
const float LUNCH_MILE_COST = 8.00f;
const float PER_MINUTE_COST = 0.70f;
const float LUNCH_MIN_MILES = 5.00f;
const float WEEKEND_MILE_COST = 3.00f;
const float DISCOUNT = 0.08f;

const int DAYS = 7;
const int TIMES = 5;

const string DAY[DAYS] = {"Monday", "Tuesday",  "Wednesday", "Thursday",
                          "Friday", "Saturday", "Sunday"};

const string TIME[TIMES] = {"12:00 AM - 07:59 AM", "08:00 AM - 11:29 AM",
                            "11:30 AM - 12:59 PM", "01:00 PM - 09:59 PM",
                            "10:00 PM - 11:59 PM"};

const string HEADER[7] = {
    "Estimated Taxi Cost",     "--------------------------------",
    "Flag Drop                 ", "Distance:                 ",
    "Waiting:                  ", "Discount:                 ",
    "Total                    $"};

// Array data validation function.
int errorCheck(int ARRAY) {
  int in = 0;
  cin >> in;

  if (in < 1 || in > ARRAY || cin.fail()) {
    cout << endl
         << "Invalid menu choice, "
         << "Please select a number from 1 to " << ARRAY << ".";
    exit(13);
  }
  return in;
}

// Rational (float) numbers check.
float rationalCheck() {
  float in = 0.00f;
  cin >> in;

  if (cin.fail()) {
    cout << endl
         << "Invalid entry.\n"
         << "Please use rational numbers only (1.23).\n";
    exit(13);
  }
  return in;
}

// Begin program.
int main() {
  // Local variables.
  int day = 0, time = 0;

  float distanceCost = 0.00f, milesDriven = 0.00f, lunchMiles = 0.00f,
        waitingCost = 0.00f, waitMinutes = 0.00f, totalCost = 0.00f,
        subtotalCost = 0.00f, discountCost = 0.00f;

  bool lunchFlag = false, lunchOverFlag = false, discountFlag = false,
       weekendFlag = false;

  // Print day of week menu and prompt user for day selection.
  cout << "Day of Week\n" << HEADER[1] << endl;
  for (int i = 0; i < DAYS; i++) {
    cout << "  " << i + 1 << " : " << DAY[i] << endl;
  }

  cout << HEADER[1] << endl
       << "What day would you like to see?\n"
       << "Please type a number from 1 to " << DAYS << endl
       << endl
       << "Day: ";
  day = errorCheck(DAYS);
  cout << endl << "You chose " << DAY[day - 1] << endl;

  // Print time of day menu and prompt user for day selection.
  cout << endl << "Time of Day\n" << HEADER[1] << endl;
  for (int i = 0; i < TIMES; i++) {
    cout << "  " << i + 1 << " : " << TIME[i] << endl;
  }

  cout << HEADER[1] << endl
       << "What time would you like to see?\n"
       << "Please type a number from 1 to " << TIMES << endl
       << endl
       << "Time: ";
  time = errorCheck(TIMES);
  cout << endl << "You chose " << TIME[time - 1] << endl;

  // Request mileage from user.
  cout << endl
       << HEADER[1] << endl
       << "How many miles do you want to\n"
       << "estimate? : ";
  milesDriven = rationalCheck();

  // Switch structure. Used to calculate distanceCost.
  switch (time) {
      // If time is option 3, and day is option 1-5:
      // Set lunchFlag to true for final output.
      // Check mileage against LUNCH_MIN and calculate using LUNCH_MILE_COST.
      // If more than LUNCH_MIN, set lunchOverFlag to true for final output.
    case 3:
      if (day < 6) {
        lunchFlag = true;
        if (milesDriven - LUNCH_MIN_MILES <= 0.00f) {
          distanceCost = milesDriven * LUNCH_MILE_COST;
        } else {
          lunchOverFlag = true;
          lunchMiles = milesDriven - LUNCH_MIN_MILES;
          distanceCost = (LUNCH_MIN_MILES * LUNCH_MILE_COST) +
                         (lunchMiles * PER_MILE_COST);
        }
      } else {
        weekendFlag = true;
        distanceCost = milesDriven * WEEKEND_MILE_COST;
      }
      break;
      // If time is option 5, and day is option 5, set discountFlag to true.
    case 5:
      if (day == 5) {
        discountFlag = true;
      }
      if (day >= 6) {
        weekendFlag = true;
        distanceCost = milesDriven * WEEKEND_MILE_COST;
      }
      break;
    default:
      if (day >= 6) {
        weekendFlag = true;
        distanceCost = milesDriven * WEEKEND_MILE_COST;
        break;
      } else {
        distanceCost = milesDriven * PER_MILE_COST;
      }
  }

  // Request waiting time if waitingFlag is set to true;
  cout << endl << HEADER[1] << endl;
  if (lunchFlag == false) {
    cout << "How many minutes would you \n"
         << "like the driver to wait ? : ";
    waitMinutes = rationalCheck();
    waitingCost = waitMinutes * PER_MINUTE_COST;
  }

  // Calculate Taxi Fare
  totalCost = FLAG_DROP + distanceCost + waitingCost;
  if (discountFlag == true) {
    subtotalCost = totalCost;
    discountCost = totalCost * DISCOUNT;
    totalCost -= discountCost;
  }

  // Set output formatting
  cout << fixed << showpoint << setprecision(2);

  // Output block
  cout << "\n\n\n"
       << HEADER[0] << endl
       << HEADER[1] << endl
       << "Day:  " << DAY[day - 1] << endl
       << "Time: " << TIME[time - 1] << endl
       << HEADER[1] << endl
       << HEADER[2] << setw(6) << FLAG_DROP << endl
       << HEADER[3] << setw(6) << distanceCost << endl;
  if (lunchFlag == true) {
    cout << "(Lunch: First " << LUNCH_MIN_MILES << " miles @ "
         << LUNCH_MILE_COST << ")\n";
    if (lunchOverFlag == true) {
      cout << "  (" << LUNCH_MIN_MILES << " Mi @ $" << LUNCH_MILE_COST << ")\n"
           << "  (" << lunchMiles << " Mi @ $" << PER_MILE_COST << ")\n";
    } else {
      cout << "  (" << milesDriven << " Mi @ $" << LUNCH_MILE_COST << ")\n";
    }
  } else {
    if (weekendFlag == true) {
      cout << "(Weekend: All miles @ " << WEEKEND_MILE_COST << ")\n"
           << "  (" << milesDriven << " Mi @ $" << WEEKEND_MILE_COST << ")\n";
    } else {
      cout << "  (" << milesDriven << " Mi @ $" << PER_MILE_COST << ")\n";
    }
    cout << HEADER[4] << setw(6) << waitingCost << endl
         << "  (" << waitMinutes << " Min @ $" << PER_MINUTE_COST << ")\n";
  }
  if (discountFlag == true) {
    cout << HEADER[5] << setw(6) << discountCost << endl
         << "  (Friday Discount!)\n"
         << "  (" << DISCOUNT * 100.00f << "% off entire ride!)\n"
         << "  ($" << subtotalCost << " @ " << DISCOUNT * 100.00f << "%)\n";
  }
  cout << HEADER[1] << endl << HEADER[6] << setw(6) << totalCost << endl;
}