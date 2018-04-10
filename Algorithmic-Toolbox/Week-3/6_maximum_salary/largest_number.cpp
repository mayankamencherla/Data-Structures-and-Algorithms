#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using std::vector;
using std::string;

using namespace std;

bool compare(string s1, string s2)
{
  string str1 = s1 + s2;

  string str2 = s2 + s1;

  return str1 > str2;
}

string largest_number(vector<string> a)
{
  sort(a.begin(), a.end(), compare);

  //write your code here
  std::stringstream ret;

  for (size_t i = 0; i < a.size(); i++)
  {
    ret << a[i];
  }
  string result;
  ret >> result;
  return result;
}

int main()
{
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++)
  {
    std::cin >> a[i];
  }

  std::cout << largest_number(a) << endl;
}
