#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bfs(vector<vector<int> > &adj, int s, vector<int> &color) {
	queue<int> Q;
	
	for (int i=0; i<adj.size(); ++i)
		color[i] = adj.size() +1; // like infinity for unexplored vertices
		
	color[s] = 0;
	Q.push(s); // initially
	
	while( !Q.empty() ){
		int u = Q.front();
		Q.pop(); // dequeue
		
		for(int i=0; i<adj[u].size(); ++i){
			if(color[adj[u][i]] == adj.size() +1){ // if unexplored
				Q.push(adj[u][i]);
				color[adj[u][i]] = color[u] ^ 1; // xor
			}
			
			else{ // if explored
				if(color[adj[u][i]] == color[u]) // if they have same color
					return 0; // break and return not bipartate
			}
		}
	}
	
	return 1;
}

int bipartite(vector<vector<int> > &adj) {
  //write your code here
  vector<int> color(adj.size(),0); // 0 is white, 1 is black
  return bfs(adj,0,color);
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
