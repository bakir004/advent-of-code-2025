#include <iostream>
#include <fstream>
#include <map>

using namespace std;

map<pair<long long, long long>, long long> memo;

long long simulate(vector<string> &matrix, long long col, long long row) {
  while (row < matrix.size()) {
    if (row >= matrix.size() - 1)
      return 1;

    if (matrix[row][col] == '^') {
      auto key = make_pair(col, row);
      if (memo.count(key))
        return memo[key];

      long long timelines = 0;
      if (col > 0)
        timelines += simulate(matrix, col - 1, row + 1);
      if (col < (long long)matrix[row].size() - 1)
        timelines += simulate(matrix, col + 1, row + 1);
      memo[key] = timelines;
      return timelines;
    }

    row++;
  }

  return 1;
}

int main() {
  ifstream file("input.txt");

  string s;
  vector<string> matrix;
  while (getline(file, s))
    matrix.push_back(s);

  long long startCol = -1;
  for (int i = 0; i < matrix[0].size(); i++) {
    if (matrix[0][i] == 'S') {
      startCol = i;
      break;
    }
  }

  long long timelines = simulate(matrix, startCol, 1);
  cout << timelines;

  return 0;
}
