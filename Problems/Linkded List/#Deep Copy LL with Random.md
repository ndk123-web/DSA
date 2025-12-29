# Copy Linked List With Random Pointer (HashMap Method)

## Problem Statement

You are given a linked list where each node contains:

- `val` → integer value
- `next` → pointer to next node
- `random` → pointer to **any node in the list or NULL**

Your task is to create a **deep copy** of this linked list.

Deep copy means:

- Every node in the new list must be a **new node**
- `next` and `random` pointers must point only to **new nodes**, never to original nodes

---

## Core Idea (Important Intuition)

The main difficulty is the `random` pointer.

### Key Insight

> Every original node already knows **exactly which node** its `random` pointer points to (by address).
>
> If we maintain a mapping:
>
> `original_node → copied_node`
>
> then setting `random` becomes trivial.

This is why we use a **hash map**.

---

## Data Structure Used

```cpp
unordered_map<Node*, Node*> hashMap;
```

Meaning:

- **Key** → original node address
- **Value** → newly created copy node

---

## Algorithm (2-Pass Solution)

### Pass 1: Copy all nodes (only values)

- Traverse original list
- For each node, create a new node with same value
- Store mapping in hash map

At this stage:

- Nodes exist
- `next` and `random` are NOT connected yet

---

### Pass 2: Assign `next` and `random` pointers

- Traverse original list again
- For each original node `curr`:

  - `copy->next   = hashMap[curr->next]`
  - `copy->random = hashMap[curr->random]`

Because:

- `hashMap[curr->next]` gives the copy of the next node
- `hashMap[curr->random]` gives the copy of the random node

---

## Final Code (With Short Comments)

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node* curr = head;
        unordered_map<Node*, Node*> hashMap;

        // PASS 1: create copy of each node
        while (curr) {
            hashMap[curr] = new Node(curr->val); // copy node
            curr = curr->next;
        }

        // PASS 2: assign next and random pointers
        curr = head;
        while (curr) {
            Node* node = hashMap[curr];

            node->next   = hashMap[curr->next];   // copy of next
            node->random = hashMap[curr->random]; // copy of random

            curr = curr->next;
        }

        // return head of copied list
        return hashMap[head];
    }
};
```

---

## Dry Run Example

### Input

```
[[3,null],[7,3],[4,0],[5,1]]
```

Meaning:

| Index | Value | Random points to |
| ----- | ----- | ---------------- |
| 0     | 3     | null             |
| 1     | 7     | index 3          |
| 2     | 4     | index 0          |
| 3     | 5     | index 1          |

---

### Pass 1: Node Creation

HashMap after first pass:

```
3  →  3'
7  →  7'
4  →  4'
5  →  5'
```

(All nodes exist, pointers not set yet)

---

### Pass 2: Pointer Assignment

For node `7`:

```
7.next   -> 4      => 7'.next   = 4'
7.random -> 5      => 7'.random = 5'
```

For node `4`:

```
4.next   -> 5      => 4'.next   = 5'
4.random -> 3      => 4'.random = 3'
```

For node `3`:

```
3.random = NULL    => 3'.random = NULL
```

---

## Why This Works

- We never compare values
- We only work with **node addresses**
- Every pointer is redirected to the **copied node** using the hash map

This guarantees a **true deep copy**.

---

## Time & Space Complexity

| Metric | Value           |
| ------ | --------------- |
| Time   | O(n)            |
| Space  | O(n) (hash map) |

---

## Common Mistakes (Avoid These)

❌ Matching nodes by value instead of address
❌ Trying to set random pointers in first pass
❌ Forgetting that random can point backward
❌ Creating shallow copy (random pointing to old nodes)

---

## One-Line Summary

We create a deep copy of the linked list by mapping each original node to its copy, then using this mapping to correctly assign both `next` and `random` pointers.
