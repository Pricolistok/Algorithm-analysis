#include <iostream>
#include "../inc/vinograd_algorithm.h"
#include "../inc/simple_multiplication.h"
#include "../inc/funcs.h"
#include "../inc/errors.h"
#include "../inc/input_output.h"


using namespace std;

int main()
{
//    size_t n = 5, m = 5;
//    double **matrix_a = add_memory_matrix(n, m);
//    double *data = add_memory_to_array(n * m);
//
//    if (!matrix_a)
//        return ERROR_ADD_MEM;
//    if (!data)
//        return ERROR_ADD_MEM;
//
//    generate_data_array(data, n * m);
//    input_data_to_matrix(matrix_a, data, n, m);
//    print_matrix(matrix_a, n, m);
//    free_memory_matrix(matrix_a, n);
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
        return OK;
    else if (choice == 3)
        return OK;
    else
        return ERROR;

}
