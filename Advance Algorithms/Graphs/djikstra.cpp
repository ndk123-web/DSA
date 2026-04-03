#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

class Dijsktra
{
public:
    vector<tuple<int, int, int>> edges;

    vector<vector<int>> algoRun(vector<tuple<int, int, int>> &edges, int startNode, int totalNodes)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> dist(totalNodes, INT_FAST32_MAX);

        // added startNode with distance
        pq.push({0, startNode});

        while (!pq.empty())
        {

            // here edge is [from, to, weight]
            for (auto &edge : edges)
            {
                
            }
        }
    }
};

int main()
{
    vector<tuple<int, int, int>> edges = {
        {0, 1, 3},
        {1, 2, 5},
        {0, 3, 2},
        {2, 3, 5},
        {1, 3, 3},
        {0, 3, 10}};

    Dijsktra dij;
    int startNode = 0;
    int totalNodes = 4;
    vector<vector<int>> ans = dij.algoRun(edges, startNode, totalNodes);
    return 0;
}