#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

using namespace std;

struct Segment
{
  int start, end;
};

// When does s1 come before s2?
bool Compare(Segment s1, Segment s2)
{
  return s1.end < s2.end;
}

vector<int> optimal_points(vector<Segment> &segments)
{
  vector<int> points;

  sort(segments.begin(), segments.end(), Compare);

  // The greedy choice is to add a point with the
  // earliest end time, and then mask all segments
  // that start and end around this time

  int curr = 0;

  int finish;

  while (curr < segments.size())
  {
    finish = segments[curr].end;

    // Make the greedy choice
    points.push_back(finish);

    curr++;

    while (segments[curr].start <= finish &&
           segments[curr].end >= finish)
    {
      // Mask all segments around finish
      curr++;
    }
  }

  return points;
}

int main()
{
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i)
  {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << endl;
  for (size_t i = 0; i < points.size(); ++i)
  {
    std::cout << points[i] << " ";
  }

  cout << endl;
}
