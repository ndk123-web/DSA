# Diameter of Binary Tree (C++)

## Problem Statement

Given the root of a binary tree, return the **diameter of the tree**.

**Diameter**:

- Longest path between **any two nodes** in the tree
- Path **may or may not pass through the root**
- Diameter is measured in **number of edges**

---

## Key Insight

> **Diameter ≠ Root-based calculation**

The longest path can pass through **any node**, not necessarily the root.

So:

- Har node ko possible center maana jaata hai
- Us node ka contribution = `leftHeight + rightHeight`

---

## Approach (Standard & Accepted)

We use **post-order recursion**.

### Two things ek saath karte hain:

1. **Height calculate karna**
2. **Diameter update karna**

---

## Height Definition (Important)

```text
height(node) = 1 + max(height(left), height(right))
```

- `NULL` node → height `0`
- Leaf node → height `1`

---

## Algorithm

1. Agar node `NULL` hai → height `0`
2. Left subtree ki height nikalo
3. Right subtree ki height nikalo
4. Current node ka diameter:

   ```
   lh + rh
   ```

5. Global answer update karo
6. Height return karo

---

## Code

```cpp
class Solution {
private:
    int ans = 0;

    int height(TreeNode* node) {
        if (!node) return 0;

        int lh = height(node->left);
        int rh = height(node->right);

        ans = max(ans, lh + rh);
        return 1 + max(lh, rh);
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        height(root);
        return ans;
    }
};
```

---

## Why This Works

- Har node pe diameter check hota hai
- Root pe depend nahi karta
- Longest possible path capture hota hai

---

## Example

```
        1
       /
      2
     /
    3
   / \
  4   5
```

- Diameter path: `4 → 3 → 5`
- Output: `2` (edges)

Correctly handled by this approach.

---

## Complexity Analysis

- **Time Complexity:** `O(n)`

  - Har node ek baar visit hota hai

- **Space Complexity:** `O(h)`

  - Recursive stack
  - `h` = height of tree

---

## Common Mistakes (Avoid These)

- Sirf root ke through diameter check karna ❌
- Depth ko manually carry karna ❌
- Height aur depth ka difference confuse karna ❌

---

## Conclusion

- Diameter ek **global property** hai
- Height ek **local return value**
- Dono ko combine karna hi correct solution hai
