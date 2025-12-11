#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <tuple>

using namespace std;

typedef unordered_map<string, vector<string>> Graph;

Graph graph;
map<tuple<string, bool, bool>, long long> memo;

long long dfs(string curr, string end, unordered_set<string> &visited, bool hasFft, bool hasDac) {
  if (curr == "fft")
    hasFft = true;
  if (curr == "dac")
    hasDac = true;

  auto key = make_tuple(curr, hasFft, hasDac);
  if (memo.count(key))
    return memo[key];

  visited.insert(curr);

  if (curr == end) {
    visited.erase(curr);
    long long result = (hasFft && hasDac) ? 1 : 0;
    memo[key] = result;
    return result;
  }

  long long count = 0;
  for (auto &neighbour : graph[curr])
    if (visited.find(neighbour) == visited.end())
      count += dfs(neighbour, end, visited, hasFft, hasDac);

  visited.erase(curr);
  memo[key] = count;
  return count;
}

int main() {
  ifstream file("input.txt");

  string s1, s2;
  char c;
  while (file >> s1) {
    s1.pop_back();
    while (file.peek() != '\n' && file.peek() != EOF) {
      file >> s2;
      graph[s1].push_back(s2);
    }
  }

  unordered_set<string> visited;
  long long result = dfs("svr", "out", visited, false, false);
  cout << result;

  return 0;
}
