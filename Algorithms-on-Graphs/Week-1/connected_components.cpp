#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(vector<int>& visited, vector<vector<int> > &adj,int x){
	visited[x] = 1;
	for(int i=0; i<adj[x].size(); ++i){
		if( visited[adj[x][i]] == 0 )
			explore(visited,adj,adj[x][i]);
	}
}

int number_of_components(vector<vector<int> > &adj) {
  vector<int> visited(adj.size(),0); // creating bool matrix of size n;
  int cc = 0; // initially number of components = 0
  
  for(int i=0; i<adj.size(); ++i){
	  if(visited[i] == 0){
		  explore(visited,adj,i);
		  cc++; // everytime a depth first search ends, num components ++
	  }
  }
  
  return cc; // the total number of connected components
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
  std::cout << number_of_components(adj);
}
