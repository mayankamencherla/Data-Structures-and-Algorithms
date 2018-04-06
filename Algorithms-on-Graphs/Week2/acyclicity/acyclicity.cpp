#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using namespace std;

void hasCycle(vector<vector<int> > &adj, int u, vector<int>& grey, bool& cycle)
{
  grey[u] = 1;

  for (int i=0; i<adj[u].size(); i++)
  {
    if (grey[adj[u][i]] == 1)
    {
      // We have found a node via DFS that is discovered,
      // and all its neighbors are still not fully discovered
      cycle = true;

      break;
    }

    hasCycle(adj, u, grey, cycle);
  }

  // We discovered all of u's neighbours
  grey[u] = 0;
}

int acyclic(vector<vector<int> > &adj)
{
  bool cycle = false;

  for (int i=0; i<adj.size(); i++)
  {
    // Being visited now
    vector<int> grey(adj.size(), 0);

    hasCycle(adj, i, grey, cycle);

    if (cycle) return 1;
  }

  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }

  std::cout << acyclic(adj);
}
