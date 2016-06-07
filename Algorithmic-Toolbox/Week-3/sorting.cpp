#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>

// The task is to use 2-way and 3 way partition to solve quick sort

using std::vector;
using std::swap;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

std::pair<int,int> partition3(vector<int> &a, int l, int r){
	int x = a[l]; // our partition value
	
	int i = l; //  i starts at l
	int lo = l;
	int hi = r;
	
	while(i<=hi){
		
		if(a[i] < x){
			swap(a[lo],a[i]); 
			lo++; 
			i++;
		}
		
		else if(a[i] > x){
			swap(a[hi],a[i]);
			hi--;
		}
		
		else  i++;
	}
	
	std::pair<int,int> m = std::make_pair(lo,hi);
	return m;
}

void randomized_quick_sort3(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  std::pair<int,int> m = partition3(a, l, r);
  
  //std::cout << m.first -1 << ' ' << m.second + 1 << '\n';

  randomized_quick_sort3(a, l, m.first - 1);
  randomized_quick_sort3(a, m.second + 1, r);
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  int m = partition2(a, l, r);
  
  //std::cout << m.first -1 << ' ' << m.second + 1 << '\n';

  randomized_quick_sort(a, l, m - 1);
  randomized_quick_sort(a, m + 1, r);
}


int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  vector<int> a1(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
	a1[i] = a[i];
  }
  
  randomized_quick_sort3(a, 0, a.size() - 1);
  //randomized_quick_sort(a1, 0, a1.size() - 1);
  
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
  
  std::cout << '\n';
  
  /*for (size_t i = 0; i < a1.size(); ++i) {
    std::cout << a1[i] << ' ';
  }*/
}
