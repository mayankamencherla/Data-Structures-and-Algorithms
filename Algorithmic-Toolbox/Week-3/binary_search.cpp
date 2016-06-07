#include <iostream>
#include <cassert>
#include <vector>
#include <math.h>

/* Task. The goal in this code problem is to implement the binary search algorithm.

 * Input Format. The first line of the input contains an integer n and a sequence a0 < a1 < : : : < an-1 of
n pairwise distinct positive integers in increasing order. The next line contains an integer k and k
positive integers b0; b1; : : : ; bk-1.

 * 
 * Output Format. For all i from 0 to k -1, output an index 0 <= j <= n -1 such that aj = bi or -1 if there
is no such index.
 * */
 
using std::vector;

int binary_search(const vector<int>&a, int low, int high, int key){
	
	// this code works for sorted array a
	int mid;
	
	if (high<low) return -1; // when element not in array
	
	// floor imported from math.h
	mid = floor((low+high)/2); // consider mid point
	
	if (key == a[mid]) return mid; // key found at mid index
	
	// key is less than mid, then key is in left half
	else if ( key < a[mid]) return binary_search(a,low,mid-1,key);
	
	// key is greater than mid, then key is in right half
	else return binary_search(a,mid+1,high,key);
}

int binary_search(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size(); 
  //write your code here
  
  // we call helper function
  // it takes in a, left, right and key to be searched, in this case x
  return binary_search(a,left,right,x);
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    //std::cout << linear_search(a, b[i]) << ' ';
	
	std::cout << binary_search(a, b[i]) << ' '; // for every b[i] find it in a
  }
}
