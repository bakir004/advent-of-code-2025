#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

map<vector<int>, int> memo;

void subtractVector(vector<int> &v1, const vector<int> &v2) {
  for (int i = 0; i < v2.size(); i++)
    v1[v2[i]]--;
}

int dp(vector<int> targetJoltage, vector<vector<int>> &buttons) {
  bool allZeros = true, hasNegative = false;
  for (auto &e : targetJoltage) {
    if (e != 0) allZeros = false;
    if (e < 0) hasNegative = true;
  }
  if (allZeros) return 0;
  if (hasNegative) return 1000000;

  if (memo.count(targetJoltage))
    return memo[targetJoltage];

  int minButtonCount = 1000000;
  for (auto &button : buttons) {
    vector<int> target = targetJoltage;
    subtractVector(target, button);
    int count = dp(target, buttons) + 1;
    minButtonCount = min(minButtonCount, count);
  }

  memo[targetJoltage] = minButtonCount;
  return minButtonCount;
}

int main()
{
  ifstream file("input.txt");

  string lights, button, joltageStr;
  int finalCount = 0;
  while (true) {
    file >> lights;
    if (!file) break;
    vector<string> buttonStrs;
    while (file.peek() != '\n') {
      file >> button;
      buttonStrs.push_back(button);
    }
    joltageStr = buttonStrs.back();
    buttonStrs.pop_back();

    vector<int> joltage;
    vector<vector<int>> buttons(buttonStrs.size());
    for (int i = 0; i < buttonStrs.size(); i++) {
      string s = buttonStrs[i];
      istringstream iss(s.substr(1, s.size() - 2));
      int n;
      char c;
      while (iss >> n) {
        iss >> c;
        buttons[i].push_back(n);
        if (!iss)
          break;
      }
    }
    istringstream iss(joltageStr.substr(1, joltageStr.size() - 2));
    int n;
    char c;
    while (iss >> n) {
      iss >> c;
      joltage.push_back(n);
      if (!iss)
        break;
    }
    memo.clear(); 
    int result = dp(joltage, buttons);
    cout << "Machine result: " << result << endl;
    finalCount += result;
  }
  cout << finalCount;

  return 0;
}
