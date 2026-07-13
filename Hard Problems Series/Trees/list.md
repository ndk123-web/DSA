## Trees List 

### [Pattern-1 (Normal Order Traversal)]
1. Binary Tree Inorder Traversal [LeetCode 94](https://leetcode.com/problems/binary-tree-inorder-traversal/)
2. Binary Tree Preorder Traversal [LeetCode 144](https://leetcode.com/problems/binary-tree-preorder-traversal/)
3. Binary Tree Postorder Traversal [LeetCode 145](https://leetcode.com/problems/binary-tree-postorder-traversal/)


### [Pattern-2 (Level Order Traversal)]
1. Maximum Depth of Binary Tree [LeetCode 104](https://leetcode.com/problems/maximum-depth-of-binary-tree/)

* 2. Diameter of Binary Tree [LeetCode 543](https://leetcode.com/problems/diameter-of-binary-tree/) 
   - Trick -> for each Node, Find Left Max Depth + Right Max Depth, can use hashMap to store the depth instead of calculating it again and again
```cpp
class Solution {
public:
    int res = INT_MIN;
    unordered_map<TreeNode*, int> mapp;

    // getting
    int maxDepth(TreeNode* node) {
        if (!node)
            return 0;

        if (mapp.count(node))
            return mapp[node];

        return mapp[node] = 1 + max(maxDepth(node->left), maxDepth(node->right));
    }

    // by assuming the current Node invloved then diameter to that node will be
    // (left max depth + right max depth)
    void assumeNodeInvolved(TreeNode* node) {
        if (!node)
            return;

        int leftDepth;
        int rightDepth;

        if (!mapp.count(node->left)) {
            leftDepth = maxDepth(node->left);
            mapp[node->left] = leftDepth;
        } else {
            leftDepth = mapp[node->left];
        }

        if (!mapp.count(node->right)) {
            rightDepth = maxDepth(node->right);
            mapp[node->right] = rightDepth;
        } else {
            rightDepth = mapp[node->right];
        }

        res = max(res, (leftDepth + rightDepth));

        assumeNodeInvolved(node->left);
        assumeNodeInvolved(node->right);

        return;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        assumeNodeInvolved(root);
        return res;
    }
};
```

* 3. Balanced Binary Tree [LeetCode 110](https://leetcode.com/problems/balanced-binary-tree/)
   - Trick -> for each Node, Find Left Max Depth and Right Max Depth, if difference is greater than 1 then return false, can use hashMap to store the depth instead of calculating it again and again 
```cpp
class Solution {
public:
    unordered_map<TreeNode*, int> mapp;

    int maxDepth(TreeNode* node) {
        if (!node)
            return 0;

        return mapp[node] =
                   1 + max(maxDepth(node->left), maxDepth(node->right));
    }

    bool forEachNode(TreeNode* node) {
        if (!node)
            return true;

        int leftMaxDepth, rightMaxDepth;

        if (mapp.count(node->left)) {
            leftMaxDepth = mapp[node->left];
        } else {
            leftMaxDepth = maxDepth(node->left);
        }

        if (mapp.count(node->right)) {
            rightMaxDepth = mapp[node->right];
        } else {
            rightMaxDepth = maxDepth(node->right);
        }

        if (abs(leftMaxDepth - rightMaxDepth) > 1) {
            return false;
        }

        return forEachNode(node->left) && forEachNode(node->right);
    }

    bool isBalanced(TreeNode* root) { return forEachNode(root); }
};
```

### [Pattern-3 (Level Order Traversal)]
* 1. Binary Tree Level Order Traversal [LeetCode 102](https://leetcode.com/problems/binary-tree-level-order-traversal/)
```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root)
            return {};
            
        queue<TreeNode*> q;
        vector<vector<int>> res;
        vector<int> part;

        q.push(root);

        while (!q.empty()) {
            int size = q.size();

            while (size--) {
                TreeNode* t = q.front();

                if (t)
                    part.push_back(t->val);
                
                if (t && t->left != nullptr) 
                    q.push(t->left);
                if (t && t->right != nullptr)
                    q.push(t->right);

                q.pop();
            }

            res.push_back(part);
            part.clear();
        }

        return res;
    }
};
```