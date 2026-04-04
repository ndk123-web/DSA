#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

unordered_set<int> visited;
unordered_set<int> recursionStack;
unordered_map<int, vector<int>> adjList;

bool dfs(int node)
{
    // again that node seen then cycle exist
    if (recursionStack.count(node))
    {
        return true;
    }

    // inside visited means dont need to visit again
    if (visited.count(node))
    {
        return false;
    }

    visited.insert(node);
    recursionStack.insert(node);

    for (int &nei : adjList[node])
    {
        // cycle exists
        if (dfs(nei))
        {
            return true;
        }
    }

    // backtracking
    recursionStack.erase(node);

    // no cycle exist
    return false;
}

bool detectCycle(vector<vector<int>> &edges, int node)
{
    for (auto &edge : edges)
    {
        int u = edge[0];
        int v = edge[1];

        adjList[u].push_back(v);
    }

    return dfs(node);
}

int main()
{
    vector<vector<int>> edges = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 3, 3},
        {3, 1, 4}};

    int totalNodes = 5;

    // because there might be another component that might have cycle
    for (int i = 0; i < 4; i++)
    {
        if (detectCycle(edges, i))
        {
            cout << "There is a Cycle" << endl;
            break;
        }
        else
        {
            cout << "There isn't any Cycle" << endl;
        }
    }
    return 0;
}