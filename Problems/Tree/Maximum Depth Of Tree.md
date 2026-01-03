# Maximum Depth of Binary Tree (C++)

## Problem Statement

Given the root of a binary tree, return its **maximum depth**.

Maximum depth means:

- Root se leke sabse gehre leaf node tak **number of nodes**.

---

## Approach

Is solution mein **recursion** use ki gayi hai.

Idea simple hai:

- Har node ke liye left aur right subtree ki depth calculate karo
- Jo bhi zyada ho, wahi answer
- Depth ko manually track kiya gaya hai using an integer parameter `d`

---

## Code Explanation

### TreeNode Structure

Binary tree ka standard node structure use hua hai:

```cpp
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};
```

---

### Helper Function: `deep`

```cpp
int deep(TreeNode* node, int d)
```

#### Parameters:

- `node`: current node
- `d`: current depth

#### Logic:

1. **Agar node NULL hai**

   - Matlab ek step extra badh gaya hai
   - Isliye `d - 1` return karte hain

2. **Agar leaf node hai**

   - Current depth `d` hi max depth hogi
   - Direct return

3. **Otherwise**

   - Left aur right subtree dono ki depth nikalo
   - `max()` use karke badi depth return karo

```cpp
return max(deep(node->left, d + 1),
           deep(node->right, d + 1));
```

---

### Main Function: `maxDepth`

```cpp
int maxDepth(TreeNode* root)
```

#### Logic:

- Agar tree empty hai → depth `0`
- Warna helper function `deep()` ko call karo with starting depth `1`

---

## Full Code

```cpp
class Solution {
private:
    int deep(TreeNode* node, int d) {
        if (!node) return d - 1;
        else if (!node->left && !node->right) return d;

        return max(deep(node->left, d + 1),
                   deep(node->right, d + 1));
    }

public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return deep(root, 1);
    }
};
```

---

## Time & Space Complexity

- **Time Complexity:** `O(n)`

  - Har node ek baar visit hota hai

- **Space Complexity:** `O(h)`

  - Recursive call stack
  - `h` = height of tree (worst case mein `n`)

---

## Notes

- Yeh solution **depth parameter manually track** karta hai
- Alternative approach mein bina `d` parameter ke bhi solution likha ja sakta hai
- Interview mein yeh approach bilkul acceptable hai

---

## Conclusion

- Recursion se tree depth nikalna straightforward hai
- Base cases clear hone chahiye
- Depth calculation mein off-by-one error se bachna zaroori hai

```

---

Agar chaho toh main:
- **Simpler recursive version (without depth parameter)**
- **Iterative BFS solution**
- **Interview-friendly optimized explanation**

bhi de sakta hoon.
```
