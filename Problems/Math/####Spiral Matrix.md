# Spiral Matrix

## Intuition

The problem requires traversing a matrix in spiral order. Instead of trying to simulate direction changes manually, we can define **four boundaries**:

* `top` → top row
* `bottom` → bottom row
* `left` → left column
* `right` → right column

We traverse layer by layer:

1. Left → Right (top row)
2. Top → Bottom (right column)
3. Right → Left (bottom row)
4. Bottom → Top (left column)

After each traversal, we shrink the corresponding boundary inward.

---

## Logic

1. Initialize boundaries:

   * `top = 0`, `bottom = n - 1`
   * `left = 0`, `right = m - 1`

2. While boundaries are valid:

   * Traverse top row → increment `top`
   * Traverse right column → decrement `right`
   * Traverse bottom row → decrement `bottom`
   * Traverse left column → increment `left`

3. After each step, check if boundaries are still valid to avoid duplicate traversal.

---

## Approach

### Steps

* Use a loop while `top <= bottom && left <= right`
* Traverse in 4 directions
* Update boundaries after each traversal
* Add boundary checks to prevent over-traversal

---

## Code

```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int r = matrix.size() - 1, c = matrix[0].size() - 1;
        int top = 0, left = 0, right = c, bottom = r;
        vector<int> res;

        while (left <= right && top <= bottom) {

            // Traverse top row
            for (int i = left; i <= right; i++) {
                res.push_back(matrix[top][i]);
            }
            top++;

            // Check if rows exhausted
            if (top > bottom)
                break;

            // Traverse right column
            for (int i = top; i <= bottom; i++) {
                res.push_back(matrix[i][right]);
            }
            right--;

            // Check if columns exhausted
            if (left > right)
                break;

            // Traverse bottom row
            for (int i = right; i >= left; i--) {
                res.push_back(matrix[bottom][i]);
            }
            bottom--;

            // Check again for row validity
            if (top > bottom)
                break;

            // Traverse left column
            for (int i = bottom; i >= top; i--) {
                res.push_back(matrix[i][left]);
            }
            left++;
        }

        return res;
    }
};
```

---

## Complexity Analysis

* Time Complexity: O(n × m)
  Every element is visited exactly once.

* Space Complexity: O(1) (excluding output)
  No extra space used apart from result storage.

---

## Key Insight

* Spiral traversal is controlled by boundaries, not direction flags.
* Each iteration processes one “layer” of the matrix.
* Boundary checks after each traversal prevent duplicates and out-of-bounds access.

---

## Notes

* Works for all cases:

  * square matrix
  * single row
  * single column
* Using `<=` ensures last row/column is processed
* Boundary checks are critical for correctness
