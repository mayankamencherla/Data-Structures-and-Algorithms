#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <math.h>
#include <limits>
#include <queue>
#include <stdio.h>

using std::vector;
using std::priority_queue;

// gets the terms to skip for the getWeight function
int sigma(int u, int n){ // n being the size of G (vertices)
	// will be used only if u is greater than or equal to 1
	int result = 0;
	for(int i=0; i<u; ++i)
		result += n-1-i;
	return result; 
}

// returns the weight on the edge between u and v
double getWeight(int u, int v, int n, vector< vector<double> > weights){
	// works
	// change this implementation to a 2D array
	return weights[u][v];
}

// sets all the weights of all the edges
void ComputeWeights(vector<int> x, vector<int> y, vector< vector<double> > &weights){
	for(int i=0; i<x.size(); ++i){
		for(int j=0; j<x.size(); ++j){
			double curr_weight = sqrt( pow(x[i]-x[j],2) + pow(y[i]-y[j],2) );
			weights[i][j] = curr_weight;
		}
	}
}

bool pqueue_contains(vector<int> popped, int z){
	for(int i=0; i<popped.size(); ++i){
		if(popped[i] == z)
			return false; // if popped has z, then prioQ doesn't
	}
	
	return true; // if popped doesn't have z, then prioQ does
}

vector<int> Prims(vector<int> x, vector<int> y, vector< vector<double> > weights){
	vector<double> cost(x.size(),std::numeric_limits<double>::max()); // 
	vector<int> parent(x.size(),-1);
	
	// pick initial vertex as 0
	cost[0] = 0.0;
	parent[0] = 0; // 0 is the parent of itself
	
	// priority queue based on min Heap
	// cmp is our priority, it is nothing but the cost of each point
	auto cmp = [&cost] (int p1, int p2) { return cost[p1] > cost[p2]; };
	std::priority_queue<int, std::vector<int>, decltype(cmp) > PrioQ(cmp);
	for(int i=0; i<x.size(); ++i)
		PrioQ.push(i); // our priority queue is made and is based on cost
	
	// Going to store an array of popped elements
	vector<int> popped;
	
	
	while(!PrioQ.empty()){
		int v = PrioQ.top();
		PrioQ.pop(); // extracting minimum priority vertex
		popped.push_back(v); // now we know that u is not part of PrioQ
		
		// for every u, v is all the points on the graph except u itself
		
		for(int i=0; i<x.size(); ++i){
			if(i != v){
				int z = i; // z is all the nodes except v
				//std::cout<< z <<std::endl;
				if(pqueue_contains(popped,z) && cost[z] > getWeight(v,z,x.size(),weights)){
					cost[z] = getWeight(v,z,x.size(),weights);
					parent[z] = v;
				}
				
				//std::cout << "Get Weight " << v << ' ' << z << ' ' << cost[z]<<std::endl;
			}
		}
	}
	
	return parent;
}

double ComputeDistance(int s, vector<int> x, vector<int> y, vector<int> parent){
	// s is always 0 in my assumption
	double distance =0.0;
	
	for(int i=1; i<parent.size(); ++i){
		int curr_parent = parent[i];
		distance += sqrt( pow(x[i]-x[curr_parent],2) + pow(y[i]-y[curr_parent],2) );
	}
	
	return distance;
}

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.0;
  //write your code here
  vector< vector<double> > weights (x.size(),vector<double>(x.size())); 
  ComputeWeights(x,y,weights);
  //std::cout<< getWeight(0,3,x.size(),weights); //This doesn't work check sigma
  vector<int> parent = Prims(x,y,weights);
  
  /*for(int i=0; i<parent.size(); ++i)
	  std::cout<<parent[i] << ' ';
  std::cout<<'\n';*/
  
  // Now, to use parent array to get the distance from start point to end point
  result = ComputeDistance(0,x,y,parent);
  
  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  
  /*size_t n = 200;
  vector<int> x(n),y(n);
  for(size_t i = 0; i < n; i++){
	  x[i] = rand()%2001 - 1000; // number between -1000 and 1000
	  y[i] = rand()%2001 - 1000;
  }*/
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
