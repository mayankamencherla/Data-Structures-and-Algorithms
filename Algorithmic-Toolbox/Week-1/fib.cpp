#include <iostream>

// contains solution to fast solution of fibonocci sequence

int calc_fib(int n) {
    int F[n];
	
	F[0] = 0;
	F[1] = 1;
	
	for(int i=2; i<=n; i++){
		F[i] = F[i-1] + F[i-2];
	}
	
	return F[n];
}

int main() {
    int n = 0;
    std::cin >> n;

    std::cout << calc_fib(n) << '\n';
    return 0;
}
