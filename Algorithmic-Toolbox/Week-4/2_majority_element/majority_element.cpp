#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>

using std::vector;

using namespace std;

void copyVecBack(vector<int>& a, vector<int>& ap, int left, int right)
{
  for (int i=left; i<=right; i++)
  {
    a[i] = ap[i-left];
  }
}

vector<int> copyVec(vector<int>& a, int left, int right)
{
  vector<int> ap;

  for (int i=left; i<=right; i++)
  {
    ap.push_back(a[i]);
  }

  return ap;
}

void Merge(vector<int>& a, int left, int mid, int right)
{
  // Merge a[left...mid] and a[mid+1...right]

  // Move over a[left..right] to ap
  vector<int> ap = copyVec(a, left, right);

  int s1 = left, s2 = mid+1;

  // Start copying over from left
  int current = 0;

  while (s1 <= mid && s2 <= right)
  {
    if (a[s1] <= a[s2])
    {
      ap[current++] = a[s1++];
    }
    else if (a[s1] > a[s2])
    {
      ap[current++] = a[s2++];
    }
  }

  while (s1 > mid && s2 <= right)
  {
    // Copy s2 over because s1 has exceeded its max
    ap[current++] = a[s2++];
  }

  while (s1 <= mid && s2 > right)
  {
    // Copy s1 over because s2 has exceeded its max
    ap[current++] = a[s1++];
  }

  copyVecBack(a, ap, left, right);
}

void MergeSort(vector<int> &a, int left, int right)
{
  if (left >= right) return;

  int mid = floor((left + right) / 2);

  MergeSort(a, left, mid);

  MergeSort(a, mid+1, right);

  Merge(a, left, mid, right);
}

int get_majority_element(vector<int> &a, int left, int right)
{
  // Sort and then scan -> O(nlogn)
  MergeSort(a, left, right);

  int maxCount = 1, count = 0, val = -1;

  for (int i=0; i<a.size(); i++)
  {
    if (a[i] == val)
    {
      // We are seeing this value again
      count++;

      if (count > maxCount)
      {
        // We have a majority element
        maxCount = count;
      }
    }
    else
    {
      // We are seeing a new value
      count = 1;

      // Setting val so that we can see it again
      val = a[i];
    }

    // At each iteration we check if we found a maximum element
    if (maxCount > a.size() / 2) return 1;
  }

  return -1;
}

void testMergeSort()
{
  int n = 10; //pow(10, 5);

  vector<int> a(n, 0);

  int val = pow(10, 1);

  for (int i=0; i<n; i++)
  {
    a[i] = rand() % val;
  }

  cout << "Array before MergeSort: ";

  for (int i=0; i<a.size(); i++)
  {
    cout << a[i] << " ";
  }

  cout << endl;

  MergeSort(a, 0, a.size()-1);

  cout << "Array after MergeSort: ";

  for (int i=0; i<a.size(); i++)
  {
    cout << a[i] << " ";
  }

  cout << endl;
}

int main()
{
  // testMergeSort();

  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i)
  {
    std::cin >> a[i];
  }

  std::cout << (get_majority_element(a, 0, a.size()-1) != -1) << '\n';
}
