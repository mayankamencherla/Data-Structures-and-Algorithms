#include <iostream>

 // code computes the last digit of any fibonacci number, even large ones

long long get_fibonacci_last_digit(int n) {
  //write your code here
    long long F[n];
	
	F[0] = 0;
	F[1] = 1;
	
	for(int i=2; i<=n; i++){
		F[i] = (F[i-1] + F[i-2])%10;
	}
	
  return F[n];
}

int main() {
  int n;
  std::cin >> n;
  int c = get_fibonacci_last_digit(n);
  std::cout << c << '\n';
}
