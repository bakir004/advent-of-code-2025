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

int main() {
  auto file = ifstream("input.txt", ios::in);
  long long invalidSum = 0, a, b;
  char c;
  while(file >> a >> c >> b) {
    long long iterationCount = 0;
    long long digits = numDigits(a);
    if(digits % 2 == 1) {
      a = getNextEvenDigitNumber(a);
      digits = numDigits(a);
    }
    if(a > b) {
      if(!(file >> c)) break;
      continue;
    }

    long long tenToHalfDigitsPower = (long long)(pow(10, digits >> 1));
    long long increment = tenToHalfDigitsPower + 1;
    long long firstHalfDigits = a / tenToHalfDigitsPower;
    long long firstValid = firstHalfDigits * tenToHalfDigitsPower + firstHalfDigits;
    if(firstValid < a) firstValid += increment;
    while(firstValid <= b) {
      if(numDigits(firstValid) % 2 == 1) {
        firstValid = getNextEvenDigitNumber(firstValid);
        digits = numDigits(firstValid);
        tenToHalfDigitsPower = (long long)(pow(10, digits >> 1));
        firstHalfDigits = firstValid / tenToHalfDigitsPower;
        firstValid = firstHalfDigits * tenToHalfDigitsPower + firstHalfDigits;
        if(firstValid > b) break;
      }
      invalidSum += firstValid;
      firstValid += increment;
    }
    
    if(!(file >> c)) break;
  }
  cout << invalidSum;
  return 0;
}
