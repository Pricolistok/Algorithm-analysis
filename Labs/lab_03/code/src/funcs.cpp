#include "funcs.hpp"
#include "consts.hpp"
#include "errors.hpp"
#include "input.hpp"
#include <fstream>
#include <iostream>

using namespace std;

uint64_t read_tsc() {
  uint64_t tsc;
  asm volatile("rdtsc" : "=A"(tsc));
  return tsc;
}

void printOddPositionsRecursive(const vector<int> &sequence, int index) {
  if (index >= (int)sequence.size()) {
    return;
  }
  if ((index + 1) % 2 != 0) {
    cout << sequence[index] << " ";
  }
  printOddPositionsRecursive(sequence, index + 1);
}

void printOddPositionsIterative(const vector<int> &sequence) {
  for (size_t i = 0; i < sequence.size(); i++) {
    if ((i + 1) % 2 != 0) {
      cout << sequence[i] << " ";
    }
  }
  cout << endl;
}

void recursive_algorithm_measure(const vector<int> &sequence, int index) {
  if (index >= (int)sequence.size()) {
    return;
  }
  if ((index + 1) % 2 != 0) {
  }
  recursive_algorithm_measure(sequence, index + 1);
}

void iterative_algorithm_measure(const vector<int> &sequence) {
  for (size_t i = 0; i < sequence.size(); i++) {
    if ((i + 1) % 2 != 0) {
    }
  }
}

int recursive_algorithm() {
  vector<int> sequence = inputSequence();

  if (sequence.empty()) {
    cout << "Последовательность пуста!" << endl;
    return OK;
  }

  cout << "Элементы с нечетными номерами (рекурсивно):" << endl;
  printOddPositionsRecursive(sequence, 0);
  cout << endl;

  return OK;
}

int iterative_algorithm() {
  vector<int> sequence = inputSequence();

  if (sequence.empty()) {
    cout << "Последовательность пуста!" << endl;
    return OK;
  }

  cout << "Элементы с нечетными номерами (итеративно):" << endl;
  printOddPositionsIterative(sequence);

  return OK;
}

int time_tests() {
  cout << "Замеры времени выполнения в тактах процессора" << endl;
  cout << "Длина последовательности: от " << START_LENGTH << " до "
       << END_LENGTH << " с шагом " << STEP_LENGTH << endl;
  cout << "Количество замеров для каждой длины: " << MEASUREMENTS_COUNT << endl;
  cout << endl;

  ofstream data_file("time_measurements.txt");
  if (!data_file.is_open()) {
    cout << "Ошибка открытия файла для записи!" << endl;
    return ERROR;
  }

  cout << "┌───────┬────────────────┬────────────────┐" << endl;
  cout << "│ Длина │  Рекурсивный   │  Итеративный   │" << endl;
  cout << "│       │    (тиках)     │    (тиках)     │" << endl;
  cout << "├───────┼────────────────┼────────────────┤" << endl;

  for (int length = START_LENGTH; length <= END_LENGTH; length += STEP_LENGTH) {
    vector<int> test_sequence;
    for (int i = 1; i <= length; i++) {
      test_sequence.push_back(i);
    }

    uint64_t total_recursive = 0, total_iterative = 0;

    for (int m = 0; m < MEASUREMENTS_COUNT; m++) {
      uint64_t start = read_tsc();
      recursive_algorithm_measure(test_sequence, 0);
      uint64_t end = read_tsc();
      total_recursive += (end - start);
    }

    for (int m = 0; m < MEASUREMENTS_COUNT; m++) {
      uint64_t start = read_tsc();
      iterative_algorithm_measure(test_sequence);
      uint64_t end = read_tsc();
      total_iterative += (end - start);
    }

    uint64_t avg_recursive = total_recursive / MEASUREMENTS_COUNT;
    uint64_t avg_iterative = total_iterative / MEASUREMENTS_COUNT;

    data_file << length << " " << avg_iterative << " " << avg_recursive << endl;

    printf("│ %5d │ %14lu │ %14lu │\n", length, avg_recursive, avg_iterative);

    if (length < END_LENGTH) {
      cout << "├───────┼────────────────┼────────────────┤" << endl;
    }
  }

  cout << "└───────┴────────────────┴────────────────┘" << endl;

  data_file.close();
  cout << "Данные сохранены в файл: time_measurements.txt" << endl;

  return OK;
}

void recursive_algorithm_to_array(const vector<int> &sequence,
                                  vector<int> &result, int index) {
  if (index >= (int)sequence.size()) {
    return;
  }

  result.push_back(sequence[index]);
  recursive_algorithm_to_array(sequence, result, index + 2);
}

void iterative_algorithm_to_array(const vector<int> &sequence,
                                  vector<int> &result) {
  for (size_t i = 0; i < sequence.size(); i += 2) {
    result.push_back(sequence[i]);
  }
}