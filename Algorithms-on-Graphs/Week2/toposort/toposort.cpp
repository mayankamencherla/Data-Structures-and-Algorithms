#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;
using std::reverse;

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x)
{
  used[x] = 1;

  for (int i=0; i<adj[x].size(); i++)
  {
    if (used[adj[x][i]] == 0)
    {
      dfs(adj, used, order, adj[x][i]);
    }
  }

  order.push_back(x);
}

vector<int> toposort(vector<vector<int> > adj)
{
  vector<int> used(adj.size(), 0);
  vector<int> order;

  for (int i=0; i<adj.size(); i++)
  {
    if (used[i] == 0)
      dfs(adj, used, order, i);
  }

  reverse(order.begin(), order.end());

  return order;
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
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
