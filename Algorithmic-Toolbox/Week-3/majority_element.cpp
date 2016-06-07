#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>

using std::vector;

int getFrequency(vector<int> &a, int element){
	// we want to count number of occurences of element between left and right
	int count = 0;
	
	for(int i=0; i< a.size(); i++){
		if(a[i] == element) count++;
	}
	
	// instead of scanning whole array we need to scan just
	// left to right to reduce time complexity
	//std::cout << count << ' ';
	return count;
}

int get_majority_element(vector<int> &a, int left, int right) {
	
	if (left == right) return -1; // Base case
	
	// returns the majority element of the base case when subarray is of length 1
	if (left + 1 == right) return a[left]; 
	
	//write your code here
	int mid = floor((left+right)/2);
	int major_left = get_majority_element(a,left,mid);
	int major_right = get_majority_element(a,mid+1,right);
	
	// both are the same then return one of them
	if( major_left == major_right) return major_left;
	
	// count of each majority element in the recursive subproblem
	int lcount = getFrequency(a,major_left);
	int rcount = getFrequency(a,major_right);
	
	// now if the count is greater than mid +1 , then we have a major element
	if(lcount >= mid+1) return major_left; // theres a count error here
	
	else if (rcount >= mid+1) return major_right;
	
	return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
