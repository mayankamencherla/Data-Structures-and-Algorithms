#include <iostream>

/*Task. The goal in this problem is to find 
 * the minimum number of coins needed to change the 
 * input value (an integer) into coins 
 * with denominations 1, 5, and 10.
 * */

int get_change(int n) {
  //write your code here
  int num_tens = n / 10;
  int num_fives = (n-num_tens*10) / 5;
  int num_ones = (n-num_tens*10 -num_fives*5);
  return num_tens + num_fives + num_ones;
}

int main() {
  int n;
  std::cin >> n;
  std::cout << get_change(n) << '\n';
}
