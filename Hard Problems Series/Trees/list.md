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

* 2. Binary Tree Right Side View
  - Trick -> use size of vector as current right side depth, 
```cpp
class Solution {
public:
    vector<int> res;

    void viewRight(TreeNode* node, int depth) {
        if (!node)
            return;
        
        if (depth == res.size()) 
            res.push_back(node->val);
        
        viewRight(node->right, depth+1);
        viewRight(node->left, depth+1);
    }

    vector<int> rightSideView(TreeNode* root) {
        viewRight(root, 0);
        return res;
    }
};
```

### [Pattern-4 (Path Related)]
* 1. Path Sum [LeetCode 112](https://leetcode.com/problems/path-sum/)
  - Trick -> main condition will be if we reach leaf node and sum is equal to targetSum then return true, else return false 
```cpp
class Solution {
public:
    bool traverse(TreeNode* node, int targetSum, int currentSum) {
        if (!node)
            return false;

        if ((currentSum + node->val) == (targetSum) && !node->left && !node->right)
            return true;

        return traverse(node->left, targetSum, currentSum + node->val) ||
               traverse(node->right, targetSum, currentSum + node->val);
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        return traverse(root, targetSum, 0);
    }
};
```

* 2. Path Sum III [LeetCode 437](https://leetcode.com/problems/path-sum-iii/)
  - Trick -> For Each Node assume its a starting point and final currentSum from that node to all its child nodes, if currentSum == targetSum then increment the count, can use hashMap to store the currentSum instead of calculating it again and again
```cpp
class Solution {
public:
    int res = 0;

    void findPaths(TreeNode* node, int targetSum, long long currentSum) {
        if (!node)
            return;

        if (currentSum + node->val == targetSum)
            res++;

        findPaths(node->left, targetSum, currentSum + node->val);
        findPaths(node->right, targetSum, currentSum + node->val);

        return;
    }

    int pathSum(TreeNode* root, int targetSum) {
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();

            while (size--) {
                TreeNode* node = q.front();
                q.pop();

                // traverse each node to find targeSum 
                // no matters targetSum or node->val is greater or smaller 
                // because it contains both pos and neg numbers
                if (node)
                    findPaths(node, targetSum, 0);

                if (node && node->left)
                    q.push(node->left);

                if (node && node->right)
                    q.push(node->right);
            }
        }

        return res;
    }
};
```

