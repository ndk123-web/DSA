# 25. Reverse Nodes in k-Group

## Intuition

The main challenge of this problem is **not reversing a linked list**.

We already know how to reverse a linked list.

The real challenge is:

```text
How do we reverse exactly k nodes and reconnect the list correctly?
```

To solve this, we process the linked list **group by group**.

For each group:

1. Find the kth node.
2. Reverse the current group.
3. Reconnect the reversed group with the rest of the list.
4. Move to the next group.

---

# Key Pointers

We maintain four important pointers:

```text
groupPrev  -> node before the current group
groupStart -> first node of current group
kth        -> last node of current group
groupNext  -> first node after the group
```

Example:

```text
dummy -> 1 -> 2 -> 3 -> 4 -> 5 -> 6
          ^         ^    ^
      groupStart   kth  groupNext
```

For `k = 3`:

```text
groupStart = 1
kth        = 3
groupNext  = 4
```

---

# Why Dummy Node?

Suppose:

```text
1 -> 2 -> 3
```

After reversing:

```text
3 -> 2 -> 1
```

The head changes.

To handle this easily, we use:

```cpp
dummy->next = head;
```

This allows us to reconnect groups uniformly.

---

# Reversing Exactly k Nodes

Normal linked list reversal:

```cpp
while(curr)
```

But here we only reverse:

```text
[groupStart ... kth]
```

So we stop at:

```cpp
while(curr != groupNext)
```

---

# The Elegant Trick

Before reversing:

```cpp
prev = groupNext;
curr = groupStart;
```

Why?

Because after reversal:

```text
1 -> 4
```

gets connected automatically.

Example:

Before:

```text
1 -> 2 -> 3 -> 4 -> 5
```

After reversing:

```text
3 -> 2 -> 1 -> 4 -> 5
```

Notice:

```text
1 already points to 4
```

No extra reconnection is needed.

---

# Dry Run

Input:

```text
1 -> 2 -> 3 -> 4 -> 5 -> 6
k = 3
```

Initial:

```text
dummy -> 1 -> 2 -> 3 -> 4 -> 5 -> 6
 ^
groupPrev
```

Find kth:

```text
groupStart = 1
kth        = 3
groupNext  = 4
```

Reverse:

```text
3 -> 2 -> 1 -> 4 -> 5 -> 6
```

Reconnect:

```cpp
groupPrev->next = kth;
groupPrev = groupStart;
```

List becomes:

```text
dummy -> 3 -> 2 -> 1 -> 4 -> 5 -> 6
                     ^
                 groupPrev
```

Process next group:

```text
4 -> 5 -> 6
```

Reverse:

```text
6 -> 5 -> 4
```

Final answer:

```text
3 -> 2 -> 1 -> 6 -> 5 -> 4
```

---

# Why does this work?

After reversing:

```text
groupStart becomes the new tail.
kth becomes the new head.
```

Therefore:

```cpp
groupPrev->next = kth;
groupPrev = groupStart;
```

These two lines reconnect the list and prepare for the next iteration.

---

# Algorithm

1. Create a dummy node.
2. Set `groupPrev = dummy`.
3. Find the kth node.
4. If fewer than k nodes remain, stop.
5. Reverse the current group.
6. Reconnect the reversed group.
7. Move `groupPrev` to the new tail.
8. Repeat.

---

# Code

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* groupPrev = dummy;

        while (true) {

            // start-1 node
            ListNode* kth = groupPrev;
            ListNode* groupStart = kth->next;

            // find kth node from prevGroup
            for (int i = 0; i < k; i++) {
                kth = kth->next;

                if (kth == nullptr)
                    return dummy->next;
            }

            ListNode* groupNext = kth->next;

            ListNode* curr = groupPrev->next;
            ListNode* prev = groupNext;

            // reverse till the end
            while (curr != groupNext) {
                ListNode* next = curr->next;

                curr->next = prev;
                prev = curr;
                curr = next;
            }

            // still dummy->1 pointing so

            // dummy->next = 3
            groupPrev->next = kth;

            // now gPrev = 1
            groupPrev = groupStart;
        }

        return dummy->next;
    }
};
```

---

# Complexity Analysis

### Time Complexity

Each node is visited a constant number of times:

```text
O(N)
```

### Space Complexity

Only a few pointers are used:

```text
O(1)
```

---

# Key Learning

This problem teaches an important Linked List pattern:

```text
Find Group
    ↓
Reverse Group
    ↓
Reconnect Group
```

The difficult part is not reversing the list.

The difficult part is managing pointers safely and reconnecting groups correctly.
