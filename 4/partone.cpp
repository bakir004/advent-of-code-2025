#include<iostream>
#include<fstream>

using namespace std;

int valid(int i, int j, int m, int n, vector<string>& matrix) {
  return i >= 0 && j >= 0 && i < m && j < n && (matrix[i][j] == '@' || matrix[i][j] == 'x');
}

int main() {
  auto file = ifstream("input.txt", ios::in);
  vector<string> matrix;
  string s;
  while(file >> s)
    matrix.push_back(s);

  int m = matrix.size(), n = matrix[0].size();
  int count = 0;

  while(true) {
    int countForRound = 0;
    for(int i = 0; i < m; i++) {
      for(int j = 0; j < n; j++) {
        if(matrix[i][j] != '@') continue;
        int countOfAts = 0;
        countOfAts += valid(i+1,j-1,m,n,matrix);
        countOfAts += valid(i+1,j,  m,n,matrix);
        countOfAts += valid(i+1,j+1,m,n,matrix);
        countOfAts += valid(i-1,j-1,m,n,matrix);
        countOfAts += valid(i-1,j,  m,n,matrix);
        countOfAts += valid(i-1,j+1,m,n,matrix);
        countOfAts += valid(i  ,j-1,m,n,matrix);
        countOfAts += valid(i  ,j+1,m,n,matrix);
        if(countOfAts < 4) {
          countForRound++;
          matrix[i][j] = 'x';
        }
      }
    }
    for(auto& s : matrix)
      for(auto& c : s)
        if(c == 'x')
          c = '.';

    if(countForRound == 0) break;
    count += countForRound;
  }
  cout << count << "\n";
  for(auto s : matrix)
    cout << s << '\n';

  return 0;
}
