#include <iostream>
#include <vector>

using namespace std;

class DSU
{
public:
    vector<int> parents;

    int find(int node)
    {
        if (node == parents[node])
        {
            return node;
        }

        return parents[node] = find(parents[node]);
    }

    bool unite(int u, int v)
    {
        int parent_u = find(u);
        int parent_v = find(v);

        // yes there is cycle
        if (parent_u == parent_v)
        {
            return true;
        }

        this->parents[parent_v] = parent_u;

        // no cycle between u and v
        return false;
    }

    bool run(vector<vector<int>> &edges, int totalNodes)
    {
        parents.assign(totalNodes, 0);

        for (int i = 0; i < totalNodes; i++)
        {
            parents[i] = i;
        }

        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];

            // means there is cycle
            if (this->unite(u, v))
            {
                return true;
            }
        }
        // no cycle
        return false;
    }
};

int main()
{

    vector<vector<int>> edges = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},
    };

    int totalNodes = 4;

    DSU *dsu = new DSU();
    bool res = dsu->run(edges, totalNodes);

    if (res)
    {
        cout << "Cycle Exists in Undirected graph" << endl;
    }
    else
    {
        cout << "Cycle doesn't Exists in Undirected graph" << endl;
    }
    return 0;
}