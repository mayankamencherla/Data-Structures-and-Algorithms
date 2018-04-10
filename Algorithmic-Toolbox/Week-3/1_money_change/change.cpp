#include <iostream>

int get_change(int m)
{
    int numTens = m / 10;

    m = m - numTens*10;

    int numFives = m / 5;

    m = m - numFives*5;

    int numOnes = m;

    return numTens + numFives + numOnes;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
