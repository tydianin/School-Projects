// taxiCab.cpp
// Weston Gibson, CISP 360
// 14 October 2021

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Global constants.
const string BREAK = "******************************************\n";

// Available cities (or use file for dynamic menu).
const string CITIES[] = {"Sacramento", "San Francisco", "Portland",
                         "Orlando",    "Los Angeles",   "Exit Application"};

// Final output structure.
const string HEADERS[] = {
    "City Name..................: ", "Standard Mile Cost.........: ",
    "Weekend Rate...............: ", "Flat Rate Cost.............: ",
    "Flat Rate Time.............: ", "Flat Rate Max Free Miles...: ",
    "Flat Rate Stop Time Allowed: ", "Discount Day...............: ",
    "Discount Time..............: ", "Discount Amount............: "};

// Calculate the length of the cities array.
const int CITIES_LENGTH = *(&CITIES + 1) - CITIES;

// File names for the provided files.
const string CITYFILE = "CityNames.dat";
const string RATEFILE = "CityTaxiRates.dat";

// Function prototypes.
string DisplayCityMenu(int&);
void CityMenu();
bool IsValidCity(string, string, int&);
bool GetCityData(string,
                 int,
                 int&,
                 int&,
                 int&,
                 double&,
                 double&,
                 double&,
                 double&,
                 double&,
                 double&);

// Main.
int main() {
  // Local variables.
  string cityName;

  bool validCity = false, cityData = false;

  int selection = 0, filePosition = 0, flatRateTime = 0, discountDay = 0,
      discountTime = 0;

  double perMileStandard = 0.00, perMileWeekend = 0.00, flatRateCost = 0.00,
         flatRateFree = 0.00, flatRateStop = 0.00, discountAmount = 0.00;

  // Get city selection from user.
  cityName = DisplayCityMenu(selection);

  // Check if user elected to close the application.
  if (cityName == "Exit Application") {
    cout << endl << "User exited the application successfully.\n";
    exit(0);
  }

  // Check if city is a valid choice, get line position.
  validCity = IsValidCity(CITYFILE, cityName, filePosition);

  // City not available.
  if (validCity == false) {
    cout << endl << "Error: City not found: " << cityName << endl;
    exit(0);
  }

  // Check if city has available rate information.
  cityData =
      GetCityData(RATEFILE, filePosition, flatRateTime, discountDay,
                  discountTime, perMileStandard, perMileWeekend, flatRateCost,
                  flatRateFree, flatRateStop, discountAmount);

  // City rate information not available.
  if (cityData == false) {
    cout << endl << "Error: Rate data not found for city: " << cityName << endl;
    exit(0);
  }

  // Set precision to 2.
  cout << fixed << setprecision(2);

  // Print the output.
  cout << "\nTaxi Cab Rates\n"
       << BREAK << HEADERS[0] << cityName << endl
       << HEADERS[1] << perMileStandard << endl
       << HEADERS[2] << perMileWeekend << endl
       << HEADERS[3] << flatRateCost << endl
       << HEADERS[4] << flatRateTime << endl
       << HEADERS[5] << flatRateFree << endl
       << HEADERS[6] << flatRateStop << endl
       << HEADERS[7] << discountDay << endl
       << HEADERS[8] << discountTime << endl
       << HEADERS[9] << discountAmount << endl;

  return (0);
}

// Get city selection from user.
string DisplayCityMenu(int& selection) {
  // Print repeatable menu.
  CityMenu();

  // Get input from user.
  cout << "Please select a city: ";
  cin >> selection;

  // While loop for input validation and drop buffer.
  while (selection < 1 || selection > CITIES_LENGTH || cin.fail()) {
    cout << endl << "Please only use one of the numbers provided." << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // If input fails, print menu again.
    CityMenu();
    cout << "Please select a city: ";
    cin >> selection;
  }

  // Return user selection
  return CITIES[selection - 1];
}

// Print repeatable menu.
void CityMenu() {
  cout << "City Name Menu\n" << BREAK << endl;

  // For loop for printing the menu array elements.
  for (int i = 0; i < CITIES_LENGTH; i++) {
    cout << i + 1 << ") " << CITIES[i] << endl;
  }
  cout << endl;
}

// Check if city is a valid choice, get line position.
bool IsValidCity(string file, string city, int& position) {
  // Local variables.
  int counter = 0;
  string line;

  // Open the provided file.
  ifstream inFile(file);

  // City data file not found. Exit Application.
  if (!inFile.is_open()) {
    cout << "City data file not found.\n" << endl << "File not found: " << file;
    exit(0);
  }

  // Get lines until we find one matching menu selection.
  while (getline(inFile, line)) {
    counter++;
    if (city == line) {
      position = counter;
      inFile.close();
      return true;
    }
  }

  // Always close your files.
  inFile.close();
  return false;
}

// Check if city has available rate information (lots of arguments).
bool GetCityData(string file,
                 int position,
                 int& flatRateTime,
                 int& discountDay,
                 int& discountTime,
                 double& perMileStandard,
                 double& perMileWeekend,
                 double& flatRateCost,
                 double& flatRateFree,
                 double& flatRateStop,
                 double& discountAmount) {
  // Local Variables.
  string line;

  // Open the provided file.
  ifstream inFile(file);

  // Rate data file not found. Exit Application.
  if (!inFile.is_open()) {
    cout << "Rate data file not found.\n" << endl << "File not found: " << file;
    exit(0);
  }

  // For loop to extract data from rate file.
  for (int i = 0; i != position; i++) {
    if (inFile.good()) {
      inFile >> perMileStandard;
      inFile >> perMileWeekend;
      inFile >> flatRateCost;
      inFile >> flatRateTime;
      inFile >> flatRateFree;
      inFile >> flatRateStop;
      inFile >> discountDay;
      inFile >> discountTime;
      inFile >> discountAmount;
    } else {
      // Always close your files.
      inFile.close();
      return false;
    }
  }

  // Always close your files.
  inFile.close();
  return true;
}