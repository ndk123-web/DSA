#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <climits>

using namespace std;

class AstarAlgo
{
private:
    string name;

public:
    AstarAlgo(string name) : name(name) {}

    vector<int> runAlgo(vector<vector<int>> &edges, int startNode, int targetNode, int totalNode, vector<int> &heuristic)
    {
        vector<int> distances(totalNode, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        unordered_map<int, vector<pair<int, int>>> adjList;

        distances[startNode] = 0;

        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adjList[u].push_back({w, v});
        }

        int estimatedCost = heuristic[startNode] + distances[startNode];
        pq.push({estimatedCost, startNode});

        while (!pq.empty())
        {
            pair<int, int> p = pq.top();
            pq.pop();

            int cost = p.first;
            int node = p.second;

            if (node == targetNode)
            {
                break;
            }

            for (auto &p : adjList[node])
            {
                int w = p.first;
                int v = p.second;

                int newDist = distances[node] + w;

                if (distances[v] > newDist)
                {
                    distances[v] = newDist;
                    pq.push({newDist + heuristic[v], v});
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
        {2, 3, 1},
        {1, 3, 2}};

    vector<int> heuristic = {3, 2, 1, 0};

    int startNode = 0;  
    int targetNode = 3;
    int totalNode = 4;

    AstarAlgo *astar = new AstarAlgo("Ndk");
    vector<int> distances = astar->runAlgo(edges, startNode, targetNode, totalNode, heuristic);

    for (int i = 0; i < totalNode; i++)
    {
        cout << i << "-> " << distances[i] << endl;
    }

    return 0;
}