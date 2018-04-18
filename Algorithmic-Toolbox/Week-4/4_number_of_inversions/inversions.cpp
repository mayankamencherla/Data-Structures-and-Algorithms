#include <iostream>
#include <vector>

using std::vector;

using namespace std;

long long Merge(vector<int>& a, size_t left, size_t mid, size_t right)
{
  long long number_of_inversions = 0;

  // Merge a[left, ..., mid] and a[mid+1, ..., right]

  int s1 = left, s2 = mid+1;

  vector<int> b(right-left+1, 0);

  int current = 0;

  // s2 represents 2nd half
  while (s1 <= mid && s2 <= right)
  {
    if (a[s1] <= a[s2])
    {
      b[current++] = a[s1++];
    }
    else
    {
      b[current++] = a[s2++];

      // All elements from s1 till mid are greater than s2
      // These are all the items that should come earlier
      // but rather they come later than they should.
      number_of_inversions += mid - s1 + 1;
    }
  }

  while (s1 <= mid && s2 > right)
  {
    b[current++] = a[s1++];
  }

  while (s2 <= right && s1 > mid)
  {
    b[current++] = a[s2++];
  }

  for (int i=left; i<=right; i++)
  {
    a[i] = b[i-left];
  }

  return number_of_inversions;
}

long long get_number_of_inversions(vector<int> &a, size_t left, size_t right)
{
  long long number_of_inversions = 0;

  if (right <= left) return number_of_inversions;

  size_t ave = left + (right - left) / 2;

  number_of_inversions += get_number_of_inversions(a, left, ave);
  number_of_inversions += get_number_of_inversions(a, ave+1, right);

  return number_of_inversions + Merge(a, left, ave, right);
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

  std::cout << get_number_of_inversions(a, 0, a.size()-1) << '\n';

  // for (size_t i = 0; i < a.size(); i++)
  // {
  //   cout << a[i] << " ";
  // }

  cout << endl;
}
