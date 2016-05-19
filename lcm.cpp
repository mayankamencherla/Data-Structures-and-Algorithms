#include <iostream>

int gcd(int a, int b){
	if(b==0) return a;
	
	int a_prime = a%b;
	return gcd(b,a_prime);
}


long long lcm(int a, int b) {
  //write your code here
  return (long long)(a)*b/gcd(a,b);
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm(a, b) << std::endl;
  return 0;
}
