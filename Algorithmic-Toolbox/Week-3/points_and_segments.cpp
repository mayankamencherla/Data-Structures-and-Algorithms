#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>

using std::vector;

struct segment{
	int start;
	int end;
};

/* A good test case::
13 14
-2 3
0 4
5 8
8 12
5 10
8 13
7 9
8 12
9 12
8 12
5 9
12 13
12 14
1 3 4 5 6 7 8 9 10 11 12 13 14 15
 * 
 * */

bool compareSegment(const segment &a, const segment &b){
	return a.start < b.start;
}

int binary_search(vector<segment> Segments, int point, int lo, int hi, int cnt){
	
	if(hi>=lo){
		
		int mid = floor((lo+hi)/2);
		
		/*if(point >= Segments[mid].start && point <= Segments[mid].end){
			cnt = cnt + 1;
			//hi = mid-1; // if it exists in this segment we need to check for segments before it as well
			return binary_search(Segments,point,lo,mid-1,cnt);
			return binary_search(Segments,point,mid+1,hi,cnt);
		}
		
		else if(point < Segments[mid].start) return binary_search(Segments,point,lo,mid-1,cnt);
		
		else return binary_search(Segments,point,mid+1,hi,cnt);*/
		
		//cnt += binary_search(Segments,point,lo,mid-1,0);
		//cnt += binary_search(Segments,point,mid+1,hi,0);
		
		if(point >= Segments[mid].start && point <= Segments[mid].end){
			cnt = cnt + 1;
			//std::cout<< Segments[mid].start << '\n';
			cnt += binary_search(Segments,point,lo,mid-1,0);
			cnt += binary_search(Segments,point,mid+1,hi,0);
		}
		
		else if(point <= Segments[mid].start || point <= Segments[mid].end){
			cnt += binary_search(Segments,point,lo,mid-1,0);
		} 
		
		else if(point >= Segments[mid].start || point >= Segments[mid].end){
			cnt += binary_search(Segments,point,mid+1,hi,0);
		}
		
		else cnt = 0;
	}
	
	return cnt;
	
}

vector<int> fast_count_segments(vector<segment> Segments, vector<int> points) {
	// starts have ith start point, ends have ith end point
	// I would like to first sort both arrays 
	vector<int> cnt(points.size());
	// So basically cnt[i] has the point val 1 or 0 for points[i]
	
	//write your code here
	// I have changed start and end to segments
	std::sort(Segments.begin(),Segments.end(),compareSegment); // sorting segments by start
	//std::sort(points.begin(),points.end()); // points also sorted now
	
	// next step is to step through the loop and rule out cases when the point isn't in the sorted segment
	
	/*std::cout<< "\nThe sorted segments are:\n" ;
	for(size_t i=0; i<Segments.size(); i++){
		std::cout<< Segments[i].start << ' ' << Segments[i].end << '\n';
	}*/
	
	// now we can do a binary search using a while look for points[j]
	for(int j=0; j<points.size(); j++){
		cnt[j] = binary_search(Segments,points[j],0,Segments.size()-1,0);
	}
	
	return cnt;
}

vector<int> naive_count_segments(vector<segment> Segments, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < Segments.size(); j++) {
      cnt[i] += Segments[j].start <= points[i] && points[i] <= Segments[j].end;
    }
  }
  return cnt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<segment> Segments(n); //ends(n);
  for (size_t i = 0; i < Segments.size(); i++) {
    std::cin >> Segments[i].start >> Segments[i].end;
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = naive_count_segments(Segments, points);
  vector<int> cnt2 = fast_count_segments(Segments, points);
  
  std::cout << "\nThe naive solution is: \n";
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
  
  std::cout << "\n\nThe fast solution is: \n";
  for (size_t i = 0; i < cnt2.size(); i++) {
    std::cout << cnt2[i] << ' ';
  }
}
