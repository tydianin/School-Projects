/* Assignment 8
Weston Gibson, CISP 430
13 November 2022

accepts a dynamically allocated array of test scores of non-negative numbers
  ** I will be using a vector for this to save space as I believe I **
  ** have sufficient practice using dynamically allocated arrays.   **
  ** Please see previous projects or ask me to describe dynamically **
  ** allocated arrays (vectors) if proof of this is needed.         **

sorts the test scores
  ** I will be using mergesort for simplicity.                      **

calculates the average score
displays the sorted scores and average score
*/

#include <iostream>  // cout
#include <string>    // string, stoi
#include <vector>    // vector, see notes

using namespace std;

constexpr char CLEAR_SCREEN[] = "\033[2J\033[1;1H";

int InToInt(string, bool&);
void mergeSort(vector<int>&, int, int);
void merge(vector<int>&, int, int, int);

int main() {
  string input = " ";
  int score, counter = 1;
  bool success;
  // again, just doing this for space savings.
  vector<int> scores;

  cout << CLEAR_SCREEN << "Please enter integer test scores.\n"
       << "Press enter after each test score.\n"
       << "When finished, press enter without entering data.\n\n";

  // get stuff from user
  while (input != "") {
    success = false;
    cout << "Score " << counter << ": ";
    getline(cin, input);

    if (!input.empty()) {
      score = InToInt(input, success);
    }

    if (success) {
      scores.push_back(score);
      counter++;
    }
  }

  // makes sure we don't try to work without scores
  if (scores.size() == 0) {
    cout << "\nNo scores provided. Exiting...\n\n";
    return 0;
  }

  // provide the original array
  cout << CLEAR_SCREEN << "\nScores provided:";
  counter = 1;
  for (int score : scores) {
    cout << "\nScore " << counter++ << ": " << score;
  }

  // sort the array
  mergeSort(scores, 0, (int)(scores.size() - 1));
  cout << "\n\nScores sorted:";
  counter = 1;
  for (int score : scores) {
    cout << "\nScore " << counter++ << ": " << score;
  }

  // calculate average score
  double average;
  for (int score : scores) {
    average += score;
  }
  average /= scores.size();
  cout << "\n\nAverage score: " << average << "\n" << endl;
}

int InToInt(string input, bool& success) {
  int score = -1;

  // tries to stoi, catches errors or negatives
  try {
    score = stoi(input);
    if (score >= 0) {
      success = true;
    } else {
      cout << "Please enter positive scores only.\n";
    }
  } catch (const invalid_argument& ia) {
    cout << "Please enter an integer only.\n";
  } catch (const out_of_range& oor) {
    cout << "Too many digits. Please try a smaller ratio.\n";
  } catch (...) {
    cout << "Unhandled exception. Please try again.\n";
  }

  return score;
}

void mergeSort(vector<int>& scores, int left, int right) {
  if (left == right) {
    return;
  }

  int mid = (left + right) / 2;
  mergeSort(scores, left, mid);
  mergeSort(scores, mid + 1, right);
  merge(scores, left, mid, right);
}

void merge(vector<int>& scores, int left, int mid, int right) {
  vector<int> temp;
  int i = left, j = mid + 1;

  // iterate over vector performing insertions as needed
  while (i <= mid && j <= right) {
    if (scores[i] <= scores[j]) {
      temp.push_back(scores[i++]);
    } else {
      temp.push_back(scores[j++]);
    }
  }

  // copy over rest of left partition
  while (i <= mid) {
    temp.push_back(scores[i++]);
  }

  // copy over rest of right partition
  while (j <= right) {
    temp.push_back(scores[j++]);
  }

  // copy temp back to scores
  for (int score : temp) {
    scores[left++] = score;
  }
}