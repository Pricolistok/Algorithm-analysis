#ifndef FUNCS_H
#define FUNCS_H

#include <cstdint>
#include <vector>

void printOddPositionsRecursive(const std::vector<int> &sequence,
                                int index = 0);
void printOddPositionsIterative(const std::vector<int> &sequence);
void recursive_algorithm_measure(const std::vector<int> &sequence,
                                 int index = 0);
void iterative_algorithm_measure(const std::vector<int> &sequence);
int recursive_algorithm();
int iterative_algorithm();
int time_tests();
uint64_t read_tsc();
void recursive_algorithm_to_array(const std::vector<int> &sequence,
                                  std::vector<int> &result, int index = 0);
void iterative_algorithm_to_array(const std::vector<int> &sequence,
                                  std::vector<int> &result);

#endif