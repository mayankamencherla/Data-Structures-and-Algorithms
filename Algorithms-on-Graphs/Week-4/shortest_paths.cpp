#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

bool relax(int u, int v, vector<long long> &distance, vector<int> &reachable, 
			vector<vector<int> > &cost){
	
	if(distance[v] > distance[u] + cost[u][v]){
		distance[v] = distance[u] + cost[u][v];
		reachable[v] = 1; // whenever this is reached
		return true; // we have relaxed
	}
	
	return false;
}

vector<int> bfs(vector<vector<int> > &adj, vector<int> &bfs_nodes, 
				vector<int> &shortest){
	// use bfs_nodes and perform bfs bfs_nodes.size() times
	vector<int> visited(bfs_nodes.size(),0); // initially all univisited
	
	for(int i =0; i<bfs_nodes.size(); ++i){
		queue<int> Q;
		vector<int> dist(bfs_nodes.size(),adj.size()+1);
		
		dist[bfs_nodes[i]] = 0; // at each iteration, one of them is source
		
		Q.push(bfs_nodes[i]); 
		
		while( !Q.empty() ){
			int u = Q.front();
			Q.pop(); // dequeue
			
			for(int i=0; i<adj[u].size(); ++i){
				if(dist[adj[u][i]] == adj.size() +1){
					Q.push(adj[u][i]);
					dist[adj[u][i]] = dist[u] + 1;
					visited[adj[u][i]] = 1;
				}
			}
		}
	}
	
	//std::cout << bfs_nodes.size() << std::endl;
		
	return visited;
}

vector<int> Bellman_Ford(vector<vector<int> > &adj, vector<vector<int> > &cost, 
					int s, vector<long long> &distance, vector<int> &reachable){
	distance[s] = 0;
	
	int V = adj.size();
	
	for(int i=0; i<V-1; ++i){
		for(int j=0; j<adj.size(); ++j){
			int u = j; // the nodes one by one
			
			const auto &nodes = adj[u]; // iterator for the neighbors of u
			
			for( auto v : nodes ){
				relax(u,v,distance,reachable,cost);
				//reachable[adj[u][v]] = 1;
			}
		}
	}
	
	vector<int> bfs_nodes;
	
	for(int j=0; j<adj.size(); ++j){
		int u = j; // the nodes one by one
		
		const auto &nodes = adj[u]; // iterator for the neighbors of u
		
		for( auto v : nodes ){
			if(relax(u,v,distance,reachable,cost)){
				bfs_nodes.push_back(v); // the nodes which decrease in Vth iter
				std::cout << v+1 << ' ' ;
			}
		}
	}
	
	std::cout << "\n";
	//std::cout << bfs_nodes.size() << std::endl;
	return bfs_nodes;
}


void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, 
					int s, vector<long long> &distance, vector<int> &reachable, 
					vector<int> &shortest) {
  // write your code here
  // bfs_nodes is the set A
  reachable[s] = 1; // a node is reachable from itself
  vector<int> bfs_nodes = Bellman_Ford(adj,cost,s,distance,reachable); 
  // we use bfs to remove nodes that are not reachable by any node in bfs_nodes
  vector<int> visited = bfs(adj,bfs_nodes,shortest);
  
  for(int i=0; i<visited.size(); ++i){
	  //std::cout << visited[i] << std::endl;
	  if(visited[i] == 1){
		  //std::cout << visited[i] << ' ' << bfs_nodes[i] << std::endl;
		  shortest[bfs_nodes[i]] = 0; // infinite arbitrage
		  std::cout << shortest[bfs_nodes[i]] << std::endl;
	  }
  }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
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
