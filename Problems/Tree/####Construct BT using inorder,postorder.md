# 106. Construct Binary Tree from Inorder and Postorder Traversal

## Intuition

We are given two traversals of the same binary tree:

```text
Inorder   = Left → Root → Right
Postorder = Left → Right → Root
```

The goal is to reconstruct the original binary tree.

---

## Key Observation 1: Postorder Gives the Root

In a postorder traversal:

```text
Left → Right → Root
```

the **last element is always the root** of the current subtree.

Example:

```text
postorder = [9,15,7,20,3]
```

The last element is:

```text
3
```

Therefore:

```text
3 = root
```

---

## Key Observation 2: Inorder Splits Left and Right Subtrees

Consider:

```text
inorder = [9,3,15,20,7]
```

After finding:

```text
root = 3
```

we locate it in the inorder array:

```text
9 | 3 | 15 20 7
```

Everything on the left belongs to:

```text
Left Subtree
```

Everything on the right belongs to:

```text
Right Subtree
```

Thus:

```text
Left subtree nodes  = [9]
Right subtree nodes = [15,20,7]
```

---

## Important Insight

When consuming postorder from the back:

```text
9 15 7 20 3
            ↑
```

we visit nodes in the order:

```text
3 → 20 → 7 → 15 → 9
```

which corresponds to:

```text
Root → Right → Left
```

Therefore we must build:

```cpp
root->right
```

before:

```cpp
root->left
```

Otherwise nodes belonging to the right subtree would be incorrectly consumed by the left subtree.

---

## Why Do We Need `left` and `right`?

The inorder traversal determines the valid range of nodes belonging to the current subtree.

For example:

```text
9 | 3 | 15 20 7
```

After choosing:

```text
3
```

the recursive calls become:

```cpp
Left  : [9]
Right : [15,20,7]
```

represented using indices:

```cpp
dfs(left, index-1)
dfs(index+1, right)
```

The inorder boundaries tell recursion when a subtree is finished.

---

## Approach

### Step 1

Store every value's position in inorder.

```cpp
unordered_map<int,int> inorderMap;
```

This allows O(1) lookup of the root's index.

---

### Step 2

Maintain a global pointer:

```cpp
postIndex
```

starting at:

```cpp
n - 1
```

because the last element of postorder is the root.

---

### Step 3

For each recursive call:

1. Take the current root from postorder.
2. Find its position in inorder.
3. Build the right subtree.
4. Build the left subtree.

---

## Dry Run

### Input

```text
inorder   = [9,3,15,20,7]
postorder = [9,15,7,20,3]
```

---

### Root

```text
root = 3
```

Split inorder:

```text
9 | 3 | 15 20 7
```

---

### Right Subtree

Next postorder value:

```text
20
```

Split:

```text
15 | 20 | 7
```

Tree becomes:

```text
      3
       \
        20
```

---

### Right Child of 20

Next postorder value:

```text
7
```

Tree:

```text
      3
       \
        20
          \
           7
```

---

### Left Child of 20

Next postorder value:

```text
15
```

Tree:

```text
      3
       \
        20
       /  \
      15   7
```

---

### Left Subtree of 3

Next postorder value:

```text
9
```

Final tree:

```text
        3
       / \
      9   20
         /  \
        15   7
```

---

## Code

```cpp
class Solution {
public:
    unordered_map<int, int> inorderMap;
    int postIndex;

    TreeNode* dfs(vector<int>& postorder, int left, int right) {

        if (left > right)
            return nullptr;

        int rootVal = postorder[postIndex--];

        TreeNode* root = new TreeNode(rootVal);

        int indexOfRoot = inorderMap[rootVal];

        root->right = dfs(postorder, indexOfRoot + 1, right);
        root->left  = dfs(postorder, left, indexOfRoot - 1);

        return root;
    }

    TreeNode* buildTree(vector<int>& inorder,
                        vector<int>& postorder) {

        int n = inorder.size();

        postIndex = n - 1;

        for (int i = 0; i < n; i++) {
            inorderMap[inorder[i]] = i;
        }

        return dfs(postorder, 0, n - 1);
    }
};
```

---

## Correctness Proof

### Lemma 1

The last unprocessed element in postorder is always the root of the current subtree.

This follows directly from:

```text
Postorder = Left → Right → Root
```

---

### Lemma 2

The root's position in inorder uniquely splits the subtree into:

```text
Left subtree nodes
Right subtree nodes
```

because:

```text
Inorder = Left → Root → Right
```

---

### Lemma 3

Building the right subtree before the left subtree consumes postorder elements in the correct order:

```text
Root → Right → Left
```

which is exactly the reverse of postorder.

---

### Theorem

Every recursive call constructs the correct root and correctly partitions the remaining nodes into left and right subtrees.

Therefore the algorithm reconstructs the original binary tree.

---

## Complexity Analysis

### Time Complexity

Building map:

```text
O(n)
```

Tree construction:

```text
O(n)
```

Total:

```text
O(n)
```

---

### Space Complexity

Hash map:

```text
O(n)
```

Recursion stack:

```text
O(h)
```

where:

```text
h = height of tree
```

Worst case:

```text
O(n)
```

Balanced tree:

```text
O(log n)
```

---

## Pattern Recognition

Whenever you see:

```text
Inorder + Postorder
```

think:

```text
Postorder → Root
Inorder   → Split Left / Right
Build Right First
```

Similarly:

```text
Preorder + Inorder
```

follows:

```text
Preorder → Root
Inorder  → Split Left / Right
Build Left First
```

This is the core pattern behind binary tree reconstruction problems. 🔥
