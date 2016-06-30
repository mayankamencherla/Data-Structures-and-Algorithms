#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using std::string;
using std::vector;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<long long>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

long long PolyHash(const string& S, long long prime, long long multiplier){
	long long hash = 0;
	for (int i = static_cast<int> (S.size()) - 1; i >= 0; --i)
		hash = (hash * multiplier + S[i]) % prime;
		
	return hash;
}

vector<long long> PreComputeHashes(const string& T, long long P_len, long long p, long long x){
	
	long long len1 = T.length()-P_len; 
	
	vector<long long> H(len1+1);
	H[len1] = PolyHash(T.substr(len1,P_len),p,x);
	
	long long y = 1;
	
	for(int i=1; i <= P_len; ++i)
		y = ( (y * x)%p + p)%p;
	
	for(int i=len1-1; i>=0; --i){
		H[i] = ( ( x*H[i+1] + T[i] - y*T[i+P_len] ) %p + p) %p; 
	}
	
	return H;
}

bool AreEqual(const string& S1, const string& S2){
	if(S1.length()!=S2.length())
		return false;
		
	for(int i=0; i< S1.length(); ++i){
		if(S1[i]!=S2[i])
			return false;
	}
	
	return true;
}

vector<long long> RabinKarp(const string& T, const string& P){
	long long p = 500009; long long x = rand()%(p-1) + 1; // 1 to p-1
	vector<long long> result;
	// now let us compute the hashes for this function
	long long pHash = PolyHash(P,p,x);
	vector<long long> H = PreComputeHashes(T,P.length(),p,x);
	
	for(int i=0; i<=T.length()-P.length(); ++i){
		if(pHash != H[i])
			continue;
			
		if(AreEqual(T.substr(i,P.length()),P)){
			result.push_back(i);
			//std::cout << i << ' ';
		}
	}
	
	std::cout<<'\n';
	
	return result;
}

vector<long long> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    vector<long long> ans;
    ans = RabinKarp(t,s); // text and pattern
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
