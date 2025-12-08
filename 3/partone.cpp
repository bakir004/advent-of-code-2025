#include<iostream>
#include<fstream>

using namespace std;

int main() {
  auto file = ifstream("input.txt", ios::in);
  string s;
  int sum = 0;
  while(file >> s) {
    int largest = 0;
    int bestNum = 0;
    for(auto &c : s) {
      int curr = c-'0';
      bestNum = max(bestNum, curr + 10*largest);
      if(curr > largest)
        largest = curr;
    }
    sum += bestNum;
  }
  cout << sum;
  return 0;
}
