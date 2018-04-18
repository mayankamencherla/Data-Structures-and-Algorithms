#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using std::vector;
using std::swap;

using namespace std;

int partition2(vector<int> &a, int l, int r)
{
  int x = a[l];
  int j = l;

  for (int i = l + 1; i <= r; i++)
  {
    if (a[i] <= x)
    {
      j++;
      swap(a[i], a[j]);
    }
  }

  swap(a[l], a[j]);
  return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r)
{
  if (l >= r)
  {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  int m = partition2(a, l, r);

  randomized_quick_sort(a, l, m - 1);
  randomized_quick_sort(a, m + 1, r);
}

vector<int> partition3(vector<int>& a, int l, int r)
{
  vector<int> m(2, 0);

  // [ <= x | == x | > x ]
  int i, m1 = l, m2 = l;

  int x = a[l];

  for (int i=l+1; i<=r; i++)
  {
    if (a[i] < x)
    {
      m2++; m1++;

      swap(a[i], a[m2]);

      swap(a[m1], a[m2]);
    }
    else if (a[i] == x)
    {
      m2++;

      swap(a[m2], a[i]);
    }
  }

  m[0] = m1; m[1] = m2;

  // Swap a[l] with a[m1]
  swap(a[l], a[m1]);

  return m;
}

void randomized_quick_sort3(vector<int>& a, int l, int r)
{
  if (l >= r) return;

  // Random number between [l, r]
  // rand()%n gives between [0, n-1]

  int k = (rand() % (r-l+1)) + l; // [l, r]

  // Push pivot to the first element
  swap(a[k], a[l]);

  // Returns [m1, m2]
  vector<int> m = partition3(a, l, r);

  randomized_quick_sort3(a, l, m[0]-1);

  randomized_quick_sort3(a, m[1]+1, r);
}

void testQuickSort()
{
  int n;

  int pow9 = pow(10, 9);

  int pow5 = pow(10, 5);

  n = rand() % pow5 + 1;

  vector<int> a(n, 0);

  vector<int> b(n, 0);

  int val;

  for (int i=0; i<a.size(); i++)
  {
    val = rand() % pow9 + 1;

    a[i] = val;

    b[i] = val;
  }

  randomized_quick_sort(a, 0, a.size()-1);

  randomized_quick_sort3(b, 0, b.size()-1);

  for (int i=0; i<a.size(); i++)
  {
    cout << a[i] << " " << b[i] << endl;

    if (a[i] != b[i])
    {
      cout << "QuickSort 3 is broken" << endl;
    }
  }
}

int main()
{
  // testQuickSort();

  int n;
  std::cin >> n;
  vector<int> a(n);

  for (size_t i = 0; i < a.size(); ++i)
  {
    std::cin >> a[i];
  }

  // randomized_quick_sort(b, 0, a.size() - 1);

  randomized_quick_sort3(a, 0, a.size() - 1);

  for (size_t i = 0; i < a.size(); ++i)
  {
    std::cout << a[i] << ' ';
  }

  cout << endl;
}
