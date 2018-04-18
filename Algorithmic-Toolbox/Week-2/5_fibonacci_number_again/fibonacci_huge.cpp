#include <iostream>
#include <vector>

using namespace std;

long long get_fibonacci_huge_naive(long long n, long long m)
{
    vector<long long> fib(n+1, 0);

    fib[0] = 0; fib[1] = 1;

    for (long long i=2; i<n+1; i++)
    {
        fib[i] = (fib[i-1] + fib[i-2]) % m;
    }

    return fib[n];
}

// Always starts with 0 and 1
// So whenever 0 and 1 repeat, we have a pisano period
vector<long long> getPisanoPeriod(long long m)
{
    vector<long long> period;

    period.push_back(0); period.push_back(1);

    long long value;

    for (long long i=2; i<m*m; i++)
    {
        value = (period[i-1] + period[i-2]) % m;

        // We found the pisano period
        if (value == (long long)1 &&
            period[i-1] == (long long)0)
        {
            break;
        }

        // Push value back into period only if
        // it is not 1 and the previous value is not 0
        period.push_back(value);
    }

    // The first occurence of 01 after the initial
    // occurence of 01 gives the period

    // Remove 0 towards the end
    period.pop_back();

    return period;
}

// Compute fib(n) % m
long long get_fibonacci_huge_fast(long long n, long long m)
{
    // The pisano period for Fn modulo m
    vector<long long> period = getPisanoPeriod(m);

    // Given m, we know how often the period repeats
    // We also know its corresponding period values

    // We know Fn % m repeats with period above
    // Which means every p, Fn % m repeats
    // We need to find out n % p.size()

    return period[(n % period.size())];
}

int main()
{
    long long n, m;
    std::cin >> n >> m;
    // std::cout << get_fibonacci_huge_naive(n, m) << '\n';
    long long res = get_fibonacci_huge_fast(n, m);

    cout << res << endl;
}
