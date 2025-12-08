#include<iostream>
#include<fstream>

using namespace std;

long long solveSingleProblem(vector<string>& matrix, int from, int to) {
  cout << "from: " << from << " to " << to << "\n";
  char op = matrix[matrix.size()-1][from];
  int m = matrix.size(), n = matrix[0].size();
  long long rez = op == '*';
  for(int j = from; j < to; j++) {
    long long currNum = 0;
    for(int i = 0; i < m-1; i++)
      if(matrix[i][j] != ' ')
        currNum = currNum * 10 + (matrix[i][j]-'0');
    cout << "Curr: " << currNum << '\n';
    if(op == '*') rez *= currNum;
    else rez += currNum;
  }
  cout << "Rez: " << rez << "\n";
  // 123 328  51 64 
  //  45 64  387 23 
  //   6 98  215 314
  // *   +   *   +  
  return rez;
}

int main() {
  ifstream tok("input.txt", ios::in);
  vector<string> matrix;
  string s;
  while(getline(tok, s))
    matrix.push_back(s);
  long long total = 0;
  int pastStart = 0;
  for(int i = 1; i < matrix[0].size(); i++) {
    char curr = matrix[matrix.size()-1][i];
    if(curr == '+' || curr == '*' || i == matrix[0].size() - 1) {
      total += solveSingleProblem(matrix, pastStart, i-1 + 2*(i==matrix[0].size()-1));
      pastStart = i;
    }
  }
  cout << total;


  return 0;
}
