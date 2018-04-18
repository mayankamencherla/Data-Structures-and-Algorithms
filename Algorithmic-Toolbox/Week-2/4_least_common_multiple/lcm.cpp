#include <iostream>

using namespace std;

long long lcm_naive(long long a, long long b)
{
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

long long gcd(long long a, long long b)
{
    if (b == 0) return a;

    long long ap = (a + b) % b;

    return gcd(b, ap);
}

long long lcm_fast(long long a, long long b)
{
    return (a * b) / gcd(a, b);
}

int main() {
  long long a, b;
  cin >> a >> b;
  // cout << lcm_naive(a, b) << endl;
  cout << lcm_fast(a, b) << endl;
  return 0;
}
