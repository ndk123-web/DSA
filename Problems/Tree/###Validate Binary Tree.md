# Validate Binary Search Tree (BST)

---

## 🔹 Solution 1: Range Validation (Top-Down DFS)

---

## Intuition (WHY)

A **Binary Search Tree** is not just about parent–child comparison.

The real rule is:

> For every node, **all values in the left subtree must be smaller**,
> and **all values in the right subtree must be greater**.

So instead of checking only immediate children,
we must ensure each node lies inside a **valid value range** decided by its ancestors.

---

## Approach (WHAT + HOW)

### WHAT

- Use DFS
- For every node, maintain a **valid range** `(left, right)`
- Check if `left < node->val < right`

### HOW

1. Start from root with range `(-∞, +∞)`
2. For left child:

   - New range becomes `(left, root->val)`

3. For right child:

   - New range becomes `(root->val, right)`

4. If any node violates the range → BST is invalid
5. If all nodes satisfy → valid BST

---

## Dry Run

### Tree

```
        5
       / \
      3   7
         / \
        6   8
```

### Execution

- Root `5` → valid in `(-∞, +∞)`
- Left `3` → valid in `(-∞, 5)`
- Right `7` → valid in `(5, +∞)`
- Left of `7` → `6` valid in `(5, 7)`
- Right of `7` → `8` valid in `(7, +∞)`

✔ All nodes satisfy constraints → **Valid BST**

---

## Complexity

- **Time Complexity:**
  $$O(n)$$
  (each node visited once)

- **Space Complexity:**
  $$O(h)$$
  (recursion stack, where `h` is tree height)

---

## Code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    bool valid(TreeNode* root, long left, long right) {
        if (!root) return true;

        // left < val < right must hold
        if (!(left < root->val && root->val < right))
            return false;

        return valid(root->left, left, root->val) &&
               valid(root->right, root->val, right);
    }

public:
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        return valid(root, LONG_MIN, LONG_MAX);
    }
};
```

---

## 🔹 Solution 2: Inorder Traversal (Sorted Property)

---

## Intuition (WHY)

A **BST has a special property**:

> **Inorder traversal of a BST always gives a strictly increasing sequence**

If the inorder sequence is **not sorted**,
then the tree **cannot be a BST**.

---

## Approach (WHAT + HOW)

### WHAT

- Perform inorder traversal
- Store values in an array
- Check if the array is strictly increasing

### HOW

1. Traverse left → root → right
2. Store values in a vector
3. Iterate over vector:

   - If `arr[i] >= arr[i+1]` → invalid BST

4. Otherwise → valid BST

---

## Dry Run

### Tree

```
        5
       / \
      3   7
         / \
        6   8
```

### Inorder Traversal

```
[3, 5, 6, 7, 8]
```

✔ Strictly increasing → **Valid BST**

---

### Invalid Case

```
        5
       / \
      3   4
```

Inorder:

```
[3, 5, 4]   ❌ not sorted
```

→ **Invalid BST**

---

## Complexity

- **Time Complexity:**
  $$O(n)$$
  (full traversal)

- **Space Complexity:**
  $$O(n)$$
  (array + recursion stack)

---

## Code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    vector<int> arr;

    void generate(TreeNode* root) {
        if (!root) return;

        generate(root->left);
        arr.push_back(root->val);
        generate(root->right);
    }

public:
    bool isValidBST(TreeNode* root) {
        if (!root) return true;

        generate(root);

        for (int i = 0; i < arr.size() - 1; i++) {
            if (arr[i] >= arr[i + 1])
                return false;
        }
        return true;
    }
};
```

---

## 🔹 Final Comparison (NDK Style)

| Aspect               | Solution 1 (Range) | Solution 2 (Inorder)   |
| -------------------- | ------------------ | ---------------------- |
| Core idea            | Range constraints  | Sorted inorder         |
| Extra space          | No extra array     | Uses vector            |
| Time                 | O(n)               | O(n)                   |
| Space                | O(h)               | O(n)                   |
| Interview preference | ⭐⭐⭐⭐           | ⭐⭐⭐                 |
| Best practice        | ✅ YES             | ❌ (works but heavier) |

---

## 🔒 Final Lock-In Rule (Very Important)

> **BST validation is about ancestor constraints, not just parent comparison**
