#include<iostream>
#include<fstream>
#include<unordered_set>

using namespace std;

int main() {
  ifstream file("input.txt");

  string s;
  unordered_set<long long> rays;
  long long count = 0;
  vector<string> matrix;
  while(getline(file, s)) {
    matrix.push_back(s);
    for(int i = 0; i < s.size(); i++) {
      if(s[i] == 'S') rays.insert(i);
      if(s[i] == '^' && rays.count(i) > 0) {
        count++;
        rays.erase(i);
        rays.insert(i-1);
        rays.insert(i+1);
      } 
    }
  }
  cout << count;

  return 0;
}
