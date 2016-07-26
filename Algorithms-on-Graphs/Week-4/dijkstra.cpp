#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::vector;

void ChangePriority(int ind, int dist, vector< pair<int,int> > &pq){
	for(int i=0; i<pq.size(); ++i){
		if(pq[i].first == ind)
			pq[i].second = dist;
	}
}

pair<int,int> ExtractMin(vector<pair<int,int> > &pq){
	int min = 1000+1;
	int min_index = 0;
	
	for(int i=0; i<pq.size(); ++i){
		if(pq[i].second < min){
			min = pq[i].second;
			min_index = i;
		}
	}
	
	pair<int,int> p = pq[min_index];
	pq.erase(pq.begin()+min_index);
	
	return p;
}

void dijsktra(vector<vector<int> > &adj, vector<vector<int> > &cost, vector<int> &dist, int s){
	vector<pair<int,int> > pq;
	
	for(int i=0; i<adj.size(); ++i){
		dist[i] = 2000;
		pq.push_back(pair<int,int>(i,dist[i]));
	}
	
	dist[s] = 0; // initially
	
	ChangePriority(s,0,pq);
	
	while(!pq.empty()){
		pair<int,int> p = ExtractMin(pq);
		
		for(int i=0; i<adj[p.first].size(); ++i){
			if(dist[adj[p.first][i]] > dist[p.first] + cost[p.first][i]){
				dist[adj[p.first][i]] = dist[p.first] + cost[p.first][i];
				ChangePriority(adj[p.first][i],dist[adj[p.first][i]],pq);
			}
		}
	}
}

int relax(int u, int v, vector<int> &dist, vector<vector<int> > &cost){
	if(dist[v] > dist[u] + cost[u][v])
		dist[v] = dist[u] + cost[u][v];
}

void dijsktra_naive(vector<vector<int> > &adj, vector<vector<int> > &cost, vector<int> &dist, int s){
	for(int i=0; i<adj.size(); ++i){
		dist[i] = 2000;
	}
	
	dist[s] = 0; // initially
	
	for(int i=0; i<adj.size(); ++i){
		for(int j=0; j<adj[i].size(); ++j){
			int v = adj[i][j];
			relax(i,v,dist,cost);
		}
	}
}

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
  vector<int> dist(adj.size(),0);
  dijsktra(adj,cost,dist,s);
  if(dist[t] != 2000) return dist[t];
  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
