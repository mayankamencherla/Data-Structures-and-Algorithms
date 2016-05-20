#include <iostream>

/* This file contains a solution to a modulo of a 
 * Fibonacci number Fn mod m when n and m are very large
 * */

long long get_fibonaccihuge(long long n, long long m) {
  //write your code here
	// Using these 3 variables to save space
	long long Fi0 = 0;
	long long Fi1 = 1;
	long long Fi2 = 0;
	
	long long pi =0;
	
	for(long long i=0; i<m*m-1; i++){
		//std::cout << Fi[i] << ' ';
		if(i>=2 && Fi0%m==0 && Fi1%m==1) break;

		Fi2 = (Fi0%m + Fi1%m)%m;
		Fi0 = Fi1;
		Fi1 = Fi2;
		pi++;
	}
	
	// pi now contains the pisano period
	// now Fn mod m = Fr mod m, where r = n mod pi;
	
	long long Fi[pi];			// we only need pi
	Fi[0] = 0; Fi[1] = 1;
	
	for(int j=0; j<pi; j++){
		Fi[j+2] = ( Fi[j]%m + Fi[j+1]%m ) %m;
	}
	
	return (Fi[n%pi]);
	
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonaccihuge(n, m) << '\n';
}
