#include<iostream>
#include<fstream>

using namespace std;

int main() {
  char c;
  int n;
  int current = 50;
  int count = 0;
  auto file = ifstream("input.txt", ios::in);
  while(file >> c >> n) {
    if(c == 'L') n = -n;
    count += abs(n) / 100;
    n = n % 100;
    if(n < 0 && current != 0 && current <= -n) count++;
    if(n > 0 && current != 0 && current + n > 99) count++;
    current += n;
    current = ((current % 100) + 100) % 100;
  }
  cout << count;

  return 0;
}
