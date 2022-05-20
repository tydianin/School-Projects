// taxiCabAgain.cpp
// Weston Gibson, CISP 360
// 23 November 2021

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Data file names.
const string STRING_FILE = "CityNames.dat";
const string DOUBLE_FILE = "CityTaxiRates.dat";

// Number of rate lines per city and base costs.
const int RLPC = 9;
const double FLAG_DROP = 5.70;
const double PER_MINUTE = 0.70;

// Constant rate specification.
const int STANDARD = 0;
const int WEEKEND = 1;
const int FLAT_RATE = 2;
const int MAX_FLAT_TIME = 3;
const int MAX_FLAT_MILES = 4;
const int MAX_FLAT_IDLE = 5;
const int DISCOUNT_DAY = 6;
const int DISCOUNT_TIME = 7;
const int DISCOUNT_P = 8;

// Final estimate display
const string HEADER1 = "Estimated Taxi Cost";
const string HEADER2 = "--------------------------------";
const string HEADER3 = "Flag Drop                 ";
const string HEADER4 = "Distance:                 ";
const string HEADER5 = "Waiting:                  ";
const string HEADER6 = "Total                    $";
const string HEADER7 = "Flat Rate                 ";
const string HEADER8 = "Discount                  ";

// Constant day enumeration
enum class Day : int {
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  SUNDAY
};
const int DAYS = 7;

// Constant time enumeration
enum class Time : int { EARLY_MORNING, MORNING, LUNCH, AFTERNOON, EVENING };
const int TIMES = 5;

// Prototypes
void ReadFiles(string f, vector<string>& vStr, vector<int>& vInt);
void SortVectors(vector<string>& vStr, vector<int>& vInt);
vector<double> GetData(string f, int i, int n);
int DisplayAMenu(vector<string>& v1);
void CalculateReceipt(vector<double> vDbl);

template <typename T>
void Swap(T& a, T& b);

void FileNotFound(string f);
void FileCorrupted(string f);
void ClearScreen();
void ExitProgram();

int main() {
  vector<string> vStr;
  vector<int> vInt;
  vector<double> vDbl;

  int selection = 0, exitApp = vStr.size() + 1;

  ReadFiles(STRING_FILE, vStr, vInt);
  SortVectors(vStr, vInt);
  selection = DisplayAMenu(vStr);

  while (selection != exitApp) {
    vDbl = GetData(DOUBLE_FILE, vInt[selection - 1], RLPC);

    if (!vDbl.empty())
      CalculateReceipt(vDbl);
    else {
      ClearScreen();
      cout << "Error: Rate data not found for city: " << vStr[selection - 1]
           << endl;
      selection = DisplayAMenu(vStr);
    }
  }
}

void ReadFiles(string f, vector<string>& vStr, vector<int>& vInt) {
  string l;
  int c = 0;
  ifstream s(f);

  if (!s.is_open())
    FileNotFound(f);

  cout << endl << "Importing file contents..." << endl;

  while (getline(s, l)) {
    vStr.push_back(l);
    vInt.push_back(c++);
  }

  if (!s.eof()) {
    s.close();
    FileCorrupted(f);
  }

  s.close();
}

void SortVectors(vector<string>& vStr, vector<int>& vInt) {
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

int DisplayAMenu(vector<string>& vStr) {
  int a = 0, n = vStr.size() + 1;

  do {
    ClearScreen();

    for (int i = 0; i < n - 1; ++i)
      cout << i + 1 << ". " << vStr[i] << endl;
    cout << n << ". Exit Application" << endl << endl;

    cout << "Please enter a menu choice between 1 and " << n + 1 << ": ";
    cin >> a;

  } while (cin.fail() || (a < 1) || (a > n + 1));

  ClearScreen();
  return a;
}

vector<double> GetData(string f, int p, int n) {
  string l;
  ifstream s(f);
  int c = 0;

  vector<double> vDbl;

  if (!s.is_open())
    FileNotFound(f);

  cout << endl << "Importing file contents..." << endl;

  s.seekg(0);
  for (int i = 0; i < p; ++i)
    s.ignore();

  while (getline(s, l) && c != n) {
    vDbl.push_back(stod(l));
    ++c;
  }

  s.close();

  return vDbl;
}

template <typename T>
void Swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

void FileNotFound(string f) {
  cout << endl
       << endl
       << "Error: File not found." << endl
       << "File may be missing." << endl
       << "File provided: " << f << endl;
  ExitProgram();
}

void FileCorrupted(string f) {
  cout << endl
       << endl
       << "Error: End of file not found." << endl
       << "File may be corrupted." << endl
       << "File provided: " << f << endl;
  ExitProgram();
}

void ClearScreen() {
  cout << "\033[2J\033[1;1H";
}

void ExitProgram() {
  cout << "Press enter to close...";
  cin.ignore();
  cin.get();
  exit(0);
}

void CalculateReceipt(vector<double> vDbl) {
  bool flat = false;

  int day = 0, time = 0, day1 = static_cast<int>(Day::MONDAY),
      day7 = static_cast<int>(Day::SUNDAY);

  double
      // input
      miles = 0.0,
      minutes = 0.0,

      // calculations
      baseRate = FLAG_DROP, milesRate = vDbl[STANDARD], milesCost = 0.0,
      minutesCost = 0.0, totalCost = 0.0, discountRate = vDbl[DISCOUNT_P],
      discount = 0.0;

  vector<string> vDay = {"Monday", "Tuesday",  "Wednesday", "Thursday",
                         "Friday", "Saturday", "Sunday"};

  vector<string> vTime = {"12:00 AM - 07:59 AM", "08:00 AM - 11:29 AM",
                          "11:30 AM - 12:59 PM", "01:00 PM - 09:59 PM",
                          "10:00 PM - 11:59 AM"};

  ClearScreen();
  DisplayAMenu(vDay);
  cin >> day;

  if ((day >= day1) && (day <= day7)) {
    ClearScreen();
    DisplayAMenu(vTime);
    cin >> time;

    // Check if a valid time was selected
    if ((time >= TIME1) && (timeChoice <= TIME5)) {
      cout << "How many miles are your traveling ? : ";
      cin >> milesDriven;

      // Check if Mon through Fri
      if ((dayChoice >= DAY1) && (dayChoice <= DAY5)) {
        // Check for Flat Rate time
        if (timeChoice == vDbl[FLAT_RATE_TIME]) {
          currentRate = vDbl[FLAT_RATE_COST];
          flat = true;

          if (milesDriven > vDbl[FLAT_RATE_MAX_FREE_MILES]) {
            milesDriven = (milesDriven - vDbl[FLAT_RATE_MAX_FREE_MILES]);
          } else {
            milesDriven = 0;
          }
        } else {
          // Not Flat Rate, check for Discount Day and Time
          if ((dayChoice == vDbl[DISCOUNT_DAY]) &&
              (timeChoice == vDbl[DISCOUNT_TIME])) {
            discountRate = vDbl[DISCOUNT_AMOUNT];
          }
        }
      } else {
        // Must be a weekend
        mileRate = vDbl[WEEKEND_RATE];
      }

      if (!isFlatRate) {
        cout << "How many minutes will you stop for?: ";
        cin >> waitMinutes;
      }

      //
      // Calculate Taxi Fare
      distanceCost = milesDriven * mileRate;
      waitingCost = waitMinutes * PER_MINUTE_COST;
      totalCost = distanceCost + waitingCost + currentRate;
      discount = -1 * (totalCost * discountRate);
      totalCost = totalCost + discount;
      //
      // Set output formatting
      cout << setprecision(2);
      cout << fixed;
      cout << showpoint;
      //
      cout << "\n\n\n";
      cout << HEADER1 << endl;
      cout << HEADER2 << endl;

      if (!isFlatRate) {
        cout << HEADER3 << setw(6) << currentRate << endl;
      } else {
        cout << HEADER7 << setw(6) << currentRate << endl;
      }

      cout << HEADER4 << setw(6) << distanceCost << endl;
      cout << "  (" << milesDriven << " Mi @ $" << vDbl[STANDARD_PER_MILE_COST]
           << ")" << endl;

      if (!isFlatRate) {
        cout << HEADER5 << setw(6) << waitingCost << endl;
        cout << "  (" << waitMinutes << " Min @ $" << PER_MINUTE_COST << ")"
             << endl;
      }

      if (discountRate > 0) {
        cout << HEADER8 << setw(6) << discount << endl;
      }

      cout << HEADER2 << endl;
      cout << HEADER6 << setw(6) << totalCost << endl;
    } else {
      cout << "Invalid menu choice, please select a number from " << TIME1
           << " to " << TIME5 << endl;
    }
  } else {
    cout << "Invalid menu choice, please select a number from " << DAY1
         << " to " << DAY7 << endl;
  }
}