
---

# #️⃣ **Custom HashSet Implementations (C++)**

Below are **3 different HashSet implementations** using:

1. **BST chaining**
2. **Linked List chaining**
3. **Boolean Direct Address Table**

Each implementation follows same idea:

```
hash(key) → pick bucket → operate inside that structure.
```

---

# ## 1) **HashSet using BST (Binary Search Tree)**

### ✔ Idea

* `size = 1000` buckets
* Every bucket contains a **BST**
* Insert/remove/search happens inside the BST
* Good when collisions occur but you want sorted structure per bucket

### ✔ Code (with short comments)

```cpp
class BST {
private:
    struct TreeNode {
        int key;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int key) : key(key), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    TreeNode* insert(TreeNode* root, int key) {
        if (!root) return new TreeNode(key);
        if (key < root->key)
            root->left = insert(root->left, key);
        else if (key > root->key)
            root->right = insert(root->right, key);
        return root;  // return updated subtree
    }

    TreeNode* minValueNodeToRight(TreeNode* root) {
        while (root->left) root = root->left;
        return root; // smallest in right subtree
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            // Case 1: no left child
            if (!root->left) {
                TreeNode* tmp = root->right;
                delete root;
                return tmp;
            }
            // Case 2: no right child
            if (!root->right) {
                TreeNode* tmp = root->left;
                delete root;
                return tmp;
            }
            // Case 3: two children → replace key with successor
            TreeNode* tmp = minValueNodeToRight(root->right);
            root->key = tmp->key;
            root->right = deleteNode(root->right, tmp->key);
        }
        return root;  // return updated subtree
    }

    bool contains(TreeNode* root, int key) {
        if (!root) return false;
        if (key == root->key) return true;
        return key < root->key ? contains(root->left, key)
                               : contains(root->right, key);
    }

public:
    BST() : root(nullptr) {}

    void add(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    bool search(int key) {
        return contains(root, key);
    }
};

class MyHashSet {
private:
    const int size = 1000;
    vector<BST> buckets;  // each bucket has its own BST

    int hash(int key) { return key % size; }

public:
    MyHashSet() : buckets(size) {}  // initialize 1000 BST objects

    void add(int key) {
        int idx = hash(key);
        if (!contains(key))
            buckets[idx].add(key);  // insert inside BST
    }

    void remove(int key) {
        int idx = hash(key);
        buckets[idx].remove(key);
    }

    bool contains(int key) {
        int idx = hash(key);
        return buckets[idx].search(key);
    }
};
```

---

# ## 2) **HashSet using Linked List Chaining**

### ✔ Idea

* `size = 10000` buckets
* Each bucket is a **dummy head node**
* Collisions handled by linked list

### ✔ Code (short comments)

```cpp
class MyHashSet {
public:
    struct Node {
        int key;
        Node* next;
        Node(int key) : key(key), next(nullptr) {}
    };

    vector<Node*> myHashSet;  // array of linked-list heads

    int hash(int key) { return key % myHashSet.size(); }

    MyHashSet() {
        myHashSet.resize(10000);
        for (auto& bucket : myHashSet)
            bucket = new Node(0);  // dummy head for each bucket
    }
    
    void add(int key) {
        Node* curr = myHashSet[hash(key)];
        while (curr->next) {
            if (curr->next->key == key) return;  // already present
            curr = curr->next;
        }
        curr->next = new Node(key);  // append new node
    }
    
    void remove(int key) {
        Node* curr = myHashSet[hash(key)];
        while (curr->next) {
            if (curr->next->key == key) {
                Node* tmp = curr->next;
                curr->next = tmp->next;  // unlink
                delete tmp;
                return;
            }
            curr = curr->next;
        }
    }
    
    bool contains(int key) {
        Node* curr = myHashSet[hash(key)];
        while (curr->next) {
            if (curr->next->key == key) return true;
            curr = curr->next;
        }
        return false;
    }
};
```

---

# ## 3) **HashSet using Boolean Vector (Direct Address Table)**

### ✔ Idea

* Best when key range is small
* `vector<bool>` directly marks presence
* Fastest possible implementation

### ✔ Code (short comments)

```cpp
class MyHashSet {
public:
    vector<bool> booleanV;  // direct-address table

    MyHashSet() : booleanV(1000001, false) {}  // keys up to 1e6
    
    void add(int key) {
        booleanV[key] = true;  // mark present
    }
    
    void remove(int key) {
        booleanV[key] = false; // unmark
    }
    
    bool contains(int key) {
        return booleanV[key];  // check presence
    }
};
```

---

# ## ⭐ Comparison Table (Simple)

| Implementation  | Memory | Speed               | When to Use                         |
| --------------- | ------ | ------------------- | ----------------------------------- |
| **BST**         | Medium | O(log n) per bucket | Balanced collisions, sorted buckets |
| **Linked List** | Medium | O(1) avg            | Classic hashset                     |
| **Boolean**     | High   | O(1) always         | Keys ≤ 1e6, fastest                 |

---

# ## ✔ Final Notes

All three follow:

```
hash(key) → bucket → insert/remove/search inside bucket
```

Difference is only the **bucket structure**.

* BST → tree
* Linked List → chain
* Boolean vector → direct address

---