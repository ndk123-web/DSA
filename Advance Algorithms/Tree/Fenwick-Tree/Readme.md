## Fenwick Tree


1. **Introduction**: Fenwick Tree, also known as Binary Indexed Tree (BIT), is a data structure that provides efficient methods for cumulative frequency tables or prefix sums. It allows for both point updates and prefix sum queries in logarithmic time.

- Operations with Time Complexity:
    - **Update**: Increment the value at a specific index in O(log n) time.
    - **Query**: Calculate the prefix sum up to a specific index in O(log n
    - **Space Complexity**: O(n), where n is the number of elements in the array.
    - **Applications**: Fenwick Trees are widely used in scenarios where we need to perform frequent updates and queries on an array, such as in competitive programming, range sum queries, and inversion counting.