#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	// size variable initialized and sets is of size size!
	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			// each element has parent set to itself
			// each sets[i] has its size initialized in the input
			sets[i].parent = i;
	}

	int getParent(int i) {
		// find parent and compress path 
		// converted to 0 based indexing
		if(i != sets[i].parent)
			sets[i].parent = getParent(sets[i].parent); // path compression
		
		return sets[i].parent;
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		if (realDestination != realSource) {
			// merge two components
			// use union by rank heuristic
			// update max_table_size
			
			// set source's parent to destinations parent
			sets[realSource].parent = realDestination;
			// increment size of destination
			sets[realDestination].size += sets[realSource].size;
			// set size of source to 0 as well
			sets[realSource].size = 0; 
			//max_table_size = max(sets.begin().size,sets.end().size)
			if(sets[realDestination].size > max_table_size)
				max_table_size = sets[realDestination].size;
		}
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (int i=0; i<n; i++) {
		cin >> tables.sets[i].size; // setting each elemeent's size = input
		tables.max_table_size = max(tables.max_table_size, tables.sets[i].size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
                --destination;
                --source;
		
		tables.merge(destination, source);
	        cout << tables.max_table_size << endl;
	}

	return 0;
}
