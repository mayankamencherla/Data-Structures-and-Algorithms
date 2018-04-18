#include <iostream>
#include <vector>

using namespace std;

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

vector<long long> getPisanoPeriod()
{
    vector<long long> period(2, 0);

    period[0] = 0; period[1] = 1;

    long long value;

    for (long long i=2; i<=100; i++)
    {
        value = (period[i-1] + period[i-2]) % 10;

        // Period has repeated with 01
        if (value == 1 && period[i-1] == 0)
            break;

        period.push_back(value);
    }

    // Remove the 0 at the end
    period.pop_back();

    return period;
}

long long fibonacci_sum_fast(long long n)
{
    if (n <= 1) return n;

    // 0 1 2 3 4  5 6   7  8  9  10
    // 0 1 1 2 3  5 8  13 21 34  55
    // 0 1 2 4 7 12 20 33 54 88 143
    //
    // Sum(F0...Fn) = 2*Fn + Fn-1 - 1
    // Sum(F0...Fn) = Fn+2 - 1

    // Algorithm:
    // 1. Get pisano period of 10
    // 2. Compute Fn%10 and Fn-1%10
    // 3. Add the 2 and compute %10

    // Get the pisano period of 10
    vector<long long> period = getPisanoPeriod();

    // Fn repeats with period p
    return ((period[(n+2) % period.size()] - 1) + 10) % 10;
}

int main()
{
    long long n = 0;
    std::cin >> n;

    // std::cout << fibonacci_sum_naive(n) << endl;

    std::cout << fibonacci_sum_fast(n) << endl;;
}
