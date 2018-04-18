#include <iostream>
#include <vector>

using namespace std;

int get_fibonacci_last_digit_naive(int n)
{
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i)
    {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int getFibLastDigit(int n)
{
    vector<int> fib(n+1, 0);

    fib[0] = 0; fib[1] = 1;

    for (int i=2; i<=n; i++)
    {
        fib[i] = (fib[i-1] + fib[i-2]) % 10;
    }

    return fib[n];
}

int main()
{
    int n;
    std::cin >> n;
    // int c = get_fibonacci_last_digit_naive(n);
    int c = getFibLastDigit(n);
    std::cout << c << '\n';
}
