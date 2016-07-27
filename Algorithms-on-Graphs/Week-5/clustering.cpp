#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <math.h>

using std::vector;
using std::pair;

struct DisjointSetElement{
	int size, parent, rank;
	
	DisjointSetElement(int size=0, int parent = -1, int rank = 0):
		size(size), parent(parent), rank(rank) {} // constructor
};

struct DisjointSet{
	int size;
	vector<DisjointSetElement> set;
	
	DisjointSet(int size) : size(size), set(size){
		for(int i=0; i<size; ++i)
			set[i].parent = i; // each element initialized to itself (parent)
	}
	
	int getParent(int i){ // find operation
		if(i != set[i].parent)
			set[i].parent = getParent(set[i].parent);
			
		return set[i].parent;
	}
	
	void merge(int destination, int source){
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		
		if(realDestination != realSource){
			// if both of them have different parents
			// set sources parent as the destination
			
			set[realSource].parent = set[realDestination].parent;
			
			set[realDestination].size += set[realSource].size;
			
			set[realSource].size = 0; // we now have a case where source is emptied
		}
	}
};

struct Edges{
	int node1, node2;
	double weight;
	
	Edges(int node1=-1, int node2=-1, double weight=-1):
		node1(node1), node2(node2), weight(weight) {};
};

bool compareByweight (Edges &edge1, Edges &edge2){
	// just remember that by returning edge2.weight > we have a ascending order in sort
	return edge1.weight < edge2.weight ;
}

int xChoose2(int x){
	// to compute number edges needed for us
	// equal to x*(x-1)/2
	return x*(x-1)/2;
}

// sets all the weights of all the edges
double ComputeWeight(vector<int> x, vector<int> y, int i, int j){
	double curr_weight = sqrt( pow(x[i]-x[j],2) + pow(y[i]-y[j],2) );
	return curr_weight;
}

void ComputeEdges(vector<Edges> &edges, vector<int> x, vector<int> y){
	int count =0;
	for(int i=0; i<x.size(); ++i){
		for(int j=i+1; j<x.size(); ++j){
			double weight = ComputeWeight(x,y,i,j);
			edges[count].node1 = i;
			edges[count].node2 = j;
			edges[count].weight = weight;
			count ++;
		}
	}
}

vector<Edges> Kruskal(vector<int> x, vector<int> y, vector<Edges> edges, DisjointSet &Vertices){ 
	// returns MST as a vector
	// edges already sorted in ascending order
	vector<Edges> MST; // add each edge from our edges based on Kruskal
	while(!edges.empty()){
		int n1 = edges[0].node1;
		int n2 = edges[0].node2;
		if(Vertices.getParent(n1) != Vertices.getParent(n2)){
			MST.push_back(edges[0]);
			Vertices.merge(n1,n2);
		}
		
		edges.erase(edges.begin());
	}
	return MST;
}

double distance(DisjointSet Vertices, vector<Edges> MST){
	double result = 0;
	for(int i=0; i<MST.size(); ++i){
		result += MST[i].weight;
	}
}

double clustering(vector<int> x, vector<int> y, int k) {
  //write your code here
  vector<Edges> edges(xChoose2(x.size()));
  //std::cout << edges.size() << std::endl;
  ComputeEdges(edges,x,y); // gets all the edges for the given vertices
  // edges now contains the entire data set in adj, weight form!!!
  // now I will sort the edges in ascending order for Kruskal
  std::sort(edges.begin(),edges.end(),compareByweight);
  DisjointSet Vertices(x.size()); // all the vertices as sets with initial parent = i
  vector<Edges> MST = Kruskal(x,y,edges,Vertices); // works
  return distance(Vertices,MST);
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
