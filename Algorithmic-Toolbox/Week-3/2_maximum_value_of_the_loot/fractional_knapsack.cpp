#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

class Compare
{
  public:
    bool operator()(pair<double, double> p1,
                    pair<double, double> p2)
    {
      // Max heap
      // if p1's ratio is smaller than p2's ratio
      // Then p1 comes below p2 in the priority
      return (p1.second / p1.first) <
             (p2.second / p2.first);
    }
};

priority_queue<pair<double, double>,
       vector<pair<double, double> >,
       Compare>
       getWeightValues(vector<double> weights,
                       vector<double> values)
{
  priority_queue<pair<double, double>,
       vector<pair<double, double> >,
       Compare> weightValues;

  for (int i=0; i<weights.size(); i++)
  {
    weightValues.push(make_pair(weights[i], values[i]));
  }

  return weightValues;
}

double get_optimal_value(double capacity, vector<double> weights, vector<double> values)
{
  double value = 0.0;

  priority_queue<pair<double, double>,
       vector<pair<double, double> >,
       Compare> weightValues;

  // PQ that contains (weight, value) in decreasing
  // values of weight / value
  weightValues = getWeightValues(weights, values);

  pair<double, double> current;

  double weight;

  for (int i=0; i<weights.size(); i++)
  {
    if (capacity == 0.0) return value;

    current = weightValues.top();

    // Either we fully use current,
    // or we fill up knapsack fully
    weightValues.pop();

    // Select the maximum possible weight
    weight = min(current.first, capacity);

    capacity -= weight;

    // weight times value per weight
    value += weight * (current.second / current.first);
  }

  return value;
}

int main() {
  int n;
  double capacity;
  std::cin >> n >> capacity;
  vector<double> values(n);
  vector<double> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  cout << fixed;
  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
