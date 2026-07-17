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

### [Pattern-3 Topological Sort (Kahn's Algorithm)]
1. Course Schedule [Leetcode 207](https://leetcode.com/problems/course-schedule/)
   - Trick: Use Kahn's algorithm for topological sorting. Count the number of nodes processed. If it equals the total number of courses, return true; otherwise, return false.
   - Time -> O(V + E), Space -> O(V + E)
```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);
        queue<int> q;

        for (auto& course : prerequisites) {
            
            // meaning we cant start with course[0] until we finish course[1], so we increase the indegree of course[0] and add course[0] to the adjacency list of course[1]
            indegree[course[0]]++;

            // meaning to further remove the dependency of course[0], we need to finish course[1] first, so we add course[0] to the adjacency list of course[1]
            adj[course[1]].push_back(course[0]);
        }

        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }

        int finish = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            finish++;

            for (auto& nei : adj[course]) {
                indegree[nei]--;
                if (indegree[nei] == 0)
                    q.push(nei);
            }
        }

        return finish == numCourses;
    }
};
```

2. Course Schedule II [Leetcode 210](https://leetcode.com/problems/course-schedule-ii/)
   - Trick: Similar to Course Schedule, but instead of just checking if it's possible to finish all courses, we need to return the order of courses. Use Kahn's algorithm and maintain a list of the order in which courses are completed.
   - Time -> O(V + E), Space -> O(V + E)
```cpp
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);
        queue<int> q;
        vector<int> res;

        for (auto& course : prerequisites) {
            indegree[course[0]]++;
            adj[course[1]].push_back(course[0]);
        }

        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }

        int finish = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            finish++;
            res.push_back(course);

            for (auto& nei : adj[course]) {
                indegree[nei]--;
                if (indegree[nei] == 0)
                    q.push(nei);
            }
        }

        if (numCourses == finish)
            return res;

        return {};
    }
};
```