#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

using namespace std;

long long MaxPairwiseProduct(const vector<long long>& numbers) {
  int n = numbers.size();

  long long result = 0;

  // We need to find the 2 indices to give us this result
  int ind1 = -1; int ind2 = -2;

  for (int i=0; i<numbers.size(); i++)
  {
    // If ind has not been assigned yet, assign to 0
    // or check if numbers[i] is the max value in the array
    if (ind1 == -1 || numbers[i] > numbers[ind1])
    {
      ind1 = i;
    }
  }

  for (int i=0; i<numbers.size(); i++)
  {
    // if i = ind1, we must not use that value, as we want the 2nd max
    // else, we assign ind2 to i if ind2 = -1 or i contains 2nd max
    if (ind1 != i && (ind2 == -1 || numbers[i] > numbers[ind2]))
    {
      ind2 = i;
    }
  }

  result = numbers[ind1] * numbers[ind2];

  return result;
}

int main() {
    int n;
    cin >> n;
    vector<long long> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    long long result = MaxPairwiseProduct(numbers);
    cout << result << "\n";
    return 0;
}
