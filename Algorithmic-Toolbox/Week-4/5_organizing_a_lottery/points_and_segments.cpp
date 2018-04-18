#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <ctime>
#include <map>
#include <algorithm>

using std::vector;

using namespace std;

bool compare(pair<int, int> p1, pair<int, int> p2)
{
  // Sort in ascending order in x axis
  if (p1.first != p2.first)
    return p1.first < p2.first;

  // If two points are on the same point on x axis
  // Then we want to choose based on whether it is a
  // point, a start or an end point.
  //
  // Start must come before point and end must come after both
  // The ordering must be [start, point, end] = [0, 1, 2]

  // [start, point, end] => [0, 1, 2]
  return p1.second < p2.second;
}

vector<pair<int, int> > getLines(vector<int>& starts,
                                 vector<int>& ends,
                                 vector<int>& points)
{
  vector<pair<int, int> > lines;

  for (int i=0; i<starts.size(); i++)
  {
    lines.push_back(make_pair(starts[i], 0));

    lines.push_back(make_pair(ends[i], 2));
  }

  for (int i=0; i<points.size(); i++)
  {
    // Pushing points into lines
    lines.push_back(make_pair(points[i], 1));
  }

  sort(lines.begin(), lines.end(), compare);

  return lines;
}

vector<int> fast_count_segments(vector<int>& starts,
                                vector<int>& ends,
                                vector<int>& points)
{
  vector<int> cnt(points.size(), 0);

  // [0, 1, 2] => [l, r, p]
  // l is the left index of the segment
  // r is the right index of the segment
  // p is the point we are searching for
  //
  // O(n + m) to create lines and O((n+m)log(n+m)) to sort
  vector<pair<int, int> > lines = getLines(starts, ends, points);

  map<int, vector<int> > index;

  for (int i=0; i<points.size(); i++)
  {
    // Gives us the index in points array based on point
    index[points[i]].push_back(i);
  }

  // 0 increases this, 1 decreases it
  // 2 implies that we found a point and we update its #
  int numLeft = 0;

  vector<int> pointIndex;

  // O(m + n) to go over entire array
  for (int i=0; i<lines.size(); i++)
  {
    if (lines[i].second == 0)
    {
      numLeft++;
    }
    else if (lines[i].second == 2)
    {
      numLeft--;
    }
    else if (lines[i].second == 1)
    {
      pointIndex = index[lines[i].first];

      for (int i=0; i<pointIndex.size(); i++)
      {
        cnt[pointIndex[i]] = numLeft;
      }
    }
  }

  return cnt;
}

vector<int> naive_count_segments(vector<int>& starts,
                                 vector<int>& ends,
                                 vector<int>& points)
{
  vector<int> cnt(points.size());

  // O(mn) algorithm
  // m = #points and n = #segments
  for (size_t i = 0; i < points.size(); i++)
  {
    for (size_t j = 0; j < starts.size(); j++)
    {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }

  return cnt;
}

void testNaiveFastSolns()
{
  int n, m;

  for (int i=1; i<1000; i++)
  {
    n = rand() % i + 1;

    m = rand() % i + 1;

    cout << "m = " << m << " n = " << n << endl;

    vector<int> starts(n), ends(n);

    vector<pair<int, int> > lines;

    int val = pow(10, 2);

    for (size_t i = 0; i < starts.size(); i++)
    {
      // std::cin >> starts[i] >> ends[i];
      starts[i] = 2 * (rand() % val) - (rand() % val);

      do
      {
        // ends has to be greater than starts
        ends[i] = 2 * (rand() % val) - (rand() % val);
      }
      while (ends[i] < starts[i]);
    }

    vector<int> points(m);

    for (size_t i = 0; i < points.size(); i++)
    {
      // std::cin >> points[i];
      points[i] = 2 * (rand() % val) - (rand() % val);
    }

    cout << "Beginning slow count segments " << endl;

    clock_t time = clock();

    //use fast_count_segments
    vector<int> cnt1 = naive_count_segments(starts, ends, points);

    double duration = (clock() - time) / (double) CLOCKS_PER_SEC;

    cout << "Slow count completed in " << duration << endl;

    cout << "Beginning fast count segments " << endl;

    time = clock();

    vector<int> cnt2 = fast_count_segments(starts, ends, points);

    duration = (clock() - time) / (double) CLOCKS_PER_SEC;

    cout << "Fast count completed in " << duration << endl;

    bool breakLoop = false;

    for (size_t i = 0; i < cnt1.size(); i++)
    {
      if (cnt1[i] != cnt2[i])
      {
        cout << "This is a failure point" << endl;

        cout << points[i] << ": " << cnt1[i] << " " << cnt2[i] << endl;

        breakLoop = true;
      }
    }

    if (breakLoop)
    {
      cout << "Segments : " << endl;

      for (int i=0; i<starts.size(); i++)
      {
        cout << starts[i] << " " << ends[i] << endl;
      }

      for (int i=0; i<points.size(); i++)
      {
        cout << points[i] << " ";
      }

      cout << endl;

      break;
    }

    cout << endl;
  }
}

int main()
{
  // testNaiveFastSolns();

  int n, m;
  std::cin >> n >> m;

  vector<int> starts(n), ends(n);

  vector<pair<int, int> > lines;

  for (size_t i = 0; i < starts.size(); i++)
  {
    std::cin >> starts[i] >> ends[i];

    // lines.push_back(make_pair(starts[i], ends[i]));
  }

  vector<int> points(m);

  for (size_t i = 0; i < points.size(); i++)
  {
    std::cin >> points[i];
  }

  //use fast_count_segments
  // vector<int> cnt = naive_count_segments(starts, ends, points);

  // for (size_t i = 0; i < cnt.size(); i++)
  // {
  //   std::cout << cnt[i] << ' ';
  // }

  // cout << endl;

  vector<int> cnt = fast_count_segments(starts, ends, points);

  for (size_t i = 0; i < cnt.size(); i++)
  {
    std::cout << cnt[i] << ' ';
  }

  cout << endl;
}
