#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int lightsToBin(string s) {
  int target = 0;
  for(int i = 0; i < s.size(); i++) {
    if(s[i] == '#')
      target++;
    target <<= 1;
  }
  target >>= 1;
  return target;
}

string toBin(int n, int width) {
  string s;
  while(n > 0) {
    s = (char)('0' + n%2) + s;
    n /= 2;
    width--;
  }
  for(int i = 0; i < width; i++)
    s = '0' + s;
  return s;
}

int findBestButtons(int target, vector<int>& buttons) {
  int minCount = INT_MAX;
  for(int i = 1; i < pow(2, buttons.size()); i++) {
    string choices = toBin(i, buttons.size());
    int x = 0, count = 0;
    for(int j = 0; j < choices.size(); j++) {
      if(choices[j] == '1') {
        count++;
        x ^= buttons[j];
      }
    }
    if(x == target && count < minCount) {
      // cout << choices << " is the winner with " << count << " buttons\n";
      minCount = count;
    }
  }
  return minCount;
}

int main() {
  ifstream file("input.txt");

  string lights, button, joltage;
  int finalCount = 0;
  while(true) {
    file >> lights;
    if(!file) break;
    vector<string> buttons;
    while(file.peek() != '\n') {
      file >> button;
      buttons.push_back(button);
    }
    joltage = buttons.back();
    buttons.pop_back();
    
    // read correctly
    int target = lightsToBin(lights.substr(1, lights.size()-2));
    int lightsSize = lights.size()-2;
    //   [.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
    //  [...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
    // [.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}
    vector<int> buttonsNums;
    // cout << lights << "\n";
    for(auto& s : buttons) {
      // cout << "doing " << s << "\n";
      istringstream iss(s.substr(1, s.size()-2));
      int n, buttonNum = 0; char c;
      while(iss >> n) {
        // cout << "for this button n is " << n << "\n";
        iss >> c;
        buttonNum += (1 << (lightsSize-1-n));
        if(!iss) break;
      }
      // cout << "for this buttonNum is " << bitset<10>(buttonNum) << "\n";
      buttonsNums.push_back(buttonNum);
    }
    // cout << "\nButtonNums " << ": \n";
    // for(auto& e : buttonsNums)
    // cout << bitset<10>(e) << " ";
    finalCount += findBestButtons(target, buttonsNums);
  }
  cout << finalCount;


  return 0;
}
