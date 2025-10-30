void printOddPositionsRecursive(const vector<int> &sequence, int index) {
  if (index >= (int)sequence.size()) {
    return;
  }
  if ((index + 1) % 2 != 0) {
    cout << sequence[index] << " ";
  }
  printOddPositionsRecursive(sequence, index + 1);
}