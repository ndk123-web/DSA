# Ultimate Master DSA Pattern Revision Sheet

> **Goal**: One single file to revise **all core DSA patterns, keyword triggers, visual mental models, and template code** before coding interviews.

---

## ⚡ Master Problem-to-Pattern Keyword Matrix

When reading any DSA problem statement, use this fast mental lookup table:

| Problem Statement Keywords | Data Structure / Technique | Core Mental Model / Pattern |
|---|---|---|
| *"Contiguous subarray / substring of length K or condition X"* | **Sliding Window** | Expand `right`, shrink `left` when condition breaks |
| *"Sorted array / Search in $O(\log N)$ / Find Min/Max boundary"* | **Binary Search** | Mid calculation, search space reduction |
| *"Pair sum in sorted array / Palindrome / Partition"* | **Two Pointers** | `left` at start, `right` at end |
| *"Subarray sum equals K / Continuous range sums"* | **Prefix Sum + Hash Map** | $P[j] - P[i-1] = K \implies P[i-1] = P[j] - K$ |
| *"Next Greater Element / Next Smaller / Histogram Area"* | **Monotonic Stack** | Stack stores monotonic indices |
| *"Top K elements / Kth Smallest / Median of Stream"* | **Min/Max Heap** | Priority Queue of size $K$ |
| *"All combinations / Permutations / Subsets / Grid path exploration"* | **Backtracking** | Choose $\rightarrow$ Explore $\rightarrow$ Unchoose (Pop) |
| *"Shortest path in unweighted graph / Level order traversal"* | **BFS (Queue)** | Queue + `visited` set |
| *"Connected components / Cycle detection / Topological order"* | **DFS / Union-Find / Kahn's** | Recursion stack or Disjoint Set Union (DSU) |
| *"Shortest path with non-negative edge weights"* | **Dijkstra's Algorithm** | Priority Queue storing `(distance, node)` |
| *"Min/Max total cost with overlapping subproblems"* | **Dynamic Programming** | State definition $\rightarrow$ Recurrence relation $\rightarrow$ Memo/Tabulation |
| *"Prefix matching / Auto-complete / Word Search"* | **Trie (Prefix Tree)** | Tree of 26-child nodes |

---

# 1. Array & Two Pointers

### ⚡ Patterns:
1. **Opposite Direction Pointers** (Two Sum II, Valid Palindrome, Container With Most Water)
2. **Fast & Slow Pointers** (Cycle Detection, Remove Duplicates)
3. **Dutch National Flag / 3-Pointers** (Sort Colors 0s, 1s, 2s)

### 💻 Template: Opposite Pointers
```cpp
int left = 0, right = n - 1;
while (left < right) {
    int current_sum = nums[left] + nums[right];
    if (current_sum == target) return {left, right};
    else if (current_sum < target) left++;
    else right--;
}
```

---

# 2. Sliding Window Pattern

### ⚡ Patterns:
1. **Fixed Window Size $K$** (Max Sum Subarray of size $K$)
2. **Variable Window Size** (Longest Substring Without Repeating Characters, Minimum Window Substring)

### 💻 Template: Dynamic Variable Window
```cpp
unordered_map<char, int> freq;
int left = 0, max_len = 0;

for (int right = 0; right < s.length(); right++) {
    freq[s[right]]++;
    
    // Shrink window if condition is violated
    while (/* invalid condition e.g. freq[s[right]] > 1 */) {
        freq[s[left]]--;
        if (freq[s[left]] == 0) freq.erase(s[left]);
        left++;
    }
    
    max_len = max(max_len, right - left + 1);
}
```

---

# 3. Prefix Sum + Hash Map

⚡ **Key Formula**: $\text{SubarraySum}(i, j) = \text{Prefix}[j] - \text{Prefix}[i-1] = K$.

### 💻 Template: Subarray Sum Equals K
```cpp
int count = 0, current_sum = 0;
unordered_map<int, int> prefix_counts;
prefix_counts[0] = 1; // Base case: empty prefix

for (int num : nums) {
    current_sum += num;
    if (prefix_counts.count(current_sum - k)) {
        count += prefix_counts[current_sum - k];
    }
    prefix_counts[current_sum]++;
}
```

---

# 4. Binary Search & Search Space Optimization

### ⚡ Patterns:
1. **Classic Binary Search** (Find index of target in sorted array)
2. **Binary Search on Answer** (Capacity To Ship Packages, Koko Eating Bananas, Minimized Maximum)

### 💻 Template: Binary Search on Answer Space
```cpp
int low = min_possible, high = max_possible, ans = -1;
while (low <= high) {
    int mid = low + (high - low) / 2;
    if (isValid(mid, nums, k)) {
        ans = mid;        // Store feasible answer
        high = mid - 1;   // Try searching for smaller valid value (Minimization)
    } else {
        low = mid + 1;
    }
}
```

---

# 5. Monotonic Stack Pattern

⚡ **Mental Hook**: Maintained stack elements are strictly increasing or decreasing.
- **Next Greater Element**: Decreasing Stack (top is smaller).
- **Next Smaller Element**: Increasing Stack (top is larger).

### 💻 Template: Next Greater Element
```cpp
vector<int> res(n, -1);
stack<int> st; // Stores indices

for (int i = 0; i < n; i++) {
    while (!st.empty() && nums[st.top()] < nums[i]) {
        res[st.top()] = nums[i];
        st.pop();
    }
    st.push(i);
}
```

---

# 6. Linked List Fast/Slow & In-Place Reversal

### ⚡ Key Tricks:
- **Cycle Detection**: `slow = slow->next`, `fast = fast->next->next`.
- **Finding Middle**: When `fast` reaches end, `slow` is at middle.
- **In-place Reversal**: Maintain `prev`, `curr`, `next_node`.

### 💻 Template: In-Place Reversal
```cpp
ListNode* prev = nullptr, *curr = head;
while (curr != nullptr) {
    ListNode* next_node = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next_node;
}
return prev; // New head
```

---

# 7. Binary Trees & BST Patterns

### ⚡ Traversal Patterns:
- **DFS Traversals**: Preorder (Root-L-R), Inorder (L-Root-R $\rightarrow$ Sorted for BST), Postorder (L-R-Root).
- **BFS Level Order**: Queue with inner `size` loop.
- **Tree Diameter / Max Path Sum**: Return bottom-up height to parent while updating global `ans = max(ans, left + right + node->val)`.

### 💻 Template: BFS Level Order Traversal
```cpp
vector<vector<int>> res;
if (!root) return res;
queue<TreeNode*> q;
q.push(root);

while (!q.empty()) {
    int level_size = q.size();
    vector<int> level_nodes;
    for (int i = 0; i < level_size; i++) {
        TreeNode* curr = q.front(); q.pop();
        level_nodes.push_back(curr->val);
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    res.push_back(level_nodes);
}
```

---

# 8. Heaps & Priority Queues (Top-K Pattern)

⚡ **Mental Hook**:
- To find **Top K Largest** elements $\rightarrow$ Use **Min-Heap** of size $K$.
- To find **Top K Smallest** elements $\rightarrow$ Use **Max-Heap** of size $K$.

### 💻 Template: Kth Largest Element
```cpp
priority_queue<int, vector<int>, greater<int>> min_heap; // Min heap
for (int num : nums) {
    min_heap.push(num);
    if (min_heap.size() > k) {
        min_heap.pop(); // Evict smallest
    }
}
return min_heap.top(); // Kth largest remains at top
```

---

# 9. Backtracking (Subsets, Permutations, Combinations)

### 💻 Template: Standard Backtracking
```cpp
void backtrack(int start, vector<int>& nums, vector<int>& path, vector<vector<int>>& res) {
    res.push_back(path); // Record decision state
    
    for (int i = start; i < nums.size(); i++) {
        // Handle duplicates if sorted: if (i > start && nums[i] == nums[i-1]) continue;
        path.push_back(nums[i]);                  // CHOOSE
        backtrack(i + 1, nums, path, res);        // EXPLORE
        path.pop_back();                          // UNCHOOSE (Backtrack)
    }
}
```

---

# 10. Graphs: BFS, DFS, Union-Find & Dijkstra

### ⚡ Decision Tree:
- **Unweighted Shortest Path** $\rightarrow$ **BFS**
- **Cycle Detection / Connected Components** $\rightarrow$ **DFS / Union-Find**
- **Dependency Ordering / Pre-requisites** $\rightarrow$ **Topological Sort (Kahn's Algorithm - In-degree Queue)**
- **Weighted Shortest Path ($w \ge 0$)** $\rightarrow$ **Dijkstra's Algorithm**

### 💻 Template: Dijkstra's Algorithm
```cpp
vector<int> dist(V, INT_MAX);
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

dist[src] = 0;
pq.push({0, src}); // {distance, node}

while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;
    
    for (auto& [v, weight] : adj[u]) {
        if (dist[u] + weight < dist[v]) {
            dist[v] = dist[u] + weight;
            pq.push({dist[v], v});
        }
    }
}
```

---

# 11. Dynamic Programming Patterns

| DP Category | State Definition | Transition Formula | Examples |
|---|---|---|---|
| **0/1 Knapsack** | `dp[i][w]` (Pick or Don't Pick item `i`) | `dp[i][w] = max(dp[i-1][w], val + dp[i-1][w-wt])` | Partition Equal Subset Sum, Target Sum |
| **Unbounded Knapsack** | `dp[w]` (Reuse item multiple times) | `dp[w] = min(dp[w], 1 + dp[w - coin])` | Coin Change, Rod Cutting |
| **LCS (Subsequence)** | `dp[i][j]` (LCS of `s1[0..i]` & `s2[0..j]`) | `s1[i]==s2[j] ? 1+dp[i-1][j-1] : max(dp[i-1][j], dp[i][j-1])` | Longest Common Subsequence, Edit Distance |
| **LIS (Increasing)** | `dp[i]` (Max LIS ending at index `i`) | `dp[i] = max(1, 1 + dp[j])` for all $j < i$ & $nums[j] < nums[i]$ | Longest Increasing Subsequence ($O(N \log N)$ with Binary Search) |

---

# 12. Quick Time Complexity Master Reference

| Algorithm / Operation | Time Complexity | Space Complexity |
|---|---|---|
| Hash Map Lookup / Insert | $O(1)$ avg, $O(N)$ worst | $O(N)$ |
| Priority Queue Push / Pop | $O(\log K)$ | $O(K)$ |
| Binary Search | $O(\log N)$ | $O(1)$ |
| Sorting (Merge / Quick Sort) | $O(N \log N)$ | $O(N)$ or $O(\log N)$ |
| Tree / Graph Traversal (DFS/BFS) | $O(V + E)$ | $O(V)$ |
| Dijkstra's Shortest Path | $O((V + E) \log V)$ | $O(V + E)$ |
| Topological Sort (Kahn's) | $O(V + E)$ | $O(V)$ |
