#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(vector<vector<int> > &adj, int x, vector<int>& visited)
{
  visited[x] = 1;

  for (int i=0; i<adj[x].size(); i++)
  {
    if (visited[adj[x][i]] == 0)
      explore(adj, adj[x][i], visited);
  }
}

int reach(vector<vector<int> > &adj, int x, int y)
{
  vector<int> visited(adj.size(), 0);

  explore(adj, x, visited);

  return visited[y];
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
