// taxiCabRedux.cpp
// Weston Gibson, CISP 360
// 2 November 2021

#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// File names for the provided files.
const string STRINGFILE = "CityNames.dat";
const string DOUBLEFILE = "CityTaxiRates.dat";

// Number of rate lines per city and base costs.
const int RLPC = 9;
const double FLAG_DROP = 5.70;
const double PER_MINUTE = 0.70;

// Menu titles.
const string TITLES[] = {
    "City Selection Menu", "************************************************",
    "Taxi Cab Rates",      "Estimated Taxi Cost",
    "Days Available",      "Times Available"};

// City output structure.
const string HEADERS_CITY[] = {
    "City Name..................: ", "Standard Mile Cost.........: ",
    "Weekend Rate...............: ", "Flat Rate Cost.............: ",
    "Flat Rate Time.............: ", "Flat Rate Max Free Miles...: ",
    "Flat Rate Stop Time Allowed: ", "Discount Day...............: ",
    "Discount Time..............: ", "Discount Amount............: "};

// Final output structure.
const string HEADERS_ESTIMATE[] = {
    "Flag Drop                  : ", "Distance:                  : ",
    "Waiting:                   : ", "Discount                     ",
    "Total                       $",
};

// Days of the Week.
const int DAY = 7;
const string DAYS[] = {
    "Monday", "Tuesday",  "Wednesday", "Thursday",
    "Friday", "Saturday", "Sunday",
};

// Times of the Day.
const int TIME = 5;
const string TIMES[] = {
    "12:00 AM - 07:59 AM", "08:00 AM - 11:29 AM", "11:30 AM - 12:59 PM",
    "01:00 PM - 09:59 PM", "10:00 PM - 11:59 PM",
};

// Function prototypes.
void ReadCityData(string f, vector<string>& vStr, vector<int>& vInt);
void SortCityNames(vector<string>& vStr, vector<int>& vInt);
int DisplayCityMenu(vector<string> vStr, int a);
vector<double> GetCityData(string f, int i, int n);
vector<string> CityDataDisplay(vector<string> vStr, vector<double> vDbl, int a);
void GetEstimateInput(vector<string> vStr,
                      vector<double> vDbl,
                      vector<string>& v1,
                      int& a,
                      int& b,
                      double& c,
                      double& d);
void GetFinalEstimate(vector<string> vStr,
                      vector<double> vDbl,
                      int a,
                      int b,
                      double c,
                      double d);

template <typename T>
void Swap(T* a, T* b);

void FileNotFound(string f);
void FileCorrupted(string f);
void ClearScreen();
void ExitProgram();

// main
int main() {
  int city = 0, day = 0, time = 0;

  double miles = 0.00, minutes = 0.00;

  cout << fixed;
  cout.precision(2);

  string cont;

  vector<string> cityNames;
  vector<int> filePositions;
  vector<double> cityData;
  vector<string> cityDataDisplay;
  vector<string> estimateInput;

  // ReadCityData
  ReadCityData(STRINGFILE, cityNames, filePositions);

  // SortCityNames
  SortCityNames(cityNames, filePositions);

  // DisplayCityMenu, GetCityData until !cityData.empty()
  while (cityData.empty()) {
    city = 0;
    city = DisplayCityMenu(cityNames, city);

    if (city == cityNames.size() + 1)
      ExitProgram();
    else
      cityData = GetCityData(DOUBLEFILE, filePositions[city] * RLPC, RLPC);

    if (cityData.empty())
      ClearScreen();
    cout << endl
         << "Error: Rate data not found for city: " << cityNames[city] << endl;
  }

  // CityDataDisplay
  cityDataDisplay = CityDataDisplay(cityNames, cityData, city);

  // GetEstimateInput
  estimateInput.push_back("City Selected: " + cityNames[city]);
  GetEstimateInput(cityDataDisplay, cityData, estimateInput, day, time, miles,
                   minutes);

  // GetFinalEstimate
  GetFinalEstimate(estimateInput, cityData, day, time, miles, minutes);

  return (0);
}

// ReadCityData
void ReadCityData(string file, vector<string>& vStr, vector<int>& vInt) {
  string l;
  int c = 0;
  ifstream f(file);

  if (!f.is_open())
    FileNotFound(file);

  cout << endl << "Importing file contents..." << endl;

  while (getline(f, l)) {
    vStr.push_back(l);
    vInt.push_back(c++);
  }

  if (!f.eof()) {
    f.close();
    FileCorrupted(file);
  }

  f.close();
}

// SortCityNames
void SortCityNames(vector<string>& vStr, vector<int>& vInt) {
  int n = vStr.size() - 1;

  bool s = true;

  cout << "Preparing file contents for processing..." << endl;

  while (s) {
    s = false;
    for (int i = 0; i < n; ++i)
      if (vStr[i] > vStr[i + 1]) {
        Swap(&vStr[i], &vStr[i + 1]);
        Swap(&vInt[i], &vInt[i + 1]);
        s = true;
      }
  }
}

// DisplayCityMenu
int DisplayCityMenu(vector<string> vStr, int a) {
  int n = vStr.size() + 1, c = 0;

  while (a < 1 || a > n || cin.fail()) {
    cout << endl << TITLES[0] << endl << TITLES[1] << endl;

    c = 0;
    for (auto i : vStr)
      cout << ++c << ") " << i << endl;

    cout << ++c << ") Exit Application" << endl << endl;
    cout << "Please select a menu choice between 1 and " << vStr.size() + 1
         << ": ";
    cin >> a;
  }

  return (a - 1);
}

// GetCityData
vector<double> GetCityData(string file, int i, int n) {
  string l;
  int c = 0;
  ifstream f(file);

  vector<double> v1;

  if (!f.is_open())
    FileNotFound(file);

  cout << endl << "Importing file contents..." << endl;

  f.seekg(0);
  for (int j = 0; j < i; ++j)
    f.ignore(numeric_limits<streamsize>::max(), '\n');

  while (getline(f, l) && c != n) {
    v1.push_back(stod(l));
    ++c;
  }

  f.close();

  return v1;
}

// CityDataDisplay
vector<string> CityDataDisplay(vector<string> vStr,
                               vector<double> vDbl,
                               int a) {
  vector<string> v1((3 + RLPC), "");
  int c = 0, n = 0;

  ClearScreen();
  v1[n++] = TITLES[2];
  v1[n++] = TITLES[1];
  for (auto i : HEADERS_CITY) {
    v1[n] = i;
    switch (c) {
      case 0:
        v1[n] = v1[n] + vStr[a];
        break;
      case 4:
        v1[n] = v1[n] + TIMES[int(vDbl[c - 1])];
        break;
      case 5:
        v1[n] = v1[n] + to_string(vDbl[c - 1]) + " Miles";
        break;
      case 6:
        if (vDbl[c - 1] == 0.00)
          v1[n] = v1[n] + "No Stopping";
        else
          v1[n] = v1[n] + to_string(vDbl[c - 1]) + " Minutes";
        break;
      case 7:
        v1[n] = v1[n] + DAYS[int(vDbl[c - 1]) - 1];
        break;
      case 8:
        v1[n] = v1[n] + TIMES[int(vDbl[c - 1]) - 1];
        break;
      default:
        v1[n] = v1[n] + "$" + to_string(vDbl[c - 1]) + "/mi";
        break;
    }
    n++;
    c++;
  }

  return v1;
}

// GetEstimateInput
void GetEstimateInput(vector<string> vStr,
                      vector<double> vDbl,
                      vector<string>& v1,
                      int& a,
                      int& b,
                      double& c,
                      double& d) {
  int n = 1;

  cout.precision(2);
  cout << fixed;

  while (a < 1 || a > DAY || cin.fail()) {
    ClearScreen();
    for (auto i : vStr)
      cout << i << endl;
    cout << endl;

    cout << TITLES[4] << endl << TITLES[1] << endl;
    n = 1;
    for (auto i : DAYS)
      cout << n++ << ") " << i << endl;
    cout << "Please select a menu choice between 1 and " << TIME << ": ";
    cin >> a;
  }
  a -= 1;
  v1.push_back("Day Selected: " + DAYS[a]);

  while (b < 1 || b > TIME || cin.fail()) {
    ClearScreen();
    for (auto i : vStr)
      cout << i << endl;
    cout << endl;
    for (auto i : v1)
      cout << i << endl;
    cout << endl;

    cout << TITLES[5] << endl << TITLES[1] << endl;
    n = 1;
    for (auto i : TIMES)
      cout << n++ << ") " << i << endl;
    cout << "Please select a menu choice between 1 and " << TIME << ": ";
    cin >> b;
  }
  b -= 1;
  v1.push_back("Time Selected: " + TIMES[b]);

  while (c < 0.01 || cin.fail()) {
    ClearScreen();
    for (auto i : vStr)
      cout << i << endl;
    cout << endl;
    for (auto i : v1)
      cout << i << endl;
    cout << endl;

    cout << "How many miles will you be traveling?" << endl;
    cout << "Please enter a number rounded to the nearest hundredth: ";
    cin >> c;
  }
  v1.push_back("Miles: " + to_string(c));

  if (vDbl[5] != 0.00) {
    while (d < 0.01 || d > vDbl[5] || cin.fail()) {
      ClearScreen();
      for (auto i : vStr)
        cout << i << endl;
      cout << endl;
      for (auto i : v1)
        cout << i << endl;
      cout << endl;

      cout << "How many minutes will our driver need to wait?" << endl;
      cout << "Waiting time is limited to " << vDbl[5] << " minutes." << endl;
      cout << "Please enter a number rounded to the nearest hundredth: ";
      cin >> d;
    }
    v1.push_back("Minutes: " + to_string(d));
  } else
    v1.push_back("No Stopping");
}

// GetFinalEstimate
void GetFinalEstimate(vector<string> vStr,
                      vector<double> cityData,
                      int day,
                      int time,
                      double miles,
                      double minutes) {
  double rate = cityData[0], discount = cityData[8],

         distance = 0.00, waiting = PER_MINUTE * minutes, total = 0.00;

  if (day == 5 || day == 6)
    rate = cityData[1];

  if (time == cityData[3])
    if (miles <= cityData[4])
      distance = cityData[2] * miles;
    else
      distance = (rate * (miles - cityData[4])) + (cityData[2] * cityData[4]);

  if (day == cityData[6] && time == cityData[7])
    discount = (cityData[8] * distance);

  total = FLAG_DROP + distance + waiting - discount;

  ClearScreen();
  for (auto i : vStr)
    cout << i << endl;
  cout << TITLES[1] << endl << endl << TITLES[3] << endl << TITLES[1] << endl;

  cout << HEADERS_ESTIMATE[0] << setw(6) << FLAG_DROP << endl;
  cout << HEADERS_ESTIMATE[1] << setw(6) << distance << endl;
  cout << HEADERS_ESTIMATE[2] << setw(6) << waiting << endl;
  cout << HEADERS_ESTIMATE[3] << setw(6) << discount << endl;
  cout << HEADERS_ESTIMATE[4] << setw(6) << total << endl;
  ExitProgram();
}

// Swap
template <typename T>
void Swap(T* a, T* b) {
  T c = *a;
  *a = *b;
  *b = c;
}

// FileNotFound
void FileNotFound(string file) {
  cout << endl
       << endl
       << "Error: File not found." << endl
       << "File may be missing." << endl
       << "File provided: " << file << endl;
  ExitProgram();
}

// FileCorrupted
void FileCorrupted(string file) {
  cout << endl
       << endl
       << "Error: End of file not found." << endl
       << "File may be corrupted." << endl
       << "File provided: " << file << endl;
  ExitProgram();
}

// ClearScreen
void ClearScreen() {
  cout.flush();
  system("CLS");
}

// ExitProgram
void ExitProgram() {
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << endl << "Press ENTER to exit the program." << endl;
  cin.get();
  exit(0);
}