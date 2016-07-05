#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }
  
  void rec_in_order(int R, vector<int>& result){
	  if(n==0) return;
	  
	  if(left[R] != -1)
		rec_in_order(left[R],result);
	  
	  result.push_back(key[R]);
	  
	  if(right[R] != -1)
		rec_in_order(right[R],result);
  }
  
  void rec_pre_order(int R, vector<int>& result){
	  if(n==0) return;
	  
	  result.push_back(key[R]);
	  
	  if(left[R] != -1)
		rec_pre_order(left[R],result);
	  
	  if(right[R] != -1)
		rec_pre_order(right[R],result);
  }
  
  void rec_post_order(int R, vector<int>& result){
	  if(n==0) return;
	  
	  if(left[R] != -1)
		rec_post_order(left[R],result);
	  
	  if(right[R] != -1)
		rec_post_order(right[R],result);
		
	  result.push_back(key[R]);
  }

  vector <int> in_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
	rec_in_order(0,result);
    return result;
  }

  vector <int> pre_order() {
    vector<int> result;    
    // Finish the implementation
    // You may need to add a new recursive method to do that
    rec_pre_order(0,result);
    return result;
  }

  vector <int> post_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    rec_post_order(0,result);
    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}
