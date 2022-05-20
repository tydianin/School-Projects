// vector.cpp
// Weston Gibson, CISP 360
// 28 October 2021

int* DoubleArray(int* oldArray, int size) {
  // New array size.
  int newSize = size * 2;

  // Array to hold the numbers.
  int* newArray = nullptr;

  // Return a null pointer if num is zero or negative.
  if (size <= 0)
    return nullptr;

  // Allocate the array.
  newArray = new int[newSize];

  // Copy the original array, initialize the rest with zero.
  for (int i = 0; i < newSize; ++i) {
    if (i < size)
      newArray[i] = oldArray[i];
    else
      newArray[i] = 0;
  }

  // Return a pointer to the array.
  return newArray;
}