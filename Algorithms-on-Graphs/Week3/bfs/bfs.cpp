#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

using namespace std;

void bfs(vector<vector<int> > &adj, int s, vector<int>& dist, vector<int>& parent)
{
  queue<int> discovered;

  discovered.push(s);

  dist[s] = 0; int current;

  while (!discovered.empty())
  {
    current = discovered.front();

    discovered.pop();

    for (int i=0; i<adj[current].size(); i++)
    {
      if (dist[adj[current][i]] == -1)
      {
        discovered.push(adj[current][i]);

        dist[adj[current][i]] = dist[current] + 1;

        parent[adj[current][i]] = current;
      }
    }
  }
}

void printPath(vector<int> parent, int s, int t)
{
  int current = t;

  vector<int> path;

  path.insert(path.begin(), t);

  while (current != s)
  {
    path.insert(path.begin(), parent[current]);

    current = parent[current];
  }

  for (int i=0; i<path.size(); i++)
  {
    cout << path[i] + 1 << " ";
  }

  cout << endl;
}

int distance(vector<vector<int> > &adj, int s, int t)
{
  vector<int> dist(adj.size(), -1);

  vector<int> parent(adj.size(), -1);

  bfs(adj, s, dist, parent);

  if (dist[t] != -1)
    cout << "We discovered " << t+1 << " via ";

  printPath(parent, s, t);

  cout << endl;

  return dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
