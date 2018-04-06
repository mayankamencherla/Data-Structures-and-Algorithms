#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <math.h>
#include <algorithm>
#include <stdlib.h>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

using namespace std;

bool relax(int s, int t, long long cost, vector<long long> &distance)
{
  // We want to avoid overflows when max + cost is computed
  if (distance[s] == numeric_limits<long long>::max())
    return false;

  if (distance[t] > distance[s] + cost)
  {
    distance[t] = distance[s] + cost;

    return true;
  }

  return false;
}

void bfs(vector<vector<int> > &adj, queue<int> cycles, vector<int> &shortest, vector<bool> &visited)
{
  while (!cycles.empty())
  {
    int current = cycles.front();

    cycles.pop();

    shortest[current] = 0;

    visited[current] = true;

    // Check all the neighbours of current
    for (int i=0; i<adj[current].size(); i++)
    {
      if (!visited[adj[current][i]])
      {
        cycles.push(adj[current][i]);
      }
    }
  }
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<long long> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest)
{
  // S is reachable to itself
  distance[s] = 0; reachable[s] = 1;

  // V - 1 iterations of the loop going over all edges
  for (int i=0; i<adj.size()-1; i++)
  {
    // All edges
    for (int j=0; j<adj.size(); j++)
    {
      for (int k=0; k<adj[j].size(); k++)
      {
        if (relax(j, adj[j][k], cost[j][k], distance))
        {
          reachable[adj[j][k]] = 1;
        }
      }
    }
  }

  queue<int> reachableFromNegCycle;

  vector<bool> visited(adj.size(), false);

  // Vth iteration we compute all vertices reachable from neg cycle
  for (int j=0; j<adj.size(); j++)
  {
    for (int k=0; k<adj[j].size(); k++)
    {
      if (visited[adj[j][k]]) continue;

      if (relax(j, adj[j][k], cost[j][k], distance))
      {
        // Since this node was relaxed in the Vth iteration
        // it is reachable from a neg cycle
        reachableFromNegCycle.push(adj[j][k]);

        visited[adj[j][k]] = true;
      }
    }
  }

  // Do a BFS and mark all vertices that are reachable from a neg cycle
  // This helps us know the vts that are capable of infinite arbitrage
  bfs(adj, reachableFromNegCycle, shortest, visited);

  distance[s] = 0;
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<long long> > cost(n, vector<long long>());
  for (int i = 0; i < m; i++) {
    int x, y;
    long long w;

    std::cin >> x >> y >> w;

    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
