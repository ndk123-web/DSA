#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;
unordered_set<int> visited;
unordered_map<int, vector<int>> adj;

bool dfs(vector<vector<int>> &edges, int node, int parent)
{
    // insert node in visited
    visited.insert(node);

    for (int &neighbour : adj[node])
    {
        if (!visited.count(neighbour))
        {
            if (dfs(edges, neighbour, node))
                return true;
        }

        // why here because here if parent == neighbour means bidirection (skip)
        // if not then means cycle exists
        else if (parent != neighbour)
        {
            return true; // cycle exists
        }
    }

    // cycle not exists
    return false;
}

bool detectCycle(vector<vector<int>> &edges, int node, int totalNodes)
{

    // build adjaceny
    for (auto &edge : edges)
    {
        int u = edge[0];
        int v = edge[1];

        // both ways
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < totalNodes; i++)
    {
        // if not visited node i
        if (!visited.count(i))
        {
            // cycle exist
            if (dfs(edges, i, -1))
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    vector<vector<int>> edges = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
    };

    bool res = detectCycle(edges, 0, 5);

    if (res)
    {
        cout << "Cycle Exists" << endl;
    }
    else
    {
        cout << "Cycle Doesn't Exists" << endl;
    }

    return 0;
}