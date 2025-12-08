#include<iostream>
#include<fstream>

using namespace std;

void removeFirstNDigitsToMakeBiggestNumber(string& s, int start, int toRemove, string& res) {
  if(start + toRemove >= s.size()) return;
  if(start >= s.size()) return;
  if(toRemove == 0) {
    for(int i = start; i < s.size(); i++)
      res += s[i];
    return;
  }
  int biggestIndex = start;
  for(int i = start; i < start + toRemove + 1; i++) {
    if(s[i] > s[biggestIndex])
      biggestIndex = i;
  }
  res += s[biggestIndex];

  removeFirstNDigitsToMakeBiggestNumber(s, biggestIndex+1, toRemove-(biggestIndex-start), res);
}

int main() {
  auto file = ifstream("input.txt", ios::in);
  string s;
  long long sum = 0;
  while(file >> s) {
    string res = "";
    removeFirstNDigitsToMakeBiggestNumber(s, 0, s.size()-12, res);  
    sum += stoll(res);
  }
  // 234234234234 789
  cout << "Final: " << sum;
  return 0;
}
