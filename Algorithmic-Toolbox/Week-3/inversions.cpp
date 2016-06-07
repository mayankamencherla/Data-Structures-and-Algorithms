#include <iostream>
#include <vector>

using std::vector;

// This is a mergesort algorithm that also counts
// the number of inversions in the array to be sorted

long long Merge(vector<int> &a, vector<int> &b, size_t left, size_t ave, size_t right) {
	// This function takes in a and left, right and center and merges 
	//a[left...ave;] to a[ave...right]
	//vector<int> d(right-left); // size of new array d
	
	// have two counters, i from left to ave-1 
	//and j from ave to right-1
	// we have another, k for value of b's index
	int i = left; int j = ave; int k = left;
	
	// we have inversion count as well
	long long inv_count = 0;
	
	while( i<=ave-1 && j<=right){
		if(a[i]<=a[j]){
			b[k++] = a[i++]; // it is moved to b
			// both k and i increase
		}
		
		else{
			b[k++] = a[j++];
			inv_count +=  ave - i; // this is the inversion case
		}
	}
	
	while(i<=ave-1){
		// this case happens when right subarray is fully sorted first
		b[k++] = a[i++]; // copy over if anything is left
	}
	
	while(j<=right){
		// this case happens when left subarray sorted
		b[k++] = a[j++];
	}
	
	// now we gotta copy over all the elements back to a
	
	for(int i= left; i<=right; i++){
		a[i] = b[i];
	}
	
	return inv_count;
}


long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
  
	long long number_of_inversions = 0;
  
	if (right <= left ) return number_of_inversions;
	
	size_t ave = (right + left) / 2;
	
	number_of_inversions = get_number_of_inversions(a, b, left, ave);
	number_of_inversions += get_number_of_inversions(a, b, ave+1, right);
	//write your code here
	//b = a; // we copy a to b each call and will sort it in Merge
	// we want to sort b[left...ave-1] and b[ave...right-1]
	number_of_inversions += Merge(a,b,left,ave+1,right);
	
	return number_of_inversions;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size()); // b is a vector of size a.size and filled with 0s
  std::cout << get_number_of_inversions(a, b, 0, a.size()-1) << '\n';
}
