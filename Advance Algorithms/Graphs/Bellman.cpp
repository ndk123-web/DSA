#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>
#include <queue>

using namespace std;

class BellmanFord
{
private:
    string name;

public:
    BellmanFord(string name)
    {
        this->name = name;
    }

    vector<int> runAlgo(vector<vector<int>> &edges, int startNode, int totalNodes)
    {
        vector<int> distances(totalNodes, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        distances[startNode] = 0;

        int ITERATION = totalNodes - 1;

        // Relax V - 1 times
        for (int i = 0; i < ITERATION; i++)
        {

            for (auto &edge : edges)
            {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];

                if (distances[u] != INT_MAX && distances[u] + w < distances[v])
                {
                    distances[v] = w + distances[u];
                }
            }
        }

        return distances;
    }
};

int main()
{
    vector<vector<int>> edges = {
        {0, 1, 2},
        {0, 2, 5},
        {1, 2, -10}};

    BellmanFord *bell = new BellmanFord("ndk");
    vector<int> v = bell->runAlgo(edges, 0, 3);

    for (int i = 0; i < 3; i++)
    {
        cout << i << "-> " << v[i] << endl;
    }

    return 0;
}