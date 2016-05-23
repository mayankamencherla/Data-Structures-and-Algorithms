#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

/*Task. Given a set of n segments [a0; b0]; [a1; b1]; : : : ; [an-1; bn-1] with integer coordinates on a line, nd
the minimum number m of points such that each segment contains at least one point. That is, find a
set of integers X of the minimum size such that for any segment [ai; bi] there is a point x 2 X such
that ai<=x<=bi.
 * */

struct Segment {
  int start, end;
};


// This comparator takes in segments and returns 
bool compareByx(const Segment &s1,const Segment &s2){
	return s1.end < s2.end;
}

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  //write your code here
  // This code works for when the list is sorted, but for unsorted it doesn't
  int min_point = segments[0].end; // initializing our min point
  int prev_min = 0;
  // Going to sort my vector now, and write a comparator
  std::sort(segments.begin(),segments.end(),compareByx);
  
  for (size_t i = 0; i < segments.size(); ++i) {
	//std::cout << segments[i].start;
	if(min_point >=segments[i].start && min_point < segments[i].end){
		// do nothing
	}
	
	else {
		min_point = segments[i].end;
		points.push_back(min_point);
	}
    //points.push_back(segments[i].start);
    //points.push_back(segments[i].end);
  }
  points.erase(unique(points.begin(),points.end()),points.end());
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
