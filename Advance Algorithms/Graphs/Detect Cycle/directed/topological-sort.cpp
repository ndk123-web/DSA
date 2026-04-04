#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

bool topologicalSort(vector<vector<int>> &edges, int totalNodes)
{
    queue<int> q;
    vector<int> indegree(totalNodes, 0);
    unordered_map<int, vector<int>> adj;
    int processed = 0;

    for (auto &edge : edges)
    {
        int u = edge[0];
        int v = edge[1];

        indegree[v]++;
        adj[u].push_back(v);
    }

    // q has that nodes which have 0 dependancies
    for (int i = 0; i < totalNodes; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (int &neighbour : adj[node])
        {
            if (--indegree[neighbour] == 0)
            {
                q.push(neighbour);
            }
        }

        processed++;
    }

    // if (false) processes < totalNode means there is cycle
    // if (true) processses == totalNode mean no cycle
    return processed == totalNodes;
}

int main()
{
    vector<vector<int>> edges = {
        {0, 1},
        {1, 2},
        {2, 3},
    };

    int totalNode = 5;

    bool res = topologicalSort(edges, totalNode);

    if (res)
    {
        cout << "Cycle doesn't Exists" << endl;
    }
    else
    {
        cout << "Cycle Exists" << endl;
    }
    return 0;
}