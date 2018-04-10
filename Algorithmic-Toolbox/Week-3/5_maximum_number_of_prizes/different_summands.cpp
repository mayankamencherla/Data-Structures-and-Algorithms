#include <iostream>
#include <vector>

using namespace std;

using std::vector;

vector<long long> optimal_summands(long long n)
{
  vector<long long> summands;

  // Greey choice is to choose the smallest
  // distinct number greater than the previous
  // such that the next number will be greater
  // than the current chosen number

  // Start with 1
  long long chosen = 1;

  while (n > 0)
  {
    if (n - chosen > chosen)
    {
      summands.push_back(chosen);
    }
    else
    {
      summands.push_back(n);

      break;
    }

    n -= chosen;

    chosen++;
  }

  return summands;
}

int main()
{
  long long n;
  std::cin >> n;
  vector<long long> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i)
  {
    std::cout << summands[i] << ' ';
  }

  cout << endl;
}
