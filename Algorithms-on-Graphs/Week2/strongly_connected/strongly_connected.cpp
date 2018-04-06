#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <ctime>

using std::vector;
using std::pair;

using namespace std;

void exploreSCC(int u,
             vector<vector<int> >& adj,
             vector<bool>& visited,
             vector<bool>& black)
{
  visited[u] = true;

  for (int i=0; i<adj[u].size(); i++)
  {
    if (black[u] == true) continue;

    if (visited[adj[u][i]] == false)
      exploreSCC(adj[u][i], adj, visited, black);
  }

  black[u] = true;
}

void explore(int u,
             vector<vector<int> >& adj,
             vector<bool>& visited,
             vector<bool>& black,
             stack<int>& postOrder)
{
  visited[u] = true;

  for (int i=0; i<adj[u].size(); i++)
  {
    if (black[adj[u][i]] == true) continue;

    if (visited[adj[u][i]] == false)
      explore(adj[u][i], adj, visited, black, postOrder);
  }

  black[u] = true;

  postOrder.push(u);
}

void DFS(vector<vector<int> > adj, stack<int>& postOrder)
{
  vector<bool> visited(adj.size(), false);

  vector<bool> black(adj.size(), false);

  for (int i=0; i<adj.size(); i++)
  {
    if (black[i] == true) continue;

    if (visited[i] == false)
      explore(i, adj, visited, black, postOrder);
  }
}

int number_of_strongly_connected_components(vector<vector<int> > adj,
                                            vector<vector<int> > adjR)
{
  int result = 0;

  stack<int> postOrder;

  DFS(adjR, postOrder);

  vector<bool> visited(adj.size(), false);

  vector<bool> black(adj.size(), false);

  while (!postOrder.empty())
  {
    int vtx = postOrder.top();

    postOrder.pop();

    if (black[vtx] == true) continue;

    if (visited[vtx] == false)
    {
      exploreSCC(vtx, adj, visited, black);

      result++;
    }
  }

  return result;
}

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > adjR(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x; int y;

    cin >> x >> y;

    adj[x - 1].push_back(y - 1);
    adjR[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj, adjR);
}
