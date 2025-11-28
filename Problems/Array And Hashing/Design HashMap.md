
---
# **MyHashMap – Custom Implementations (C++)**

This file contains **two different implementations** of a `HashMap` in C++:

1. **HashMap using Linked List Chaining**
2. **HashMap using Direct Address Table (`vector<int>`)**

Each approach solves the design problem differently based on constraints.

---

# #️⃣ **1. HashMap Using Linked List Chaining**

### **📌 Idea**

* Hash table with **1000 buckets**.
* Each bucket is a **linked list** (to handle collisions).
* Insert / remove / search happen inside that linked list.
* Standard “Separate Chaining” approach.

---

## **Code**

```cpp
class MyHashMap {
private:
    // Node for chaining in each bucket
    struct Node {
        int key, value;
        Node* next;
        Node(int key, int value, Node* next = nullptr)
            : key(key), value(value), next(next) {}
    };

    vector<Node*> myHashMap;       // 1000 buckets
    int hash(int key) { return key % myHashMap.size(); }

public:
    MyHashMap() : myHashMap(1000, nullptr) {}

    void put(int key, int value) {
        int idx = hash(key);

        // First insertion in bucket
        if (!myHashMap[idx]) {
            myHashMap[idx] = new Node(key, value);
            return;
        }

        Node* current = myHashMap[idx];
        Node* prev = nullptr;

        // Update value if key exists
        while (current) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            prev = current;
            current = current->next;
        }

        // Key not found → insert at end
        prev->next = new Node(key, value);
    }

    int get(int key) {
        int idx = hash(key);
        Node* current = myHashMap[idx];

        while (current) {
            if (current->key == key) return current->value;
            current = current->next;
        }
        return -1;    // key not found
    }

    void remove(int key) {
        int idx = hash(key);
        Node* current = myHashMap[idx];
        Node* prev = nullptr;

        while (current) {
            if (current->key == key) {
                // deleting head node
                if (!prev) {
                    myHashMap[idx] = current->next;
                } 
                // deleting node in middle/end
                else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
};
```

---

## **Complexity**

| Operation | Avg. Case | Worst Case                     |
| --------- | --------- | ------------------------------ |
| put       | O(1)      | O(n) (all keys in same bucket) |
| get       | O(1)      | O(n)                           |
| remove    | O(1)      | O(n)                           |

---

# #️⃣ **2. HashMap Using Direct Address Table (`vector<int>`)**

### **📌 Idea**

* For constraints `0 ≤ key ≤ 1,000,000`
* Use a **vector of size 1e6+1**.
* Store values directly at index `key`.
* `-1` marks “key not present”.

Fastest possible HashMap approach.

---

## **Code (short & clean)**

```cpp
class MyHashMap {
public:
    vector<int> myHashMap;

    // Initialize table with -1 (meaning "empty")
    MyHashMap() : myHashMap(1000001, -1) {}

    void put(int key, int value) {
        myHashMap[key] = value;    // direct write
    }

    int get(int key) {
        return myHashMap[key];     // direct read
    }

    void remove(int key) {
        myHashMap[key] = -1;       // mark empty
    }
};
```

---

## **Complexity**

| Operation | Time | Space  |
| --------- | ---- | ------ |
| put       | O(1) | O(1e6) |
| get       | O(1) | O(1e6) |
| remove    | O(1) | O(1e6) |

---

# #️⃣ **Comparison Table**

| Feature            | Linked List Chaining | Direct Table      |
| ------------------ | -------------------- | ----------------- |
| Collision Handling | Linked list nodes    | No collisions     |
| Memory Use         | Medium               | High (1e6+1 ints) |
| Speed              | O(1) avg             | O(1) always       |
| Best For           | Generic HashMap      | Small key range   |

---

# ✔ Final Note

Both implementations follow the same formula:

```
hash(key) → bucket → store/search/erase inside bucket.
```

The **difference is the bucket structure**:

* Linked List → general-purpose HashMap
* Direct Address Table → fastest when key range is known

---
