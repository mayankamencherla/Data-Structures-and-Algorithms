#include <iostream>
#include <vector>

using namespace std;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

vector<int> getPisanoPeriod()
{
    vector<int> period(2, 0);

    period[0] = 0; period[1] = 1;

    long long value;

    for (int i=2; i<=100; i++)
    {
        value = (period[i-1] + period[i-2]) % 10;

        if (value == 1 && period[i-1] == 0) break;

        period.push_back(value);
    }

    // Remove the 0 at the end
    period.pop_back();

    return period;
}

long long get_fibonacci_partial_sum_fast(long long from, long long to)
{
    // Get pisano period of 10
    vector<int> period = getPisanoPeriod();

    // Find the sum up till Ffrom-1
    long long s1 = period[(from-1+2) % period.size()] - 1;

    // Find the sum up till Fto
    long long s2 = period[(to+2) % period.size()] - 1;

    return (s2 - s1 + 10) % 10;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    // cout << get_fibonacci_partial_sum_naive(from, to) << endl;

    cout << get_fibonacci_partial_sum_fast(from, to) << endl;
}
