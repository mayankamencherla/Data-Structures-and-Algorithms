#include <iostream>
#include <vector>
#include <math.h>

using std::vector;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
	int n = weights.size();
	vector<double> usage(n,0.0); // array with item usages
	double V = 0.0; // our calorie count is currently 0
	
	for(int i=0; i<n; i++){
		if(capacity == 0) return V;
		
		int a; // our best vi/wi for later
		// We first find max(vi/wi) for wi >0
		double max_calorie = 0;
		int max_weight = 0;
		int index = 0;
		for(int j=0; j<n; j++){
			//std::cout << weights[j] << '\n';
			if(weights[j]> 0 && double(values[j])/weights[j] > max_calorie){
				max_calorie = double(values[j])/weights[j];
				max_weight = weights[j];
				index = j;
			}
		}
		
		a = std::min(max_weight,capacity);
		V = V + a*max_calorie;
		weights[index] = weights[index] - a;
		usage[index] = usage[i] + a;
		capacity = capacity - a;
	}
	
	return floor(V*10000)/10000;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
