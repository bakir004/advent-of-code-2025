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
  sort(ranges.begin(), ranges.end(), [](auto& r1, auto& r2){
    return r1.first < r2.first;
  });
  long long count = 0;

  for(int i = 0; i < ranges.size()-1; i++) {
    if(ranges[i].second >= ranges[i+1].first) {
      ranges[i].second = max(ranges[i].second,ranges[i+1].second);
      ranges.erase(ranges.begin()+i+1);
      i--;
    } else count += ranges[i].second - ranges[i].first+1;
  }
  count += ranges[ranges.size()-1].second - ranges[ranges.size()-1].first+1;

  cout << count;
  return 0;
}
