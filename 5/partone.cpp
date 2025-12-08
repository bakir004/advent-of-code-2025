#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int main() {
  auto file = ifstream("input.txt", ios::in);
  string s;
  vector<pair<long long,long long>> ranges;
  while(getline(file, s)) {
    if(s == "") break;
    istringstream iss(s);
    long long a,b; char c;
    iss >> a >> c >> b;
    ranges.push_back({a,b});
  }
  long long n, count = 0;
  while(file >> n) {
    for(auto& r : ranges) {
      if(n >= r.first && n <= r.second) {
        count++;
        break;
      }
    }
  }
  cout << count;
  return 0;
}
