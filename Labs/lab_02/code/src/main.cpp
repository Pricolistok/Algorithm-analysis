#include "errors.h"
#include "funcs.h"
#include "input.h"
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
  short int choice;

  cout << "Программа для вывода элементов с нечетными номерами в "
          "последовательности: "
       << endl;
  cout << "1 - Рекурсивный алгоритм" << endl;
  cout << "2 - Итеративный алгоритм" << endl;
  cout << "3 - Замеры времени выполнения" << endl;
  cout << "4 - Exit the program" << endl;
  cout << "Ваш выбор: ";
  cin >> choice;

  while ((choice < 1) || (choice > 4)) {
    cout << "Ошибка ввода! Повторите" << endl << "Ваш выбор: ";
    cin >> choice;
  }

  if (choice == 1)
    return recursive_algorithm();
  else if (choice == 2)
    return iterative_algorithm();
  else if (choice == 3)
    return time_tests();
  else if (choice == 4)
    return OK;
  else
    return ERROR;
}