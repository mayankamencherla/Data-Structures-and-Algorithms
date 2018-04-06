#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <map>
#include <queue>
#include <limits>

using namespace std;

using std::vector;
using std::pair;

class DisjointSet
{
  private:
    // Mapping vertex to parent
    map<int, int> dset;

    int clusters;

  public:
    DisjointSet(int size)
    {
      for (int i=0; i<size; i++)
      {
        dset[i] = i;
      }

      clusters = size;
    }

    int find(int i)
    {
      // Getting the parent of i
      return dset[i];
    }

    void merge(int i, int j)
    {
      int parentOfI = find(i);

      int parentOfJ = find(j);

      if (parentOfI == parentOfJ) return;

      map<int, int>::iterator it;

      for(it=dset.begin(); it!=dset.end(); it++)
      {
        // Setting all vertices belonging to J's
        // set to be in I's set
        if (it->second == parentOfJ)
          it->second = parentOfI;
      }

      // Every merge results in 1 less cluster
      clusters--;
    }

    int getNumClusters()
    {
      return clusters;
    }

    void printClusters()
    {
      map<int, int>::iterator it;

      cout << "We currently have " << clusters << " clusters" << endl;

      for(it=dset.begin(); it!=dset.end(); it++)
        cout << it->first << " " << it->second << endl;;

      cout << endl;
    }
};

class Compare
{
  public:
    bool operator()(pair<pair<int, int>, double> p1, pair<pair<int, int>, double> p2)
    {
      // We want to build a min heap based pq
      // which means we return true if p1 has a higher weight than p2
      // that will push p1 below p2 in the priority queue
      return p1.second > p2.second;
    }
};

double getDistance(vector<int> x, vector<int> y, int i, int j)
{
  return sqrt(pow(abs(x[i] - x[j]), 2) + pow(abs(y[i] - y[j]), 2));
}

priority_queue<pair<pair<int, int>, double>,
                 vector<pair<pair<int, int>, double> >,
                 Compare>
    computeWeights(vector<int> x, vector<int> y)
{
  priority_queue<pair<pair<int, int>, double>,
                 vector<pair<pair<int, int>, double> >,
                 Compare>
                 pq;

  for (int i=0; i<x.size(); i++)
  {
    for (int j=i+1; j<x.size(); j++)
    {
      double distance = getDistance(x, y, i, j);

      pq.push(make_pair(make_pair(i, j), distance));
    }
  }

  return pq;
}

double Kruskal(vector<int> x, vector<int> y, int k)
{
  priority_queue<pair<pair<int, int>, double>,
                 vector<pair<pair<int, int>, double> >,
                 Compare>
                 pq = computeWeights(x, y);

  // We create a disjoint set with all vertices
  DisjointSet dset(x.size());

  double distance = -1.;

  pair<pair<int, int>, double> current;

  int pt1, pt2;

  while (!pq.empty())
  {
    current = pq.top();

    pq.pop();

    distance = current.second;

    pt1 = current.first.first;

    pt2 = current.first.second;

    if (dset.find(pt1) != dset.find(pt2))
    {
      // If the edge doesn't produce a cycle
      dset.merge(pt1, pt2);
    }

    //
    // We found the edge that has reduced the number
    // of clusters to k-1. All other edges will have
    // weight greater than d. All the other edges
    // will also connect and reduce clusters,
    // but we found the minimum distance that seperates
    // all k clusters, as all clusters are seperated
    // by the edges remaining in the pq, and the edge
    // we just found is the smallest among them,
    // which means this distance is the smallest distance
    // between each pair of vertices in k clusters
    //
    if (dset.getNumClusters() == k-1)
      break;
  }

  // dset.printClusters();

  return distance;
}

double clustering(vector<int> x, vector<int> y, int k)
{
  return Kruskal(x, y, k);
}

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;

  //
  // During Kruskal, we always extract the minimum weight edge in the
  // graph whose vertex does not produce a cycle. At the start, there are
  // as many clusters as there are vertices. With k clusters, we will
  // have all the edges that are the smallest weight to form k clusters.
  // The next edge to be extracted from the queue will have a weight w.
  // All the remaining edges in the queue will have a weight greater than
  // or equal to w. All the edges discovered thus far will have weight
  // less than or equal to w. For Kruskal to converge, we must reduce
  // all k clusters to 1 cluster forming an MST. To be able to do that,
  // we must join all the clusters by the corresponding edges. Since we
  // know that at this point, all edges are >= w in weight, for each
  // cluster to join any of the other cluster, the edge selected must have
  // a weight of at least d. Therefore, this is how we can compute d
  //

  cout << fixed;

  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
