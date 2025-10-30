void printOddPositionsIterative(const vector<int> &sequence) {
  for (size_t i = 0; i < sequence.size(); i++) {
    if ((i + 1) % 2 != 0) {
      cout << sequence[i] << " ";
    }
  }
  cout << endl;
}