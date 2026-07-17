## Graph Lists

### [Pattern-1: Basic Foundation]
1. Number of Islands [Leetcode 200](https://leetcode.com/problems/number-of-islands/)
   - Trick: Use DFS or BFS to traverse the grid and mark visited land cells. Count the number of times you initiate a DFS/BFS from an unvisited land cell.
   - Time -> O(M*N), Space -> O(M*N) for recursion stack or queue