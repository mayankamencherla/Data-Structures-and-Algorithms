#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

class TreeHeight {
  long long n;             
  std::vector<long long> parent;
  std::vector< std::vector <long long> > Tree;
  std::vector<long long> heights;
  long long root; //  to keep track of size of Tree

public:
  void read() {
    std::cin >> n;
    parent.resize(n);
	heights.resize(n); // creating a dynammic programming solution of size n

    for (long long i = 0; i < n; i++)
      std::cin >> parent[i];
  }

  long long compute_height() {
    // Replace this code with a faster implementation
    long long maxHeight = 0;
    for (long long vertex = 0; vertex < n; vertex++) {
      long long height = 0;
      for (long long i = vertex; i != -1; i = parent[i])
        height++;
      maxHeight = std::max(maxHeight, height);
    }
    return maxHeight;
  }
  
  /*My algo is as follows:
   * Build Tree
   * Tree[ind][:] gives children of node ind
   * if Tree[ind] == 0, then it has no children
   * Go through this and fill up the height matrix
   * */
  
  void buildTree(){
	  //successfully built the tree
	  Tree.resize(n);
	  //std::cout << Tree.size() ;
	  
	  for(long long i=0; i<n; i++){
		  long long par = parent[i]; // we have i's parent node
		  
		  if(par!=-1) {
			  Tree[par].push_back(i);
		  }
		  
		  else root = i; // now we have set the root as well
		}
		
  }
  
  long long fast_height(){
	  buildTree(); // builds our Tree vector and we have root
	  return fast_height(root);
  }
  
  long long fast_height(long long index){
	  // we start at root index
	  if(Tree[index].size()==0) return 1; // the case where only the root exists
	  int max_height = 0;
	  for(long long i=0; i<Tree[index].size(); i++){
		  // returns max height at every level
		  int height = 1 + fast_height(Tree[index][i]);
		  if (max_height < height) max_height = height;
	  }
	  
	  return max_height;
  }
  

};

int main() {
  std::ios_base::sync_with_stdio(0);
  TreeHeight tree;
  tree.read();
  std::cout << tree.fast_height() << std::endl;
}
