# Balanced Binary Tree (C++)

## Problem Statement

Given the root of a binary tree, determine whether it is **height-balanced**.

A binary tree is **balanced** if:

- For **every node**, the height difference between its left and right subtree is **at most 1**.

---

## Key Idea

> Balance check **sirf root pe nahi**,  
> **har node pe** hona chahiye.

Isliye tree ko **post-order traversal** se process kiya jaata hai.

---

## Approach Used

We combine:

1. **Height calculation**
2. **Balance checking**

in **one recursive function**.

A global boolean flag `res` track karta hai:

- Tree balanced hai ya nahi

---

## Height Definition

```text
height(node) = 1 + max(leftHeight, rightHeight)
```

- `NULL` node → height `0`
- Leaf node → height `1`

---

## Algorithm

1. Agar node `NULL` hai → height `0`
2. Pehle left subtree check karo
3. Phir right subtree check karo
4. Dono heights ka difference nikalo
5. Agar difference > 1 → tree unbalanced
6. Height return karo

---

## Code

```cpp
class Solution {
private:
    bool res = true;

    int check(TreeNode* node) {
        if (!node) return 0;
        if (!res) return 0;

        int l = check(node->left) + 1;
        int r = check(node->right) + 1;

        if (abs(l - r) > 1)
            res = false;

        return max(l, r);
    }

public:
    bool isBalanced(TreeNode* root) {
        check(root);
        return res;
    }
};
```

---

## Why This Works

- Height bottom-up calculate hoti hai
- Har node pe balance condition check hoti hai
- Jaise hi imbalance milta hai, `res = false`
- Extra traversal ki zarurat nahi

---

## Dry Run (Step-by-Step)

### Example Tree

```
        1
       / \
      2   3
     /
    4
```

---

### Step 1: Node 4

- Left height = 0
- Right height = 0
- `|0 - 0| = 0` → balanced
- Return height = `1`

---

### Step 2: Node 2

- Left height = 1
- Right height = 0
- `|1 - 0| = 1` → balanced
- Return height = `2`

---

### Step 3: Node 3

- Left height = 0
- Right height = 0
- `|0 - 0| = 0` → balanced
- Return height = `1`

---

### Step 4: Node 1 (Root)

- Left height = 2
- Right height = 1
- `|2 - 1| = 1` → balanced

✔ Final Answer: **true**

---

## Unbalanced Example

```
        1
       /
      2
     /
    3
```

At node `1`:

- Left height = 2
- Right height = 0
- `|2 - 0| = 2` ❌

❌ Tree is **not balanced**

---

## Time & Space Complexity

- **Time Complexity:** `O(n)`

  - Har node ek baar visit hota hai

- **Space Complexity:** `O(h)`

  - Recursive stack
  - `h` = height of tree

---

## Common Mistakes (Avoid These)

- Height aur balance ko alag-alag functions mein check karna ❌
- Sirf root pe balance check karna ❌
- Repeated height calculation ❌

---

## Conclusion

- Balanced tree check **local condition** hai
- Post-order traversal best approach hai
- Ye solution **optimal aur interview-safe** hai

```

```
