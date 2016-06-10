#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}


vector<int> my_optimal_sequence(int n) {
	// a good recurrence relation to follow is...........
	// C(n) = min { C(n-1) + 1,  C(n/2) + 1,  C(n/3) + 1 } 
	// Kind of like the DP change problem 
	
	vector<int> sequence;
	vector<int> MinNum(n+1); 
	vector<int> pre_board(n+1); 
	pre_board[0] = 0; pre_board[1] = 1;
	MinNum[0] = 0; MinNum[1] = 1; // for 0 and 1 the answers are 0 and 1
	int a,b,c;
	
	for(int i=2; i<=n; i++){
		
		a = MinNum[i-1]+1; 
		b = (i%2==0)? MinNum[i/2]+1 : n+1;
		c = (i%3==0)? MinNum[i/3]+1 : n+1;
		
		MinNum[i] = std::min(std::min(a,b),c);
	} 
	// using MinNum array trace back the steps to the 1 number
	int j = MinNum[n];
	sequence.push_back(n);
	int x,y,z;
	while(j>1){
		x = n-1; y = (n%2==0)? n/2 : 0; z = (n%3==0)? n/3 : 0; 
		
		if(MinNum[z] == j-1) n = n/3;
		else if(MinNum[y] == j-1) n = n/2;
		else n = n-1;
		
		sequence.push_back(n);
		
		j--;
	}
	
	reverse(sequence.begin(),sequence.end());
	return sequence;
}

int main() {
  int n;
  std::cin >> n;
  /*vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }*/
  
  vector<int> sequence2 =  my_optimal_sequence(n);
  
  //sequence_game(n);
  std::cout << sequence2.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence2.size(); ++i) {
    std::cout << sequence2[i] << " ";
  }
}
