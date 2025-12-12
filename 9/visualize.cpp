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

int main() {
  ifstream file("input.txt");
  long long x, y;
  char c;
  vector<pair<long long, long long>> points;
  while (file >> x >> c >> y)
    points.push_back({x, y});

  long long minX = points[0].first, maxX = points[0].first;
  long long minY = points[0].second, maxY = points[0].second;
  for (auto &p : points) {
    minX = min(minX, p.first);
    maxX = max(maxX, p.first);
    minY = min(minY, p.second);
    maxY = max(maxY, p.second);
  }

  long long width = maxX - minX + 1;
  long long height = maxY - minY + 1;
  int imgWidth = min(1000LL, width);
  int imgHeight = min(1000LL, height);

  set<pair<long long, long long>> redSet(points.begin(), points.end());

  ofstream img("shape.ppm");
  img << "P3\n" << imgWidth << " " << imgHeight << "\n255\n";

  for (int py = 0; py < imgHeight; py++) {
    for (int px = 0; px < imgWidth; px++) {
      long long wx = minX + (px * width) / imgWidth;
      long long wy = minY + (py * height) / imgHeight;

      if (redSet.count({wx, wy}))
        img << "255 0 0 ";
      else if (isOnBoundary(wx, wy, points))
        img << "0 255 0 ";
      else if (windingNumber(wx, wy, points) != 0)
        img << "100 200 100 ";
      else img << "50 50 50 ";
    }
    img << "\n";

    if (py % 100 == 0)
      cout << "Progress: " << (py * 100 / imgHeight) << "%" << endl;
  }

  img.close();
  cout << "Image saved to shape.ppm" << endl;
  cout << "You can open it with most image viewers or convert to PNG with: convert shape.ppm shape.png" << endl;

  return 0;
}
