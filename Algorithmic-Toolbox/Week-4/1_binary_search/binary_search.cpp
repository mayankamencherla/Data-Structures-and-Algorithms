#include <iostream>
#include <cassert>
#include <vector>
#include <math.h>

using std::vector;

using namespace std;

int binary_search(const vector<int> &a, int x, int low, int high)
{
  if (low > high) return -1;

  int mid = floor((low + high) / 2);

  if (a[mid] == x) return mid;

  else if (a[mid] > x) return binary_search(a, x, low, mid-1);

  return binary_search(a, x, mid+1, high);
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main()
{
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++)
  {
    std::cin >> a[i];
  }

  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i)
  {
    std::cin >> b[i];
  }

  for (int i = 0; i < m; ++i)
  {
    //replace with the call to binary_search when implemented
    // std::cout << linear_search(a, b[i]) << ' ';
    std::cout << binary_search(a, b[i], 0, a.size()-1) << ' ';
  }

  cout << endl;
}
