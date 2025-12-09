#include<iostream>
#include<fstream>

using namespace std;

int main() {
  ifstream file("input.txt");

  long long x,y; char c;
  vector<pair<long long, long long>> points;
  while(file >> x >> c >> y)
    points.push_back({x,y});
  
  long long maxP = 0;
  for(int i = 0; i < points.size(); i++) {
    for(int j = i+1; j < points.size(); j++) {
      if(i == j) continue;
      // cout << points[i].first << "," << points[i].second << "-";
      // cout << points[j].first << "," << points[j].second << '=';

      long long p = abs(points[i].first - points[j].first+1) 
        * abs(points[i].second - points[j].second+1);
      // cout << p << '\n';
      maxP = max(maxP,p);
    }
  }
  cout << maxP;

  return 0;
}
