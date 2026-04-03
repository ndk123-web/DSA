#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <unordered_map>
#include <string>

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
        vector<int> distances(totalNodes, INT32_MAX);
        unordered_map<int, vector<pair<int, int>>> adjList;

        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adjList[u].push_back({w, v});
        }

        distances[src] = 0;
        pq.push({0, src});

        while (!pq.empty())
        {
            pair<int,int> p = pq.top();
            int dist = p.first;
            int node = p.second;

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
        {0, 1, 1},
        {0, 2, 4},
        {0, 3, 5},
        {1, 2, 1},
        {2, 3, 1}};

    Dijsktra dij("Ndk");
    auto v = dij.runDijkstra(edges,0,4);

    for (int i = 0 ; i < 4; i++) {
        cout << i << "-> " << v[i] << endl;
    }

    return 0;
}