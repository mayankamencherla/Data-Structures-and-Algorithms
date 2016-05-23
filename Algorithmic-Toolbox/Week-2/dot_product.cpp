#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

/*Task: The goal is, given two sequences a1,a2.. an 
 * and b1,b2.. bn, find a permutation of the second
sequence such that the dot product of a and b is minimum.
 * */

long long min_dot_product(vector<long long> a, vector<long long> b) {
  // write your code here
  long long result = 0;
  std::sort(b.begin(),b.end()); // ascending order
  std::sort(a.begin(),a.end(),std::greater<long long>()); // descending
  
  for (size_t i = 0; i < a.size(); i++) {
    result += a[i] * b[i];
  }
  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<long long> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << min_dot_product(a, b) << std::endl;
}
