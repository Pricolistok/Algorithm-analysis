#include "errors.h"
#include "funcs.h"
#include "input_output.h"
#include "simple_multiplication.h"
#include "vinograd_algorithm.h"
#include <iostream>

#define CNT_TIMES 20
#define MEASUREMENTS 500
#define VERBOSE 0

using namespace std;

int main() {
  short int choice;

  cout << "Select the program operating mode: " << endl;
  cout << "1 - Multiply two matrices" << endl;
  cout << "2 - Run time tests" << endl;
  cout << "3 - Exit the program" << endl;
  cout << "Your choice: ";
  cin >> choice;

  while ((choice < 0) || (choice > 3)) {
    cout << "Invalid input! Please try again." << endl << "Your choice: ";
    cin >> choice;
  }

  if (choice == 1)
    return multiply_two_matrix();
  else if (choice == 2)
    return time_tests(CNT_TIMES, MEASUREMENTS, VERBOSE);
  else if (choice == 3)
    return OK;
  else
    return ERROR;
}
