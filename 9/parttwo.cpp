#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int windingNumber(long long px, long long py, const vector<pair<long long, long long>> &polygon) {
  int winding = 0;
  int n = polygon.size();

  for (int i = 0; i < n; i++) {
    long long x1 = polygon[i].first;
    long long y1 = polygon[i].second;
    long long x2 = polygon[(i + 1) % n].first;
    long long y2 = polygon[(i + 1) % n].second;

    if (y1 <= py) {
      if (y2 > py) {
        long long cross = (x2 - x1) * (py - y1) - (px - x1) * (y2 - y1);
        if (cross > 0)
          winding++;
      }
    } else {
      if (y2 <= py) {
        long long cross = (x2 - x1) * (py - y1) - (px - x1) * (y2 - y1);
        if (cross < 0)
          winding--;
      }
    }
  }
  return winding;
}

bool isOnBoundary(long long px, long long py, const vector<pair<long long, long long>> &points) {
  int n = points.size();
  for (int i = 0; i < n; i++) {
    long long x1 = points[i].first;
    long long y1 = points[i].second;
    long long x2 = points[(i + 1) % n].first;
    long long y2 = points[(i + 1) % n].second;

    if (x1 == x2 && px == x1 && py >= min(y1, y2) && py <= max(y1, y2))
      return true;
    if (y1 == y2 && py == y1 && px >= min(x1, x2) && px <= max(x1, x2))
      return true;
  }
  return false;
}

bool isGreen(long long px, long long py, const vector<pair<long long, long long>> &points) {
  return isOnBoundary(px, py, points) || windingNumber(px, py, points) != 0;
}

int main() {
  ifstream file("input.txt");

  long long x, y;
  char c;
  vector<pair<long long, long long>> points;
  while (file >> x >> c >> y)
    points.push_back({x, y});

  set<pair<long long, long long>> redSet(points.begin(), points.end());

  cerr << "Total points: " << points.size() << endl;

  vector<vector<pair<int, int>>> greenNeighbors(points.size());
  int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

  for (int i = 0; i < points.size(); i++) {
    for (int d = 0; d < 8; d++) {
      long long nx = points[i].first + dx[d];
      long long ny = points[i].second + dy[d];

      if (isGreen(nx, ny, points))
        greenNeighbors[i].push_back({dx[d], dy[d]});
    }
  }

  cerr << "Green neighbors computed" << endl;

  long long maxArea = 0;
  long long totalPairs = (long long)points.size() * (points.size() - 1) / 2;
  long long pairsChecked = 0;
  int lastPercent = -1;

  cerr << "Checking " << totalPairs << " rectangle pairs..." << endl;

  for (int i = 0; i < points.size(); i++) {
    for (int j = i + 1; j < points.size(); j++) {
      pairsChecked++;

      int percent = (pairsChecked * 100) / totalPairs;
      if (percent != lastPercent && percent % 10 == 0) {
        cerr << percent << "% complete (max area so far: " << maxArea << ")" << endl;
        lastPercent = percent;
      }

      long long minX = min(points[i].first, points[j].first);
      long long maxX = max(points[i].first, points[j].first);
      long long minY = min(points[i].second, points[j].second);
      long long maxY = max(points[i].second, points[j].second);

      bool valid = true;

      for (int k = 0; k < points.size() && valid; k++) {
        if (k == i || k == j)
          continue;

        long long px = points[k].first;
        long long py = points[k].second;

        if (px > minX && px < maxX && py > minY && py < maxY) {
          valid = false;
          break;
        }

        if (px >= minX && px <= maxX && py >= minY && py <= maxY) {
          int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
          int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

          for (int d = 0; d < 8; d++) {
            long long nx = px + dx[d];
            long long ny = py + dy[d];

            if (nx >= minX && nx <= maxX && ny >= minY && ny <= maxY) {
              bool isRed = false;
              for (int m = 0; m < points.size(); m++) {
                if (points[m].first == nx && points[m].second == ny) {
                  isRed = true;
                  break;
                }
              }

              if (!isRed && !isGreen(nx, ny, points)) {
                valid = false;
                break;
              }
            }
          }
        }
      }

      if (valid && maxX > minX + 1 && maxY > minY + 1) {
        long long width = maxX - minX + 1;
        long long height = maxY - minY + 1;
        int samples = min(100LL, max(20LL, (width + height) / 1000));

        for (int gx = 1; gx <= samples && valid; gx++) {
          for (int gy = 1; gy <= samples && valid; gy++) {
            long long sx = minX + ((maxX - minX) * gx) / (samples + 1);
            long long sy = minY + ((maxY - minY) * gy) / (samples + 1);

            if (!redSet.count({sx, sy}) && !isGreen(sx, sy, points))
              valid = false;
          }
        }
      }

      if (valid) {
        long long area = (maxX - minX + 1) * (maxY - minY + 1);
        maxArea = max(maxArea, area);
      }
    }
  }

  cerr << "\n100% complete!" << endl;
  cerr << "Final max area: ";
  cout << maxArea << endl;

  return 0;
}
