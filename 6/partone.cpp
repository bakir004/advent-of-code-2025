#include<iostream>
#include<sstream>
#include<fstream>

using namespace std;

int main() {
  ifstream tok("input.txt", ios::in);
  vector<vector<long long>> matrica;

  vector<char> operatori;
  while(true) {
    string trenutniRed;
    getline(tok, trenutniRed);
    if(trenutniRed.size() == 0) break;

    bool imaBrojeva = false;
    for(auto& karakter : trenutniRed) {
      if(karakter >= '0' && karakter <= '9') {
        imaBrojeva = true;
        break;
      }
    }
    if(!imaBrojeva) { 
      istringstream redTok(trenutniRed);
      char c;
      while(redTok >> c) {
        operatori.push_back(c);
      }
      break;
    }
    istringstream redTok(trenutniRed);
    vector<long long> redMatrice;
    long long n;
    while(redTok >> n) {
      redMatrice.push_back(n);
    }
    matrica.push_back(redMatrice);
  }

  long long konacniZbir = 0;
  for(int j = 0; j < matrica[0].size(); j++) {
    long long rezultat = 0;
    if(operatori[j] == '*') rezultat = 1;
    for(int i = 0; i < matrica.size(); i++) {
      if(operatori[j] == '+')
        rezultat += matrica[i][j];
      else
        rezultat *= matrica[i][j];
    }
    konacniZbir += rezultat;
  }
  cout << konacniZbir;

  // for(auto& red : matrica) {
  //   for(auto& e : red)
  //     cout << e << " ";
  //   cout << "\n";
  // }
  // cout << "operatori:\n";
  // for(auto& e : operatori)
  //   cout << e << " ";
  //
  return 0;
}
