#include <iostream>
#include <fstream>
#include <stack>
#include <unordered_map>

using namespace std;

typedef unordered_map<string, vector<string>> Graph;

Graph graph;
int counter = 0;

void dfs(string start, string end) {
  stack<string> s;
  unordered_map<string, bool> visited;

  s.push(start);
  visited[start] = true;

  while(!s.empty()) {
    string curr = s.top();
    s.pop();
    if(curr == end) {
      counter++;
      continue;
    }
    for(auto& neighbour : graph[curr]) {
      if(!visited[neighbour]) {
        visited[neighbour] = true;
        dfs(neighbour, end);
      }
    }
  }
}

int main() {
  ifstream file("input.txt");

  string s1, s2; char c;
  while(file >> s1) {
    s1.pop_back();
    while(file.peek() != '\n') {
      file >> s2;
      graph[s1].push_back(s2);
    }
  }

  dfs("you", "out");
  cout << counter;

  return 0;
}
