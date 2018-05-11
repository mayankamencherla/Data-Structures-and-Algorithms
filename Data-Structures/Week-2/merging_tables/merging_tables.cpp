#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DisjointSet
{
    private:
        vector<int> parent;
        vector<int> rank;

        // Max number of rows
        int maxRows;

    public:
        DisjointSet(int size, vector<int> numRows)
        {
            parent.resize(size, 0);

            // i is a parent of itself initially
            for (int i=0; i<size; i++) parent[i] = i;

            rank.resize(size, 0);

            maxRows = 0;

            for (int i=0; i<numRows.size(); i++)
            {
                rank[i] = numRows[i];

                maxRows = max(maxRows, rank[i]);
            }
        }

        // Returns the parent of the element i
        int find(int i)
        {
            if (parent[i] != i)
            {
                parent[i] = find(parent[i]);
            }

            return parent[i];
        }

        void merge(int destination, int source)
        {
            int dest_id = find(destination);

            int source_id = find(source);

            // Both of them are already in the same set
            if (dest_id == source_id) return;

            // Source has a symlink to destination
            parent[source_id] = dest_id;

            // Destination now has sources tables
            rank[dest_id] += rank[source_id];

            // Setting max rows
            maxRows = max(rank[dest_id], maxRows);

            // Source has no tables left
            rank[source_id] = 0;
        }

        vector<int> getRank()
        {
            return rank;
        }

        vector<int> getParent()
        {
            return parent;
        }

        int getMaxRows()
        {
            return maxRows;
        }
};

int main()
{
    // Setting up the main function
    int numTables, numMerge;

    cin >> numTables;

    cin >> numMerge;

    vector<int> numRows(numTables, 0);

    for (int i=0; i<numTables; i++)
    {
        // Number of rows in the ith table
        cin >> numRows[i];
    }

    // Initializing the disjoint set
    DisjointSet dset = DisjointSet(numTables, numRows);

    int source, destination;

    vector<int> maxRows;

    for (int i=0; i<numMerge; i++)
    {
        cin >> destination;

        cin >> source;

        dset.merge(destination-1, source-1);

        maxRows.push_back(dset.getMaxRows());
    }

    for (int maxRow : maxRows)
    {
        cout << maxRow << endl;
    }
}
