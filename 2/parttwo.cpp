#include<iostream>
#include<fstream>

using namespace std;

long long numDigits(long long n) {
  if(n == 0) return 1;
  return int(log10(n))+1;
}

long long getNextEvenDigitNumber(long long n) {
  long long digits = numDigits(n);
  return pow(10, digits + (digits % 2 == 1)-1);
}

bool isInvalid(long long x) {
  if(x < 11) return false;
  long long digits = numDigits(x);
  long long max10Degree = digits / 2;
  for(long long i = 1; i <= max10Degree; i++) {
    long long y = x;
    if(digits % i != 0) continue;
    long long powOf10 = pow(10, i);
    long long firstIDigits = y % powOf10;
    y /= powOf10;
    bool valid = true;
    bool didOneIteration = false;
    while(y > 0) {
      if(y % powOf10 != firstIDigits) valid = false;
      y /= powOf10;
      didOneIteration = true;
    }
    if(valid && didOneIteration) return true;
  }
  return false;
}

int main() {
  auto file = ifstream("input.txt", ios::in);
  long long invalidSum = 0, a, b;
  char c;
  while(file >> a >> c >> b) {
    for(long long i = a; i <= b; i++)
      if(isInvalid(i))
        invalidSum += i;

    if(!(file >> c)) break;
  }
  cout << invalidSum;
  return 0;
}
