# C++ DSA Revision Sheet — Write From Scratch

Goal: pattern recognition + implementation fluency. This is a curated **150-problem core sheet**, not 150 per individual technique (which would become thousands of problems). Your repo already tracks C++ foundations/STL; focus here on algorithmic recall.

## Rules for every problem
- [x] Identify the pattern before coding.
- [x] Write the brute-force idea and complexity in 1–2 lines.
- [x] Implement from a blank file in C++ (no looking at old solutions).
- [x] Test edge cases: empty/single element, duplicates, negatives, overflow, already sorted/reverse sorted as relevant.
- [x] State time and auxiliary-space complexity.
- [x] If stuck: 20 minutes of honest attempt, then inspect only the key idea; close it and re-implement.
- [x] Revisit misses after 1 day, 3 days, and 7 days.

Mark each problem: **G** = solved cleanly from scratch; **Y** = needed a hint / bug fix; **R** = could not derive it. Revise Y/R again.

## Phase 0 — C++ / STL quick warm-up (not counted in 150)
- [x] vector, string, references, const, pass-by-reference
- [x] sort + custom comparator, lower_bound / upper_bound
- [x] unordered_map / unordered_set vs map / set
- [x] stack, queue, deque, priority_queue
- [x] pair, tuple, structured bindings
- [x] recursion stack, integer overflow, long long
- [x] complexity: O(1), O(log n), O(n), O(n log n), O(n²)

---

# A. Arrays, Hashing & Prefix/Suffix (1–18)
1. [x] Two Sum — 1
2. [x] Contains Duplicate — 217
3. [x] Best Time to Buy and Sell Stock — 121
4. [x] Product of Array Except Self — 238
5. [x] Maximum Subarray — 53
6. [x] Majority Element — 169
7. [x] Sort Colors — 75
8. [x] Missing Number — 268
9. [x] Find All Numbers Disappeared in an Array — 448
10. [x] Longest Consecutive Sequence — 128
11. [x] Subarray Sum Equals K — 560
12. [x] Continuous Subarray Sum — 523
13. [x] Range Sum Query - Immutable — 303
14. [x] Find Pivot Index — 724
15. [x] Maximum Product Subarray — 152
16. [x] First Missing Positive — 41
17. [x] Set Matrix Zeroes — 73
18. [x] Spiral Matrix — 54

# B. Two Pointers (19–30)
19. [x] Valid Palindrome — 125
20. [x] Two Sum II - Input Array Is Sorted — 167
21. [x] 3Sum — 15
22. [x] 4Sum — 18
23. [x] Container With Most Water — 11
24. [ ] Remove Duplicates from Sorted Array — 26
25. [ ] Move Zeroes — 283
26. [ ] Squares of a Sorted Array — 977
27. [ ] Trapping Rain Water — 42
28. [ ] Sort Array By Parity — 905
29. [ ] Backspace String Compare — 844
30. [ ] Is Subsequence — 392

# C. Sliding Window (31–42)
31. [ ] Maximum Average Subarray I — 643
32. [ ] Longest Substring Without Repeating Characters — 3
33. [ ] Longest Repeating Character Replacement — 424
34. [ ] Permutation in String — 567
35. [ ] Find All Anagrams in a String — 438
36. [ ] Minimum Size Subarray Sum — 209
37. [ ] Max Consecutive Ones III — 1004
38. [ ] Fruit Into Baskets — 904
39. [ ] Minimum Window Substring — 76
40. [ ] Sliding Window Maximum — 239
41. [ ] Subarray Product Less Than K — 713
42. [ ] Count Number of Nice Subarrays — 1248

# D. Binary Search & Search on Answer (43–54)
43. [ ] Binary Search — 704
44. [ ] Search Insert Position — 35
45. [ ] Find First and Last Position of Element in Sorted Array — 34
46. [ ] Search in Rotated Sorted Array — 33
47. [ ] Find Minimum in Rotated Sorted Array — 153
48. [ ] Search a 2D Matrix — 74
49. [ ] Koko Eating Bananas — 875
50. [ ] Capacity To Ship Packages Within D Days — 1011
51. [ ] Split Array Largest Sum — 410
52. [ ] Median of Two Sorted Arrays — 4
53. [ ] Find Peak Element — 162
54. [ ] Time Based Key-Value Store — 981

# E. Stack, Monotonic Stack & Queue (55–66)
55. [ ] Valid Parentheses — 20
56. [ ] Min Stack — 155
57. [ ] Evaluate Reverse Polish Notation — 150
58. [ ] Daily Temperatures — 739
59. [ ] Next Greater Element II — 503
60. [ ] Largest Rectangle in Histogram — 84
61. [ ] Maximal Rectangle — 85
62. [ ] Asteroid Collision — 735
63. [ ] Decode String — 394
64. [ ] Implement Queue using Stacks — 232
65. [ ] Sliding Window Maximum — 239 (deque implementation)
66. [ ] Design Circular Queue — 622

# F. Linked Lists (67–76)
67. [ ] Reverse Linked List — 206
68. [ ] Merge Two Sorted Lists — 21
69. [ ] Linked List Cycle — 141
70. [ ] Linked List Cycle II — 142
71. [ ] Remove Nth Node From End of List — 19
72. [ ] Reorder List — 143
73. [ ] Add Two Numbers — 2
74. [ ] Copy List with Random Pointer — 138
75. [ ] LRU Cache — 146
76. [ ] Reverse Nodes in k-Group — 25

# G. Recursion & Backtracking (77–88)
77. [ ] Subsets — 78
78. [ ] Subsets II — 90
79. [ ] Permutations — 46
80. [ ] Permutations II — 47
81. [ ] Combination Sum — 39
82. [ ] Combination Sum II — 40
83. [ ] Letter Combinations of a Phone Number — 17
84. [ ] Generate Parentheses — 22
85. [ ] Word Search — 79
86. [ ] Palindrome Partitioning — 131
87. [ ] N-Queens — 51
88. [ ] Sudoku Solver — 37

# H. Trees & BST (89–104)
89. [ ] Maximum Depth of Binary Tree — 104
90. [ ] Binary Tree Level Order Traversal — 102
91. [ ] Diameter of Binary Tree — 543
92. [ ] Balanced Binary Tree — 110
93. [ ] Same Tree — 100
94. [ ] Binary Tree Right Side View — 199
95. [ ] Lowest Common Ancestor of a Binary Tree — 236
96. [ ] Validate Binary Search Tree — 98
97. [ ] Kth Smallest Element in a BST — 230
98. [ ] Construct Binary Tree from Preorder and Inorder Traversal — 105
99. [ ] Binary Tree Maximum Path Sum — 124
100. [ ] Path Sum III — 437
101. [ ] Serialize and Deserialize Binary Tree — 297
102. [ ] Binary Search Tree Iterator — 173
103. [ ] Delete Node in a BST — 450
104. [ ] Recover Binary Search Tree — 99

# I. Heap / Priority Queue (105–112)
105. [ ] Kth Largest Element in an Array — 215
106. [ ] Top K Frequent Elements — 347
107. [ ] Find Median from Data Stream — 295
108. [ ] K Closest Points to Origin — 973
109. [ ] Task Scheduler — 621
110. [ ] Find K Pairs with Smallest Sums — 373
111. [ ] Smallest Range Covering Elements from K Lists — 632
112. [ ] Reorganize String — 767

# J. Graphs, BFS/DFS, Topological Sort & DSU (113–128)
113. [ ] Number of Islands — 200
114. [ ] Clone Graph — 133
115. [ ] Max Area of Island — 695
116. [ ] Rotting Oranges — 994
117. [ ] Pacific Atlantic Water Flow — 417
118. [ ] Course Schedule — 207
119. [ ] Course Schedule II — 210
120. [ ] Number of Connected Components in an Undirected Graph — 323
121. [ ] Redundant Connection — 684
122. [ ] Graph Valid Tree — 261
123. [ ] Network Delay Time — 743
124. [ ] Cheapest Flights Within K Stops — 787
125. [ ] Word Ladder — 127
126. [ ] Min Cost to Connect All Points — 1584
127. [ ] Accounts Merge — 721
128. [ ] Is Graph Bipartite? — 785

# K. Dynamic Programming (129–144)
129. [ ] Climbing Stairs — 70
130. [ ] House Robber — 198
131. [ ] House Robber II — 213
132. [ ] Coin Change — 322
133. [ ] Coin Change II — 518
134. [ ] Longest Increasing Subsequence — 300
135. [ ] Longest Common Subsequence — 1143
136. [ ] Edit Distance — 72
137. [ ] Word Break — 139
138. [ ] Partition Equal Subset Sum — 416
139. [ ] Unique Paths — 62
140. [ ] Minimum Path Sum — 64
141. [ ] Decode Ways — 91
142. [ ] Combination Sum IV — 377
143. [ ] Best Time to Buy and Sell Stock with Cooldown — 309
144. [ ] Burst Balloons — 312

# L. Greedy, Intervals & Bit Manipulation (145–150)
145. [ ] Jump Game — 55
146. [ ] Jump Game II — 45
147. [ ] Merge Intervals — 56
148. [ ] Non-overlapping Intervals — 435
149. [ ] Single Number — 136
150. [ ] Counting Bits — 338

---

## Extra topics to cover after the 150
These are deliberately outside the main 150 so the core sheet remains doable:
- [ ] **Range queries:** Fenwick Tree / Binary Indexed Tree; Segment Tree; lazy propagation
- [ ] **Sparse Table:** immutable range min/max queries
- [ ] **Circular queue:** implemented in this sheet; practice invariants and full/empty cases
- [ ] **String algorithms:** KMP, Z-function, Rabin–Karp, Manacher
- [ ] **Advanced graph:** Bellman–Ford, Floyd–Warshall, bridges/articulation points, SCC (Kosaraju/Tarjan)
- [ ] **DP extensions:** bitmask DP, tree DP, digit DP, interval DP; optimize 2D DP to 1D where valid
- [ ] **Number theory:** GCD/LCM, sieve, modular arithmetic, fast exponentiation
- [ ] **Greedy proofs:** exchange argument, interval scheduling
- [ ] **Divide and conquer:** merge-sort counting, quickselect
- [ ] **Trie:** implement insert/search/prefix and solve Word Search II (212)
- [ ] **Monotonic queue and deque patterns**
- [ ] **DSU implementation with path compression + union by size/rank**

## Suggested schedule (college-friendly)
- Week 1: A–D (54 problems) — do 4–6 per study day; on exam-heavy days do 1.
- Week 2: E–H (50 problems) — prioritize the R/Y problems.
- Week 3: I–L (46 problems) — give graphs/DP full sessions; don't rush them.
- Every Sunday: redo all R problems and write the invariant/recurrence from memory.
- Do not call a problem revised just because you recognize the solution. It counts only when you can derive and implement it from a blank editor.
