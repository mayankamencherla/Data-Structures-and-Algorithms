#include <iostream>
#include <vector>

using std::vector;

/*Task. The goal of this problem is to represent a given positive integer n as a sum of as many pairwise
distinct positive integers as possible. That is, to find the maximum k such that n can be written as
a1 + a2 +....+ ak where a1... ak are positive integers and ai != aj for all 1 <= i <=j <=k.
 * */
vector<int> optimal_summands(vector<int> summands,int k, int l) {
  
  while(k!=0){
	if(k<=2*l){
		l = k;
		summands.push_back(l);
		k = k - l;
	}  
	
	else{
		summands.push_back(l);
		k = k-l;
		l++;
	}
  }
  
  return summands;
}
vector<int> optimal_summands(int n) {
  vector<int> summands;
  //write your code here
  summands = optimal_summands(summands,n, 1); // starts at 1
  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
