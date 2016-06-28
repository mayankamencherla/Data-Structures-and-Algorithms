#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
  }
  
  void GenerateSwapsFast(){
	  swaps_.clear();
	  int size = data_.size();
	  
	  for(int i = floor(size/2); i>=1; i--){
		  SiftDown(i-1); // based on 0 indexing 
	  } 
  }
  
  void SiftDown(int i){
	  int maxIndex = i;
	  int l = leftChild(i);
	  
	  if(l<data_.size() && data_[l] < data_[maxIndex]){
		  maxIndex = l;
	  }
	  
	  int r = rightChild(i);
	  
	  if(r < data_.size() && data_[r] < data_[maxIndex]){
		  maxIndex = r;
	  }
	  
	  if(i != maxIndex){
		  swap(data_[i], data_[maxIndex]);
		  swaps_.push_back(make_pair(i, maxIndex));
		  SiftDown(maxIndex);
	  }
  }
  
  int leftChild(int i){
	  return 2*i+1;
  }
  
  int rightChild(int i){
	  return 2*i+2;
  }

 public:
  void Solve() {
    ReadData();
    //GenerateSwaps();
	GenerateSwapsFast();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
