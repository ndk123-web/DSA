    # Kth Smallest Element in a BST

---

## 🔑 Core Observation (VERY IMPORTANT)

> **Inorder traversal of a BST gives values in sorted order**

So:

- 1st smallest → first inorder node
- k-th smallest → k-th inorder node

---

# ✅ Solution 1: Inorder Traversal + Store All Values

---

## Intuition (WHY)

BST ka inorder traversal already **sorted order** deta hai.
So agar hum poora inorder traversal store kar lein,
to **k-th index directly answer** hoga.

This is the **most straightforward** solution.

---

## Approach (WHAT)

- Perform inorder traversal
- Store values in a vector
- Return `vector[k-1]`

---

## How (STEP-BY-STEP)

1. Traverse left subtree
2. Store current node value
3. Traverse right subtree
4. After traversal, vector is sorted
5. Return `nums[k-1]`

---

## Dry Run

### Tree

```
        5
       / \
      3   7
     / \
    2   4
```

Inorder traversal:

```
[2, 3, 4, 5, 7]
```

If `k = 3`
Answer = `nums[2] = 4`

---

## Complexity

- **Time Complexity:**
  $$O(n)$$
  (full traversal)

- **Space Complexity:**
  $$O(n)$$
  (vector storage + recursion stack)

---

## Code

```cpp
class Solution {
private:
    vector<int> nums;

    void generate(TreeNode* root) {
        if (!root) return;

        generate(root->left);
        nums.push_back(root->val);
        generate(root->right);
    }

public:
    int kthSmallest(TreeNode* root, int k) {
        if (!root) return -1;
        generate(root);
        return nums[k - 1];
    }
};
```

---

## Verdict

✅ Very easy
❌ Uses extra memory
❌ Not optimal if only k-th is needed

---

# ✅ Solution 2: Inorder Traversal with Early Stop (Optimized DFS)

---

## Intuition (WHY)

We **don’t need all values**.
We only care about the **k-th** inorder node.

So instead of storing everything:

- Maintain a counter
- Decrease it during inorder traversal
- Stop when counter becomes `0`

---

## Approach (WHAT)

- Use inorder traversal
- Pass `k` by reference
- Decrement `k` at each node visit
- When `k == 0`, store answer and stop recursion

---

## How (STEP-BY-STEP)

1. Traverse left subtree
2. Visit current node → decrement `k`
3. If `k == 0`, this is the answer
4. Traverse right subtree only if needed

---

## Dry Run

### Tree

```
        5
       / \
      3   7
     / \
    2   4
```

Inorder visit order:

```
2 → 3 → 4 → 5 → 7
```

If `k = 3`:

- Visit `2` → k = 2
- Visit `3` → k = 1
- Visit `4` → k = 0 ✅ → answer = 4

Traversal stops early.

---

## Complexity

- **Time Complexity:**
  $$O(h + k)$$ (average)
  $$O(n)$$ (worst case)

- **Space Complexity:**
  $$O(h)$$
  (recursion stack only)

---

## Code

```cpp
class Solution {
private:
    void kth(TreeNode* root, vector<int>& res) {
        if (!root)
            return;

        kth(root->left, res);

        res[0]--;   // decrement k

        if (res[0] == 0) {
            res[1] = root->val;
            return;
        }

        kth(root->right, res);
    }

public:
    int kthSmallest(TreeNode* root, int k) {
        vector<int> res(2);
        res[0] = k;   // remaining k
        kth(root, res);
        return res[1];
    }
};
```

---

## Why `vector<int> res` is used

```cpp
res[0] → remaining k
res[1] → answer
```

Because:

- C++ passes primitives by value
- Vector allows shared mutable state across recursive calls

(Alternative: use class variable or references)

---

## Final Comparison

| Aspect               | Solution 1   | Solution 2         |
| -------------------- | ------------ | ------------------ |
| Traversal            | Full inorder | Early stop inorder |
| Extra memory         | O(n)         | O(1)               |
| Speed                | Slower       | Faster             |
| Interview preference | ❌           | ✅                 |
| Simplicity           | ⭐⭐⭐⭐     | ⭐⭐⭐             |
