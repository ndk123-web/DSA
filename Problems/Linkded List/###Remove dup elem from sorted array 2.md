## Intuition

Since the linked list is **sorted**, all duplicate values appear **consecutively**.

Instead of removing nodes one by one, we can think of the list as a collection of **groups**:

```text
1 -> 2 -> 3 -> 3 -> 4 -> 4 -> 5

Groups:
[1] [2] [3,3] [4,4] [5]
```

For each group:

* If the group size is **1**, keep it.
* If the group size is **greater than 1**, remove the entire group.

To achieve this, we traverse the list and detect whether the current value belongs to a duplicate group using a boolean flag.

---

## Approach

Maintain:

* `curr` → current node being processed.
* `prev` → last node that is guaranteed to remain in the final answer.
* `root` → head of the resulting list.
* `isDuplicate` → indicates whether the current value appears more than once.

### Steps

1. Traverse the list using `curr`.
2. For every value, move `curr` to the last occurrence of that value.
3. If duplicates were found:

   * Skip the entire group by connecting:

     ```cpp
     prev->next = curr->next;
     ```
4. If no duplicates were found:

   * The node is part of the final answer.
   * Update `prev`.
   * If it is the first valid node, initialize `root`.
5. Continue until the end of the list.

---

## Example

```text
Input:
1 -> 2 -> 3 -> 3 -> 4 -> 4 -> 5
```

Processing groups:

```text
[1]      -> keep
[2]      -> keep
[3,3]    -> remove
[4,4]    -> remove
[5]      -> keep
```

Result:

```text
1 -> 2 -> 5
```

---

## Algorithm

```text
Initialize:
curr = head
prev = nullptr
root = nullptr

While curr exists:

    isDuplicate = false

    Move curr to the last node of its value group

    If group contains duplicates:
        Remove the entire group

    Else:
        Keep the node
        Update prev
        Initialize root if needed

Return root
```

---

## Complexity Analysis

### Time Complexity

```text
O(n)
```

Each node is visited at most once while traversing duplicate groups.

### Space Complexity

```text
O(1)
```

Only a few pointers and a boolean variable are used.

---

## Key Observation

Because the list is **sorted**, duplicate values always form a continuous block:

```text
3 -> 3 -> 3
```

This allows us to process duplicates as a **group** rather than handling individual nodes, leading to an efficient **O(n)** solution with **constant extra space**.

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head){
            return nullptr;
        }

        ListNode* curr = head;
        ListNode* prev = nullptr;
        ListNode* root = nullptr;
        bool isDuplicate = false;

        while (curr) {
            isDuplicate = false;

            while (curr && curr->next && curr->val == curr->next->val) {
                isDuplicate = true;
                curr = curr->next;
            }

            // if not prev and no duplicate found, initialize root and prev
            if (!prev && !isDuplicate) {
                root = curr;
                prev = curr;
            }

            // if there prev and no duplicate found, update prev
            else if (prev && !isDuplicate) {
                prev = curr;
            }

            // if there prev and duplicate found, skip the entire group
            else if (prev && isDuplicate && curr) {
                prev->next = curr->next;
            }

            curr = curr->next;
        }

        return root;
    }
};
```