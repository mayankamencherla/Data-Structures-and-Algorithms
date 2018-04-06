#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

using namespace std;

int isBipartite(vector<vector<int> > &adj, int s, vector<int> colors)
{
  queue<int> bfs;

  bfs.push(s);

  // Color the first node white
  colors[s] = 0;

  int current;

  while (!bfs.empty())
  {
    current = bfs.front();

    bfs.pop();

    for (int i=0; i<adj[current].size(); i++)
    {
      if (colors[adj[current][i]] == -1)
      {
        // XOR
        colors[adj[current][i]] = colors[current] ^ 1;

        bfs.push(adj[current][i]);
      }
      else if (colors[adj[current][i]] == colors[current])
      {
        // If parent and node that is discovered have the same
        // color, then we know that this graph cannot be bipartite
        return 0;
      }
    }
  }

  return 1;
}

int bipartite(vector<vector<int> > &adj)
{
  // Initially all colored -1
  vector<int> colors(adj.size(), -1);

  return isBipartite(adj, 0, colors);
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
