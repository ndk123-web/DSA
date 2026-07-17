## Graph Lists

### [Pattern-1: Basic Foundation]
1. Number of Islands [Leetcode 200](https://leetcode.com/problems/number-of-islands/)
   - Trick: Use DFS or BFS to traverse the grid and mark visited land cells. Count the number of times you initiate a DFS/BFS from an unvisited land cell.
   - Time -> O(M*N), Space -> O(M*N) for recursion stack or queue

### [Pattern-2: Connected Components]
1. Redundant Connection [Leetcode 684](https://leetcode.com/problems/redundant-connection/)
   - Trick: Use Union-Find (Disjoint Set Union) to detect cycles in the graph. If two nodes are already connected, adding an edge between them creates a cycle.
   - Time -> O(N * α(N)), Space -> O(N)
```cpp
class Solution {
public:
    vector<int> res, parents;

    int find(int node) {
        if (node == parents[node])
            return node;

        return parents[node] = find(parents[node]);
    }

    bool unite(int u, int v) {
        int pu = find(u);
        int pv = find(v);

        if (pu == pv) {
            res.push_back(u);
            res.push_back(v);
            return false;
        }

        parents[pv] = pu;
        return true;
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        this->parents.resize(n + 1);

        for (int i = 0; i < n; i++)
            parents[i] = i;

        for (vector<int>& edge : edges) {
            if (!unite(edge[0], edge[1]))
                break;
        }

        return res;
    }
};
```

2. Number Of Provinces [Leetcode 547](https://leetcode.com/problems/number-of-provinces/)
   - Trick: Use DFS or BFS to traverse the graph and count the number of connected components. Each time you initiate a DFS/BFS from an unvisited node, increment the province count.
   - Time -> O(N^2), Space -> O(N) for recursion stack or queue
```cpp
class Solution {
public:
    vector<int> parents;

    int find(int node) {
        if (node == parents[node])
            return node;

        return parents[node] = find(parents[node]);
    }

    void unite(int u, int v) {
        int pu = find(u);
        int pv = find(v);

        if (pu == pv)
            return;

        parents[pv] = pu;
        return;
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected[0].size();
        this->parents.resize(n);

        for (int i = 0; i < n; i++)
            parents[i] = i;

        int t = 0;
        for (vector<int>& g : isConnected) {

            for (int i = 0; i < g.size(); i++) {
                if (i == t)
                    continue;
                    
                if (g[i] == 1)
                    unite(t, i);
            }

            t++;
        }

        for (int i = 0; i < n; i++) {
            find(i);
        }

        int res = 0;
        unordered_set<int> sett;
        for (int i = 0; i < n; i++) {
            sett.insert(parents[i]);
        }

        return sett.size();
    }
};
```