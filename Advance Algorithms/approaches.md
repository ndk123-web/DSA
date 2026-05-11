## Approaches 

1. Graph
   1. Dijsktra
      - To Find shortest between (src, target) 
      - can be used for both `weighted and unweighted graph`
      - Time Complexity: O(E log V)
      - Space Complexity: O(V + E)
      - Cannot handle negative weight edges.
      - Uses a priority queue to always expand the least costly edge next, which is efficient for dense graphs.
  
  2. Bellman Ford 
       - To Find shortest between (src, target)
       - can be used for both `weighted and unweighted graph`
       - Time Complexity: O(V * E)
       - Space Complexity: O(V)
       - Can handle negative weight edges, but not negative weight cycles. 
       - Iteratively relaxes edges up to V-1 times, which is less efficient than Dijkstra's for sparse graphs but necessary for graphs with negative weights.
  
  3. Floyd Warshall
       - To Find shortest between all pairs of vertices
       - can be used for both `weighted and unweighted graph`
       - Time Complexity: O(V^3)
       - Space Complexity: O(V^2)
       - Can handle negative weight edges, but not negative weight cycles.
       - Uses dynamic programming to iteratively update a distance matrix, which is straightforward but inefficient for large graphs compared to Dijkstra's or Bellman-Ford for single-source shortest paths.
  
  4. Prim's Algorithm
       - To Find Minimum Spanning Tree (MST)
       - can be used for both `weighted and unweighted graph`
       - Time Complexity: O(E log V)
       - Space Complexity: O(V + E)
       - Cannot handle negative weight edges.
       - Uses a priority queue to always expand the least costly edge next, which is efficient for dense graphs.
  
  5. Kruskal's Algorithm
       - To Find Minimum Spanning Tree (MST)
       - can be used for both `weighted and unweighted graph`
       - Time Complexity: O(E log E) (or O(E log V) with Union-Find)
       - Space Complexity: O(V + E)
       - Cannot handle negative weight edges.
       - Requires sorting of edges, which is the main bottleneck.
       - Uses a Union-Find data structure to efficiently detect cycles when building the MST, which is effective for sparse graphs.

2. DP 
   1. Top-Down (Memoization)
       - To solve problems with overlapping subproblems and optimal substructure.
       - Time Complexity: O(N) or O(N * M) depending on the problem.
       - Space Complexity: O(N) for the recursion stack + O(N) for memoization.
       - Can be less efficient than bottom-up due to recursion overhead, but often easier to implement and understand.

   2. Bottom-Up (Tabulation)
       - To solve problems with overlapping subproblems and optimal substructure.
       - Time Complexity: O(N) or O(N * M) depending on the problem.
       - Space Complexity: O(N) or O(N * M) depending on the problem.
       - Generally more efficient than top-down due to iterative approach and better cache locality, but can be more complex to implement.

3. Detect Cycle In Graph
   1. DFS 
       - To detect cycles in a `directed or undirected graph`.
       - Time Complexity: O(V + E)
       - Space Complexity: O(V) for the recursion stack and visited set.
       - Can be used for both directed and undirected graphs, but the logic differs slightly (e.g., checking for back edges in directed graphs).

   2. Union-Find (Disjoint Set Union)
       - To detect cycles in an `undirected graph`.
       - Time Complexity: O(E α(V)) where α is the inverse Ackermann function, which is very slow-growing and almost constant for all practical purposes.
       - Space Complexity: O(V) for the parent and rank arrays.
       - Only applicable to undirected graphs, as it relies on the concept of connected components.
  
  3. Kahn's Algorithm (Topological Sort)
       - To detect cycles in a `directed graph`.
       - Time Complexity: O(V + E)
       - Space Complexity: O(V) for the in-degree array and queue.
       - Only applicable to directed graphs, as it relies on the concept of in-degrees and topological ordering.
  
  4. DFS with Coloring
       - To detect cycles in a `directed graph`.
       - Time Complexity: O(V + E)
       - Space Complexity: O(V) for the recursion stack and color array.
       - Only applicable to directed graphs, as it uses a color-coding scheme to track the state of each vertex during DFS.