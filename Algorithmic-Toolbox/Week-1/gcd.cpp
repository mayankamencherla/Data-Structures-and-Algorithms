#include <iostream>

// This function computes the greatest common divisor of 2 numbers very quickly using the Euclidean algorithm

int gcd(int a, int b) {
  //write your code here
  if(b==0) return a;
  
  int a_prime = a%b;
  
  return gcd(b,a_prime);
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd(a, b) << std::endl;
  return 0;
}
