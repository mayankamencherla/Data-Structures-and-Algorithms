#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stdlib.h>
#include <algorithm>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

using namespace std;

class Compare
{
public:
  // When does p1 come before p2?
  bool operator()(pair<int, int> p1, pair<int, int> p2)
  {
    // When dist p1 is smaller than p2
    return p1.second < p2.second;
  }
};

bool relax(int s, int t, int cost, vector<int>& dist)
{
  if (dist[s] == numeric_limits<int>::max())
    return false;

  // Reduce dist if we found a shorter path
  if (dist[t] > dist[s] + cost)
  {
    dist[t] = dist[s] + cost;

    return true;
  }

  return false;
}

void dijkstra(vector<vector<int> > &adj, vector<vector<int> > &cost, vector<int>& dist, int s)
{
  // (u, dist(u))
  priority_queue<int, vector<pair<int, int> >, Compare> pq;

  dist[s] = 0;

  pq.push(make_pair(s, dist[s]));

  int current;

  while (!pq.empty())
  {
    current = pq.top().first;

    pq.pop();

    // Relax all neighbours of current
    for (int i=0; i<adj[current].size(); i++)
    {
      int neighbour = adj[current][i];

      if (relax(current, neighbour, cost[current][i], dist))
      {
        pq.push(make_pair(neighbour, dist[neighbour]));
      }
    }
  }
}

int bellmanFord(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t)
{
  vector<int> dist(adj.size(), numeric_limits<int>::max());

  dist[s] = 0;

  // Repeat V - 1 times to update distances correctly
  for (int i=0; i<adj.size()-1; i++)
  {
    for (int j=0; j<adj.size(); j++)
    {
      for (int k=0; k<adj[j].size(); k++)
      {
        int neighbour = adj[j][k];

        int neighbourCost = cost[j][k];

        relax(j, neighbour, neighbourCost, dist);
      }
    }
  }

  if (dist[t] == numeric_limits<int>::max()) return -1;

  return dist[t];
}

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t)
{
  vector<int> dist(adj.size(), numeric_limits<int>::max());

  dijkstra(adj, cost, dist, s);

  if (dist[t] == numeric_limits<int>::max()) return -1;

  return dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << "Dijkstra outputs " << distance(adj, cost, s, t) << endl;
  cout << "Bellman Ford outputs " << bellmanFord(adj, cost, s, t) << endl;
}
