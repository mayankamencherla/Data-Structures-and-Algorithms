#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <ctime>
#include <stdlib.h>

using std::vector;
using std::string;
using std::pair;
using std::min;

using namespace std;

double getMinDistance(vector<pair<int, int> >& pointsX,
                      vector<pair<int, int> >& pointsY,
                      int start,
                      int end);

bool compareX(pair<int, int>& p1, pair<int, int>& p2)
{
  // Sort by x-axis
  // -2 -1 0 1 2
  return p1.first < p2.first;
}

bool compareY(pair<int, int>& p1, pair<int, int>& p2)
{
  // Sort by x-axis
  // -2 -1 0 1 2
  return p1.second < p2.second;
}

double getDist(int x1, int y1, int x2, int y2)
{
  double result = 0.;

  result = sqrt( pow(x1 - x2, 2) +
                 pow(y1 - y2, 2) );

  return result;
}

double getDistance(vector<pair<int, int> >& points,
                   int start,
                   int end)
{
  double result = 0.;

  pair<int, int> p1 = points[start];

  pair<int, int> p2 = points[end];

  result = sqrt( pow(p1.first - p2.first, 2) +
                 pow(p1.second - p2.second, 2) );

  return result;
}

double calculateCombinedDist(vector<pair<int, int> >& pointsX,
                             vector<pair<int, int> >& pointsY,
                             int start,
                             int mid,
                             int end)
{
  double distance = numeric_limits<double>::max();

  // For every point [start, mid] calulate dist to every point in
  // [mid+1, end]. From there, compute minimum distance

  // We find all points from [start, end] in the pointsY vector
  vector<pair<int, int> > stripX, stripY;

  for (int i=start; i<=end; i++)
  {
    stripX.push_back(pointsX[i]);
  }

  sort(stripX.begin(), stripX.end(), compareY);

  stripY = stripX;

  pair<int, int> p1, p2;

  int x1, y1, x2, y2;

  for (int i=0; i<stripY.size(); i++)
  {
    p1 = stripY[i];

    x1 = p1.first; y1 = p1.second;

    for (int j=i+1; j<stripY.size(); j++)
    {
      if (abs(j - i) > 7) break;

      p2 = stripY[j];

      x2 = p2.first; y2 = p2.second;

      distance = min(distance, getDist(x1, y1, x2, y2));
    }
  }

  return distance;
}

/**
 * The algorithm is as follows:
 * From start to end, find the smallest dist between
 * pairs of points from [start, mid] to [mid+1, end]
 *
 * Compute distance IFF both points are less than dist
 * away from the mid point's x value.
 *
 * This is because dist is the min distance from the
 * divide-conquer step. Therefore, If a point p1 is at least
 * d away from the mid point, and so is the other point p2,
 * there is potential for the 2 points to have a distance
 * smaller then dist.
 */
double getCombMinDist(vector<pair<int, int> >& pointsX,
                      vector<pair<int, int> >& pointsY,
                      int start,
                      int mid,
                      int end,
                      double dist)
{
  double combinedDist = numeric_limits<double>::max();

  int combinedStart = start - 1;

  int combinedEnd = end + 1;

  // TODO: Check if this is correct
  pair<int, int> midPoint = pointsX[mid];

  pair<int, int> current;

  // The points are sorted via x axis
  for (int i=start; i<=end; i++)
  {
    current = pointsX[i];

    // Find points that are within dist from the centre
    double diff = (double) abs(current.first - midPoint.first);

    if (diff > dist) continue;

    if (i <= mid && combinedStart == start - 1)
    {
      // We find the first index that satisfies this
      // value, and then we move on to combinedEnd
      combinedStart = i;
    }
    else if (i > mid && combinedStart == start - 1)
    {
      break;
    }
    else if (i > mid)
    {
      combinedEnd = i;
    }
  }

  if ((combinedStart != start - 1) && (combinedEnd != end + 1))
  {
    return calculateCombinedDist(pointsX, pointsY, combinedStart, mid, combinedEnd);
  }

  return combinedDist;
}

/**
 * The algorithm is as follows:
 * 1. Divide - the set into 2 equal halves
 * 2. Conquer - get min dist(d) of each half recursively
 * 3. Combine - both halves, and check for any cases of 2
 *              points overlapping from one set to another
 *              to form a min distance. Eliminate all points
 *              that are d away from the centre
 */
double getMinDistance(vector<pair<int, int> >& pointsX,
                      vector<pair<int, int> >& pointsY,
                      int start,
                      int end)
{
  // Base case - when there is only 1 point or less
  if (start >= end)
  {
    return numeric_limits<double>::max();
  }

  // 2 points
  else if (start == end - 1)
  {
    return getDistance(pointsX, start, end);
  }

  int mid = floor((start + end) / 2);

  // Split into 2 halves
  double dist1 = getMinDistance(pointsX, pointsY, start, mid);

  double dist2 = getMinDistance(pointsX, pointsY, mid+1, end);

  // Combine step
  double dist = min(dist1, dist2);

  // Check if there's a distance smaller than dist
  // whose points are across the mid seperator
  double combinedDist = getCombMinDist(pointsX, pointsY, start, mid, end, dist);

  return min(dist, combinedDist);
}

double getMinDistanceNaive(vector<int>& x, vector<int>& y)
{
  double dist = numeric_limits<double>::max();

  int x1, x2, y1, y2;

  for (int i=0; i<x.size(); i++)
  {
    for (int j=i+1; j<y.size(); j++)
    {
      x1 = x[i]; y1 = y[i];

      x2 = x[j]; y2 = y[j];

      cout << "The points : " << endl;

      cout << x1 << " " << y1 << endl;

      cout << x2 << " " << y2 << endl;

      dist = min(dist, getDist(x1, y1, x2, y2));

      cout << "Dist now : ";

      cout << dist << endl;
    }
  }

  return dist;
}

void printPoints(vector<pair<int, int> >& points)
{
  for (pair<int, int> current : points)
  {
    cout << current.first << " " << current.second << endl;
  }
}

void testMinDistance()
{
  int nMax = pow(10, 5) + 2;

  int total = 0;

  int failure = 0;

  for (int k=2; k<nMax; k++)
  {
    int n = nMax;

    // total++;

    vector<int> x(n, 0);
    vector<int> y(n, 0);

    int xMax = pow(10, 9);

    vector<pair<int, int> > pointsX;

    vector<pair<int, int> > pointsY;

    // cout << endl;

    // cout << endl;

    // cout << "New iteration " << endl;

    cout << endl;

    for (size_t i = 0; i < n; i++)
    {
      x[i] = 2 * (rand() % xMax) - (rand() % xMax);

      do
      {
        y[i] = 2 * (rand() % xMax) - (rand() % xMax);
      }
      while (x[i] == y[i]);

      pointsX.push_back(make_pair(x[i], y[i]));

      pointsY.push_back(make_pair(x[i], y[i]));
    }

    // Sort by x-coordinate
    sort(pointsX.begin(), pointsX.end(), compareX);

    sort(pointsY.begin(), pointsY.end(), compareY);

    // printPoints(points);

    std::cout << std::fixed;

    clock_t time = clock();

    cout << "Computing min distance : " << endl;

    // double dist1 = getMinDistanceNaive(x, y);

    double dist2 = getMinDistance(pointsX, pointsY, 0, x.size()-1);

    cout << "Distance is : " << dist2 << endl;

    double duration = (double)(clock() - time) / (CLOCKS_PER_SEC);

    cout << "Duration for the clock : " << duration << endl;

    // if (dist1 != dist2)
    // {
    //   cout << "The distances are not equal " << endl;

    //   cout << "Naive : " << setprecision(9) << dist1 << endl;

    //   cout << "Fast : " << setprecision(9) << dist2 << endl;

    //   failure++;

    //   break;
    // }
  }

  // cout << endl;

  // cout << "My code has a failure rate of .... : " << endl;

  // cout << (double) (failure * 100 / total) << endl;
}

int main()
{
  testMinDistance();

  vector<pair<int, int> > pointsX;

  vector<pair<int, int> > pointsY;

  size_t n;
  std::cin >> n;

  // vector<int> x(n, 0);
  // vector<int> y(n, 0);

  int x, y;

  for (size_t i = 0; i < n; i++)
  {
    cin >> x >> y;

    pointsX.push_back(make_pair(x, y));

    pointsY.push_back(make_pair(x, y));
  }

  // Sort by x-coordinate
  sort(pointsX.begin(), pointsX.end(), compareX);

  sort(pointsY.begin(), pointsY.end(), compareY);

  std::cout << std::fixed;

  cout << setprecision(9) <<
      getMinDistance(pointsX, pointsY, 0, pointsX.size()-1) << endl;
}
