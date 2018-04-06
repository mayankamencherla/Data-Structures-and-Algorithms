#include <iostream>
#include <vector>

using std::vector;

bool relax(int s, int t, int cost, vector<int>& dist)
{
  if (dist[t] > dist[s] + cost)
  {
    dist[t] = dist[s] + cost;

    // We return true indicating that a value was updated
    return true;
  }

  return false;
}

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost)
{
  vector<int> dist(adj.size(), 10000);

  for (int i=0; i<adj.size()-1; i++)
  {
    for (int j=0; j<adj.size(); j++)
    {
      for (int k=0; k<adj[j].size(); k++)
      {
        relax(j, adj[j][k], cost[j][k], dist);
      }
    }
  }

  // Vth iteration
  for (int j=0; j<adj.size(); j++)
  {
    for (int k=0; k<adj[j].size(); k++)
    {
      if (relax(j, adj[j][k], cost[j][k], dist))
        return 1;
    }
  }

  return 0;
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
  std::cout << negative_cycle(adj, cost);
}
