#include "input.hpp"
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

vector<int> inputSequence() {
  vector<int> sequence;
  int number;

  cout << "Введите последовательность целых чисел (0 для завершения):" << endl;

  while (true) {
    cin >> number;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Ошибка ввода! Пожалуйста, введите целое число: ";
      continue;
    }

    if (number == 0) {
      break;
    }

    sequence.push_back(number);
  }

  return sequence;
}