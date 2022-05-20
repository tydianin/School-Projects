// inventory.cpp
// Weston Gibson, CISP 360
// 4 November 2021

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Create a array to hold product type information.
const int NUM_PRODUCTS = 4;
const string PRODUCT_TYPE[NUM_PRODUCTS] = {"Stereo", "Speakers", "TV",
                                           "Receiver"};

enum ProductType { STEREO, SPEAKERS, TV, RECEIVER };

// Create a struct to hold product information.
struct Product {
  string date;
  string sn;
  ProductType type;
};

int main() {
  // Local variables.
  int type;

  // Create a vector to hold product information.
  vector<Product> products;

  // Greet the user.
  cout << "Welcome to the product registration system." << endl;

  // Get 3 items from the user.
  for (int i = 0; i < 3; i++) {
    Product product;

    // State product entry number.
    cout << endl << "Product #" << (i + 1);

    // Get the date.
    cout << endl << "Enter date of purchase: ";
    cin >> product.date;

    // Get the serial number.
    cout << endl << "Enter serial number: ";
    cin >> product.sn;
    cout << endl;

    // Display the product type options.
    for (int i = 0; i < NUM_PRODUCTS; i++) {
      cout << i + 1 << ") " << PRODUCT_TYPE[i] << endl;
    }

    // Get the product type.
    cout << endl << "Select product type: ";
    cin >> type;

    // Convert the product type to the enum.
    product.type = static_cast<ProductType>(type - 1);

    // Add the product to the vector.
    products.push_back(product);
  }

  // Display elements of the vector.
  for (int i = 0; i < products.size(); i++) {
    cout << endl << "Product #....: " << (i + 1) << endl;
    cout << "Product Type.: " << PRODUCT_TYPE[products[i].type] << endl;
    cout << "Purchase Date: " << products[i].date << endl;
    cout << "Serial Number: " << products[i].sn << endl;
  }
}