#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

int edit_distance(const string &str1, const string &str2) {
	//vector< vector<int> > D(str1.size(), vector<int>(str2.size())); // creating a 2D vector of int
	int D[str1.size()+1][str2.size()+1];
	int insertion,deletion,mismatch,match;
	
	for(int k =0; k<=str1.size(); k++) D[k][0] = k;
	for(int l =0; l<=str2.size(); l++) D[0][l] = l;
	
	for(int j=1; j<=str2.size(); j++){
		for(int i=1; i<=str1.size(); i++){
			insertion = D[i][j-1] + 1;
			deletion = D[i-1][j] + 1;
			match = D[i-1][j-1];
			mismatch = D[i-1][j-1] + 1;
			
			if(str1[i-1] == str2[j-1]){
				D[i][j] = std::min(std::min(insertion,deletion),match);
			}
			
			else{
				D[i][j] = std::min(std::min(insertion,deletion),mismatch);
			}
		} 
	}
  
  return D[str1.size()][str2.size()];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
