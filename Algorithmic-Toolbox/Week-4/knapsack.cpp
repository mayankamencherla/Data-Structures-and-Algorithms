#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  vector < vector<int> > value(w.size()+1, vector <int>(W+1));
  
  int val = 0;
  // each weight is only 1 quantity, and we need to optimize
  // the weights in the bag
  // therefore the values are just 1
  
  for(int j=0; j<=w.size(); j++) value[j][0] = 0;
  for(int i=0; i<=W; i++) value[0][i] = 0;
  
  for( int i=1; i<=w.size(); i++){
	  for(int j=1; j<=W; j++){
		  value[i][j] = value[i-1][j];
		  if(w[i-1]<=j){
			  val = value[i-1][j-w[i-1]] + w[i-1]; // vi = 1 for all
			  if(value[i][j] < val){
				  value[i][j] = val;
			  }
		  }
	  }
  }
  
  return value[w.size()][W];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
