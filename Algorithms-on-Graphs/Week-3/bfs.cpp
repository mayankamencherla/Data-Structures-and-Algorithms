#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

void bfs(vector<vector<int> > &adj, int s, vector<int> &dist) {
	queue<int> Q;
	
	for (int i=0; i<adj.size(); ++i)
		dist[i] = adj.size() +1; // like infinity
		
	dist[s] = 0;
	Q.push(s); // initially
	
	while( !Q.empty() ){
		int u = Q.front();
		Q.pop(); // dequeue
		
		for(int i=0; i<adj[u].size(); ++i){
			if(dist[adj[u][i]] == adj.size() +1){
				Q.push(adj[u][i]);
				dist[adj[u][i]] = dist[u] + 1;
			}
		}
	}
}

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  vector<int> dist(adj.size(),0);
  bfs(adj,s,dist);
  if(dist[t] != adj.size()+1) return dist[t];
  return -1;
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
