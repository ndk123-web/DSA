# Merge k Sorted Lists — Complete Explanation (2 Approaches)

## Problem Summary

You are given `k` sorted linked lists.
Merge them into **one sorted linked list**.

---

## Approach 1️⃣: Sequential Merge (Merge One by One)

### Idea (Simple but Important)

- Take the **first list** as result
- Merge it with the second list
- Merge the result with the third list
- Continue until all lists are merged

This reuses the classic **merge two sorted lists** logic.

---

## Code — Sequential Merge

```cpp
class Solution {
private:
    ListNode* merge(ListNode* a, ListNode* b) {
        ListNode dummy(0);
        ListNode* curr = &dummy;

        while (a && b) {
            if (a->val <= b->val) {
                curr->next = a;
                a = a->next;
            } else {
                curr->next = b;
                b = b->next;
            }
            curr = curr->next;   // move forward
        }

        curr->next = a ? a : b;
        return dummy.next;
    }

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;

        ListNode* res = lists[0];
        for (int i = 1; i < lists.size(); i++) {
            res = merge(res, lists[i]);
        }

        return res;
    }
};
```

---

## Dry Run — Sequential Merge

### Input

```
lists = [
  1 → 4 → 5,
  1 → 3 → 4,
  2 → 6
]
```

### Step 1: merge list0 and list1

```
merge(1→4→5 , 1→3→4)
→ 1 → 1 → 3 → 4 → 4 → 5
```

### Step 2: merge result with list2

```
merge(result , 2→6)
→ 1 → 1 → 2 → 3 → 4 → 4 → 5 → 6
```

Final output achieved.

---

## Time & Space Complexity

- **Time:** `O(k * N)`

  - Each merge takes O(N)
  - Done k times

- **Space:** `O(1)` extra (node reuse)

---

## Issues You Faced (and Why)

### ❌ Missing `curr = curr->next`

- Caused infinite loop / corrupted list
- `curr` must move after attaching node

### ❌ Iterator vs pointer confusion earlier

- `lists.begin()` ≠ `ListNode*`
- Correct usage is `lists[i]`

---

## Verdict for Approach 1

| Aspect      | Status                        |
| ----------- | ----------------------------- |
| Simplicity  | ✅ Very easy                  |
| Correctness | ✅                            |
| Performance | ❌ Slow for large `k`         |
| Interview   | ⚠️ Acceptable but not optimal |

---

---

## Approach 2️⃣: Min Heap (Optimal Solution)

### Idea (Industry Standard)

- Use a **min heap** to always pick the smallest head among `k` lists
- Push first node of every list into heap
- Repeatedly:

  - Pop smallest node
  - Attach it to result
  - Push its `next` node (if exists)

This avoids repeated full merges.

---

## Code — Heap Based Merge

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;

        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val > b->val;
        };

        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> minheap(cmp);

        for (auto& list : lists) {
            if (list != nullptr) {
                minheap.push(list);
            }
        }

        ListNode dummy(0);
        ListNode* curr = &dummy;

        while (!minheap.empty()) {
            ListNode* node = minheap.top();
            minheap.pop();

            curr->next = node;
            curr = curr->next;

            if (node->next != nullptr) {
                minheap.push(node->next);
            }
        }

        return dummy.next;
    }
};
```

---

## Dry Run — Heap Based

### Input

```
lists = [
  1 → 4 → 5,
  1 → 3 → 4,
  2 → 6
]
```

### Initial heap

```
Heap: [1, 1, 2]
```

### Iterations

| Heap Pop | Result List   | Push Next |
| -------- | ------------- | --------- |
| 1        | 1             | push 4    |
| 1        | 1 → 1         | push 3    |
| 2        | 1 → 1 → 2     | push 6    |
| 3        | 1 → 1 → 2 → 3 | push 4    |
| 4        | ... → 4       | push 5    |
| 4        | ... → 4       | none      |
| 5        | ... → 5       | none      |
| 6        | ... → 6       | none      |

Final result:

```
1 → 1 → 2 → 3 → 4 → 4 → 5 → 6
```

---

## Time & Space Complexity

- **Time:** `O(N log k)`
- **Space:** `O(k)` (heap)

---

## Issues You Faced (and Why)

### ❌ `ListNode* res(0)`

- This creates a **null pointer**
- Not a dummy node

### ✅ Correct Fix

```cpp
ListNode dummy(0);
ListNode* curr = &dummy;
```

---

## Comparison — Both Approaches

| Feature              | Sequential Merge | Heap Merge |
| -------------------- | ---------------- | ---------- |
| Time                 | O(k·N)           | O(N log k) |
| Space                | O(1)             | O(k)       |
| Code Simplicity      | High             | Medium     |
| Performance          | Poor for big k   | Excellent  |
| Interview Preference | ⚠️               | ✅         |

---

## Final Takeaways (Important)

- Sequential merge teaches **linked list fundamentals**
- Heap merge shows **real algorithmic optimization**
- Your bugs were **pointer-movement & dummy-node issues**, not logic issues
- Both solutions are valid — heap one is **production grade**

---

## One-Line Mental Model

> **Sequential = merge again and again** > **Heap = always pick smallest head**

---
