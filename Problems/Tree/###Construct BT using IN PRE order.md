# Construct Binary Tree from Preorder and Inorder Traversal

---

## Intuition (WHY)

We are given **two traversal orders** of the same binary tree:

- **Preorder** → `root, left, right`
- **Inorder** → `left, root, right`

Key observations:

1. In **preorder**, the **first element is always the root**
2. In **inorder**, everything **left of root belongs to left subtree**,
   everything **right of root belongs to right subtree**

So if we:

- pick root from preorder
- find its index in inorder
- recursively build left and right subtrees

👉 we can reconstruct the **exact same tree**.

---

## Approach (WHAT)

We use **DFS + recursion** with these ideas:

- Maintain a pointer `idx` on preorder (global / class variable)
- Use a hashmap to quickly find root index in inorder
- Recursively construct tree using inorder boundaries

---

## How (STEP BY STEP)

### Step 1: Preprocess inorder

Create a map:

```
value → index in inorder
```

This allows **O(1)** lookup instead of searching every time.

---

### Step 2: Recursive DFS

`dfs(preorder, l, r)` means:

> Build a tree using inorder indices from `l` to `r`

Inside DFS:

1. Take `preorder[idx]` → this is root
2. Increment `idx`
3. Find root position `mid` in inorder
4. Recursively build:

   - Left subtree → `[l, mid-1]`
   - Right subtree → `[mid+1, r]`

Base case:

```
if l > r → return nullptr
```

---

## Dry Run (IMPORTANT)

### Input

```
preorder = [3,9,20,15,7]
inorder  = [9,3,15,20,7]
```

---

### Step-by-step

#### 1️⃣ First call

- idx = 0 → root = `3`
- inorder index of 3 = `1`

Left subtree → inorder `[0..0]`
Right subtree → inorder `[2..4]`

---

#### 2️⃣ Left subtree

- idx = 1 → root = `9`
- inorder index = `0`

Left → empty
Right → empty

Node `9` is leaf.

---

#### 3️⃣ Right subtree

- idx = 2 → root = `20`
- inorder index = `3`

Left → `[2..2]` → `15`
Right → `[4..4]` → `7`

---

### Final Tree

```
        3
       / \
      9  20
         / \
        15  7
```

---

## Why `idx` works (IMPORTANT)

- Preorder always gives **root first**
- Once root is consumed, next preorder value belongs to left subtree
- `idx` ensures preorder is consumed **in correct order**

---

## Complexity

### Time Complexity

```
O(n)
```

- Each node is created once
- Hashmap lookup is O(1)

---

### Space Complexity

```
O(n)
```

- Hashmap for inorder indices
- Recursion stack (worst case skewed tree)

---

## Code

```cpp
class Solution {
private:
    unordered_map<int, int> mapp;
    int idx = 0;

    TreeNode* dfs(vector<int>& preorder, int l, int r) {
        if (l > r)
            return nullptr;

        int root_val = preorder[idx++];
        TreeNode* node = new TreeNode(root_val);

        int mid = mapp[root_val];

        node->left = dfs(preorder, l, mid - 1);
        node->right = dfs(preorder, mid + 1, r);

        return node;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();

        for (int i = 0; i < n; i++) {
            mapp[inorder[i]] = i;
        }

        return dfs(preorder, 0, n - 1);
    }
};
```

---

## Common Mistakes (You Avoided These)

❌ Searching inorder linearly every time
❌ Passing preorder index by value
❌ Mixing preorder & inorder boundaries
❌ Forgetting base case `l > r`
