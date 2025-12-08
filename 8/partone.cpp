#include <iostream>
#include <fstream>

using namespace std;

class UnionFind {
  vector<int> parent;

public:
  UnionFind(int size) : parent(vector<int>(size, 0)) {
    for (int i = 0; i < parent.size(); i++)
      parent[i] = i;
  }
  int find(int i) {
    if (parent[i] == i)
      return i;
    return find(parent[i]);
  }
  void unite(int i, int j) {
    int parentI = find(i);
    int parentJ = find(j);
    parent[parentI] = parentJ;
  }
};

struct Point {
  long long id, x, y, z;
  void print() {
    cout << "{" << id << ": {" << x << ',' << y << ',' << z << "}}\n";
  }
};

struct Edge {
  double w;
  long long p1, p2;
  void print() {
    cout << "(" << p1 << "-" << p2 << ", " << w << ")\n";
  }
};

double d(Point &p1, Point &p2) {
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

vector<Edge> getEdges(vector<Point> &points) {
  vector<Edge> edges;
  for (int i = 0; i < points.size(); i++) {
    for (int j = i + 1; j < points.size(); j++) {
      if (i == j)
        continue;

      Edge e{d(points[i], points[j]), points[i].id, points[j].id};
      edges.push_back(e);
    }
  }
  return edges;
}

long long floodfill(int start, vector<bool> &visited, vector<vector<int>> &graph) {
  visited[start] = true;
  long long size = 1;
  for (auto e : graph[start]) {
    if (visited[e])
      continue;

    size += floodfill(e, visited, graph);
  }
  return size;
}

int main() {
  ifstream file("input.txt", ios::in);

  vector<Point> points;
  char c;
  Point p;
  int nextId = 0;
  while (file >> p.x >> c >> p.y >> c >> p.z) {
    p.id = nextId++;
    points.push_back(p);
  }
  vector<Edge> edges = getEdges(points);
  sort(edges.begin(), edges.end(), [](Edge &e1, Edge &e2)
       { return e1.w < e2.w; });

  vector<vector<int>> graph(points.size(), vector<int>());
  UnionFind u(points.size());
  vector<bool> completed(points.size(), false);
  int remaining = points.size();

  int count = 0;
  for (auto &e : edges) {
    if (u.find(e.p1) != u.find(e.p2)) {
      u.unite(e.p1, e.p2);
      graph[e.p1].push_back(e.p2);
      graph[e.p2].push_back(e.p1);
    }
    count++;
    if (count >= 1000) break;
  }

  vector<bool> visited(points.size(), false);
  vector<long long> sizes;
  for (int i = 0; i < visited.size(); i++) {
    if (visited[i]) continue;
    long long size = floodfill(i, visited, graph);
    sizes.push_back(size);
  }
  sort(sizes.begin(), sizes.end());
  int n = sizes.size();
  long long pr = 1;
  for (int i = 0; i < min((int)sizes.size(), 3); i++)
    pr *= sizes[n - 1 - i];
  cout << pr;

  return 0;
}
