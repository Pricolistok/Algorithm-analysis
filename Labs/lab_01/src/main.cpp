#include <iostream>
#include "vinograd_algorithm.h"
#include "simple_multiplication.h"
#include "funcs.h"
#include "errors.h"
#include "input_output.h"


using namespace std;

int main()
{
    short int choice;

    cout << "Select the program operating mode: " << endl;
    cout << "1 - Multiply two matrices" << endl;
    cout << "2 - Run time tests" << endl;
    cout << "3 - Exit the program" << endl;
    cout << "Your choice: ";
    cin >> choice;

    while ((choice < 0) || (choice > 3))
    {
        cout << "Invalid input! Please try again." << endl << "Your choice: ";
        cin >> choice;
    }

    if (choice == 1)
        return multiply_two_matrix();
    else if (choice == 2)
        return time_tests();
    else if (choice == 3)
        return OK;
    else
        return ERROR;
}
