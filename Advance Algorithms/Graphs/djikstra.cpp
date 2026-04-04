#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <unordered_map>
#include <string>
#include <climits>

using namespace std;

class Dijsktra
{
private:
    string name;

public:
    Dijsktra(string name)
    {
        this->name = name;
    }

    vector<int> runDijkstra(vector<vector<int>> &edges, int src, int totalNodes)
    {

        // min heap
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        // min distances with INT_MAX
        vector<int> distances(totalNodes, INT_MAX);

        // Adjacency List (src -> (weight, dest))
        unordered_map<int, vector<pair<int, int>>> adjList;

        // 1. Build Adjacency List
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adjList[u].push_back({w, v});
        }

        // src dist = 0
        distances[src] = 0;

        // in min heap push the weight 0 with start node
        pq.push({0, src});

        while (!pq.empty())
        {
            pair<int, int> current = pq.top();
            int dist = current.first;
            int node = current.second;

            pq.pop();

            for (auto &edge : adjList[node])
            {
                int weight = edge.first;
                int neigbour = edge.second;

                if (dist + weight < distances[neigbour])
                {
                    distances[neigbour] = dist + weight;
                    pq.push({distances[neigbour], neigbour});
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

    Dijsktra dij("Ndk");
    auto v = dij.runDijkstra(edges, 0, 4);

    for (int i = 0; i < 4; i++)
    {
        cout << i << "-> " << v[i] << endl;
    }

    return 0;
}