## Merge Triplets to Form Target

### Intuition

The operation allows merging two triplets by taking the coordinate-wise maximum. Instead of simulating merges, observe that the final target can be constructed if each coordinate of the target is achievable independently from valid triplets.

A triplet is only useful if it does not exceed the target in any coordinate. Otherwise, it would introduce a value larger than the target during merging, making it impossible to reach the exact target.

---

### Key Idea

Filter out invalid triplets where:

```
ai > x OR bi > y OR ci > z
```

From the remaining valid triplets, check whether:

* There exists a triplet with `ai == x`
* There exists a triplet with `bi == y`
* There exists a triplet with `ci == z`

If all three conditions are satisfied, the target can be formed by merging these triplets.

---

### Approach

1. Initialize three boolean flags:

   * `a` for first coordinate
   * `b` for second coordinate
   * `c` for third coordinate

2. Iterate through each triplet:

   * Skip if it exceeds target in any dimension
   * Otherwise, update flags if it matches target values

3. Return `true` if all flags are true, otherwise `false`

---

### Code

```cpp
class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        bool a = false, b = false, c = false;
        
        for (auto& t : triplets) {
            if (t[0] > target[0] || t[1] > target[1] || t[2] > target[2]) {
                continue;
            }

            if (t[0] == target[0]) a = true;
            if (t[1] == target[1]) b = true;
            if (t[2] == target[2]) c = true;
        }

        return a && b && c;
    }
};
```

---

### Example

```
Input:
triplets = [[1,2,3],[7,1,1]]
target = [7,2,3]

Valid triplets:
[1,2,3], [7,1,1]

Coordinates found:
7 from [7,1,1]
2 from [1,2,3]
3 from [1,2,3]

Output: true
```

---

### Complexity

* Time Complexity: O(n)
* Space Complexity: O(1)

---

### Why This Works

The merge operation is associative and commutative with respect to the max function. Therefore, achieving each coordinate independently guarantees that combining those triplets will result in the target.
