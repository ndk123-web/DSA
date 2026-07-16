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

* 3. Maximum Path Sum [LeetCode 124](https://leetcode.com/problems/binary-tree-maximum-path-sum/)
  - Trick -> for each node, find leftMax and rightMax, then update the res with max(res, leftMax + rightMax + node->val), return max(leftMax, rightMax) + node->val to parent node
```cpp
class Solution {
public:
    int res = 0;

    int dfs(TreeNode* node) {
        if (!node)
            return 0;

        // take max 0 
        int leftMax = max(dfs(node->left), 0);
        int rightMax = max(dfs(node->right), 0);

        res = max(res, leftMax + rightMax + node->val);

        // return 1 highest path (either left or right through)
        return max(leftMax, rightMax) + node->val;
    }

    int maxPathSum(TreeNode* root) {
        res = root->val;
        dfs(root);
        return res;
    }
};
```

### [Pattern-5 (Binary Search Tree)]
* 1. Search in a Binary Search Tree [LeetCode 700](https://leetcode.com/problems/search-in-a-binary-search-tree/)
  - Trick -> if current node value is equal to target then return current node, if current node value is greater than target then go left else go right
  - Time -> O(logN) if tree is balanced else O(N)
```cpp
class Solution {
public:
    TreeNode* search(TreeNode* node, int val) {
        if (!node)
            return nullptr;

        if (node->val > val)
            return search(node->left, val);
        else if (node->val < val)
            return search(node->right, val);
        else if (node->val == val)
            return node;

        return nullptr;
    }

    TreeNode* searchBST(TreeNode* root, int val) { 
        return search(root, val); 
    }
};
```

* 2. Validate Binary Search Tree [LeetCode 98](https://leetcode.com/problems/validate-binary-search-tree/)
  - Trick -> create an arr, and push inside that inorder traversal of tree, then check if arr is sorted or not, if sorted then return true else false 
  - Time -> O(N)
  - Sol 1 - with extra space 
```cpp
class Solution {
public:
    vector<int> arr;

    void generate(TreeNode* node) {
        if (!node)
            return;

        generate(node->left);
        arr.push_back(node->val);
        generate(node->right);

        return;
    }

    bool isValidBST(TreeNode* root) {
        generate(root);

        for (int i = 0; i < arr.size() - 1; i++) {
            if (arr[i] >= arr[i + 1])
                return false;
        }

        return true;
    }
};
```

  - Sol 2 - without using extra space 
```cpp
class Solution {
public:
    bool isValid(TreeNode* node, long long mn, long long mx) {
        if (!node)
            return true;

        if (!(node->val > mn && node->val < mx))
            return false;

        return isValid(node->left, mn, node->val) &&
               isValid(node->right, node->val, mx);
    }

    bool isValidBST(TreeNode* root) {
        return isValid(root, LLONG_MIN, LLONG_MAX);
    }
};
```

* 3. Kth smallest element in a BST [LeetCode 230](https://leetcode.com/problems/kth-smallest-element-in-a-bst/)
  - Trick -> do inorder traversal and keep track of count, when count == k then return the node value
  - Time -> O(H + K) where H is the height of the tree, K is the kth smallest element
```cpp
class Solution {
public:
    vector<int> res;

    void generate(TreeNode* node, int k) {
        if (!node)
            return;
        
        if (res.size() == k)
            return;

        generate(node->left, k);
        res.push_back(node->val);
        generate(node->right, k);
    }

    int kthSmallest(TreeNode* root, int k) {
        generate(root, k);

        if (k > res.size())
            return -1;

        return res[k - 1];
    }
};
```

### [Pattern-6 (Building Tree)]
* 1. Construct Binary Tree from Preorder and Inorder Traversal [LeetCode 105](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)
  - Trick -> store inorder value positions in map, then idx = 0, for each root preorder[idx] find its position in inorder, then recursively call for left and right subtree
  - All about obsevation, preorder -> root, left, right and inorder -> left, root, right 
  - Time -> O(N)
```cpp
class Solution {
public:
    unordered_map<int, int> mapp;
    int idx = 0;

    TreeNode* dfs(vector<int>& preorder, int st, int end) {
        if (st > end)
            return nullptr;
            
        int rootVal = preorder[idx++];
        TreeNode* node = new TreeNode(rootVal);

        int rootIdx = mapp[rootVal];
        node->left = dfs(preorder, st, rootIdx - 1);
        node->right = dfs(preorder, rootIdx + 1, end);

        return node;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < preorder.size(); i++)
            mapp[inorder[i]] = i;

        return dfs(preorder, 0, preorder.size() - 1);
    }
};
```