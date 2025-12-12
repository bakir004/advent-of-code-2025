#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
  ifstream file("input.txt");
  string line;

  while (getline(file, line)) {
    if (line.empty()) continue;
    if (isdigit(line[0]) && line.find('x') != string::npos)
      break;
  }

  int validCount = 0;

  do {
    if (line.empty()) continue;

    int w, h;
    sscanf(line.c_str(), "%dx%d:", &w, &h);

    size_t colonPos = line.find(':');
    istringstream iss(line.substr(colonPos + 1));

    int totalPieces = 0;
    int c;
    while (iss >> c)
      totalPieces += c;

    if ((w / 3) * (h / 3) >= totalPieces)
      validCount++;
  } while (getline(file, line));

  cout << validCount;
  return 0;
}
