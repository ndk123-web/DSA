#include <iostream>
#include <vector>
#include <queue>
#include <string>

class Dijsktra {
    private:
        string name;
    public:
        Dijsktra(string name) {
            this->name = name;
        }

        vector<int> runDijkstra(vector<vector<int>>& edges, int src, int totalNodes) {

            // min heap
            priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
            vector<int> distances(totalNodes, INT_MAX);
            unordered_map<int, vector<pair<int,int>>> adjList;

            for (auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];

                adjList[u].push_back({v,w});
            }

            distances[src] = 0;
            pq.push({0,src});

            while (!pq.empty()) {
                auto& [dist, node] = pq.top();
                pq.pop();

                for (auto& edge : edges[node]) {
                    int neigbour = edge[1];
                    int weight = edge[2];

                    if (dist + weight < distances[neigbour]) {
                        distances[neigbour] = dist + weight;
                        pq.push({distances[neigbour], neigbour});
                    }
                }
            }

            return distances
        }
};

int main () {

    vector<vector<int>> edges = {
        {0,1,1},
        {0,2, 4},
        {0, 3, 5},
        {1, 2, 1},
        {2,3, 1};
    }
    Dijsktra* dij("ndk");

    dij->runDijkstra(edges, 0, 4);    

    return 0;
}