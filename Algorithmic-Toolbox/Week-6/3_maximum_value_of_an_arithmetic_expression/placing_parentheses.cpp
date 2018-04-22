#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <limits>

using std::vector;
using std::string;
using std::max;
using std::min;

using namespace std;

// Global variables
vector<vector<long long> > Max;
vector<vector<long long> > Min;

long long eval(long long a, long long b, char op)
{
  if (op == '*')
  {
    return a * b;
  }
  else if (op == '+')
  {
    return a + b;
  }
  else if (op == '-')
  {
    return a - b;
  }
  else
  {
    assert(0);
  }
}

void initializeMinMaxArrays(const string &exp)
{
  Max.resize(exp.size()/2+1, vector<long long>(exp.size()/2+1, 0));

  Min.resize(exp.size()/2+1, vector<long long>(exp.size()/2+1, 0));

  for (int i=0; i<exp.size(); i=i+2)
  {
    long long num = exp[i] - '0';

    Max[i/2][i/2] = num;

    Min[i/2][i/2] = num;
  }
}

// Modifying the states of M[i][j] and m[i][j]
void getMinMaxValue(const string &exp, int i, int j)
{
  long long min = numeric_limits<long long>::max();

  long long max = numeric_limits<long long>::min();

  long long a, b, c, d;

  char opk;

  // d0 op0 d1 op1 d2 op2 d3

  // M[i][k] opk M[k+1][j]
  for (int k=i; k<j; k++)
  {
    opk = exp[2*k+1];

    a = eval(Max[i][k], Max[k+1][j], opk);

    b = eval(Max[i][k], Min[k+1][j], opk);

    c = eval(Min[i][k], Max[k+1][j], opk);

    d = eval(Min[i][k], Min[k+1][j], opk);

    min = std::min(min, std::min(a, std::min(b, std::min(c, d))));

    max = std::max(max, std::max(a, std::max(b, std::max(c, d))));
  }

  Max[i][j] = max;

  Min[i][j] = min;
}

// exp has length 2n+1
// So we must make a grid of size n by n
long long get_maximum_value(const string &exp)
{
  // Pre-compute across main diagonal
  initializeMinMaxArrays(exp);

  int n = exp.size() / 2;

  // The algorithm computes the values across diagonals
  // starting from the 2nd diagonal that is further away
  // from the main diagonal.

  // The algorithm is based on the differences in (i, j).
  // For eg. (0, 1), (1, 2) ... for s = 1
  // For eg. (0, 2), (1, 3) ... for s = 2
  // For eg. (0, n-1), (1, n)   for s = n-1
  // For eg. (0, n)             for s = n
  for (int s = 1; s <= n; s++)
  {
    for (int i = 0; i <= n - s; i++)
    {
      int j = i + s;

      getMinMaxValue(exp, i, j);
    }
  }

  return Max[0][exp.size()/2];
}

int main()
{
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
