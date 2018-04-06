#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
#include <limits>

using namespace std;

using std::vector;

class DisjointSet
{
  private:
    // Map from vertex to its parent
    map<int, int> dset;
  public:
    DisjointSet(int size)
    {
      for (int i=0; i<size; i++)
      {
        // Each vertex is put into its own set
        dset[i] = i;
      }
    }

    // Finds the parent of vertex i
    int find(int i)
    {
      if (i > dset.size()) return -1;

      return dset[i];
    }

    // Merge sets of vertices (i, j)
    void merge(int i, int j)
    {
      int parentOfJ = find(j);

      int parentOfI = find(i);

      // Sanity check
      if (parentOfI == parentOfJ) return;

      map<int, int>::iterator it;

      for (it=dset.begin(); it!=dset.end(); it++)
      {
        // Set all elements that belong to the same
        // set as J to belong to the same set as I

        if (it->second == parentOfJ)
        {
          it->second = parentOfI;
        }
      }
    }
};

class ComparePQ
{
  public:
    // p1 comes before p2 if p1's weight is smaller
    bool operator()(pair<pair<int, int>, double> p1, pair<pair<int, int>, double> p2)
    {
      // Min priority queue
      // This means that if p1.second > p2.second,
      // It should be pushed to below p2 in the queue
      return p1.second > p2.second;
    }
};

class ComparePrims
{
  public:
    bool operator()(pair<int, double> p1, pair<int, double> p2)
    {
      // If p1's cost is greater than p2's cost,
      // it must be lower in the priority queue
      // This is because we are writing a min pq
      return p1.second > p2.second;
    }
};

double getDistance(vector<double> x, vector<double> y, int i, int j)
{
  return sqrt(pow(abs(x[i] - x[j]), 2) + pow(abs(y[i] - y[j]), 2));
}

priority_queue<pair<pair<int, int>, double>,
               vector<pair<pair<int, int>, double> >,
               ComparePQ >
  computeWeights(vector<double> x, vector<double> y)
{
  priority_queue<pair<pair<int, int>, double>, vector<pair<pair<int, int>, double> >, ComparePQ > dist;

  for (int i=0; i<x.size(); i++)
  {
    for (int j=i+1; j<x.size(); j++)
    {
      double distance = getDistance(x, y, i, j);

      dist.push(make_pair(make_pair(i, j), distance));
    }
  }

  return dist;
}

double kruskal(priority_queue<pair<pair<int, int>, double>,
               vector<pair<pair<int, int>, double> >,
               ComparePQ > dist,
               int size)
{
  double result = 0.0;

  // Make set
  DisjointSet dset = DisjointSet(size);

  pair< pair<int, int>, double > current;

  int p1; int p2;

  // In non - decreasing order of their weights
  while (!dist.empty())
  {
    current = dist.top();

    dist.pop();

    p1 = current.first.first;

    p2 = current.first.second;

    if (dset.find(p1) != dset.find(p2))
    {
      // When we find an edge that is in a different set,
      // we merge the two sets and add the edge weight to
      // the total weight of the minimum spanning tree
      dset.merge(p1, p2);

      result += current.second;
    }
  }

  return result;
}

double minimum_distance(vector<double> x, vector<double> y)
{
  // We calculate the distance for a pair of points (i, j)
  // We store this as a priority queue
  priority_queue<pair<pair<int, int>, double>,
               vector<pair<pair<int, int>, double> >,
               ComparePQ > dist = computeWeights(x, y);

  int size = x.size();

  return kruskal(dist, size);
}

double prims(vector<vector<int> > adj, vector<vector<double> > weights)
{
  double result = 0.;

  priority_queue<pair<int, double>, vector<pair<int, double> >, ComparePrims> pq;

  vector<double> cost(adj.size(), numeric_limits<double>::max());

  // We want to begin with the first element
  cost[0] = 0.;

  int current = 0;

  pq.push(make_pair(current, cost[current]));

  while(!pq.empty())
  {
    current = pq.top().first;

    pq.pop();

    for(int i=0; i<adj[current].size(); i++)
    {
      // Relax all vertices neighbouring current
      if (cost[adj[current][i]] > weights[current][i])
      {
        cost[adj[current][i]] = weights[current][i];

        pq.push(make_pair(adj[current][i], weights[current][i]));
      }
    }
  }

  for (int i=0; i<cost.size(); i++)
  {
    result += cost[i];
  }

  return result;
}

int main()
{
  size_t n;
  std::cin >> n;

  vector<double> x(n), y(n);
  for (size_t i = 0; i < n; i++)
  {
    std::cin >> x[i] >> y[i];
  }

  cout << fixed << "\nKruskal outputs ";

  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;

  vector<vector<int> > adj(x.size(), vector<int>());

  vector<vector<double> > weights(x.size(), vector<double>());

  for (int i=0; i<x.size(); i++)
  {
    for (int j=0; j<x.size(); j++)
    {
      if (i == j) continue;

      // Each element has an edge with every other element
      adj[i].push_back(j);

      adj[j].push_back(i);

      double distance = getDistance(x, y, i, j);

      weights[i].push_back(distance);

      weights[j].push_back(distance);
    }
  }

  cout << "\nPrims outputs ";

  std::cout << std::setprecision(10) << prims(adj, weights) << std::endl;
}
