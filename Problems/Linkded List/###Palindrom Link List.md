# Intuition

A linked list is a palindrome if the sequence of values reads the same from left to right and right to left.

For example:

```text
1 -> 2 -> 3 -> 2 -> 1
```

The first half:

```text
1 -> 2
```

matches the reverse of the second half:

```text
1 -> 2
```

Instead of storing values in an array or string, we can use the structure of the linked list itself.

The idea is:

1. Find the middle of the linked list.
2. Reverse the second half.
3. Compare the first half with the reversed second half.

This gives an **O(n)** time solution with **O(1)** extra space.

---

# Approach

## Step 1: Find the Middle

Use the classic **slow and fast pointer** technique.

* `slow` moves one step at a time.
* `fast` moves two steps at a time.

```text
1 -> 2 -> 3 -> 2 -> 1

slow: ^
fast: ^
```

After traversal:

```text
1 -> 2 -> 3 -> 2 -> 1
          ^
        slow
```

---

### Odd Length

```text
1 -> 2 -> 3 -> 2 -> 1
          ^
        slow
```

`fast` will not be `nullptr`.

The middle node does not participate in palindrome comparison, so we skip it:

```cpp
slow = slow->next;
```

---

### Even Length

```text
1 -> 2 -> 2 -> 1
          ^
        slow
```

`fast` becomes `nullptr`.

No need to skip any node.

---

## Step 2: Reverse the Second Half

Suppose we have:

```text
1 -> 2 -> 3 -> 2 -> 1
```

After reaching the middle:

```text
Second Half:
2 -> 1
```

Reverse it:

```text
1 -> 2
```

Now we have:

```text
Left Side:   1 -> 2
Right Side:  1 -> 2
```

---

## Step 3: Compare Both Halves

Use two pointers:

```cpp
p1 = head;
p2 = reversedSecondHalf;
```

Compare node by node:

```text
1 == 1
2 == 2
```

If every value matches, the list is a palindrome.

Otherwise, it is not.

---

# Dry Run

### Input

```text
1 -> 2 -> 2 -> 1
```

### Find Middle

```text
slow = third node (2)
```

### Reverse Second Half

```text
2 -> 1
```

becomes

```text
1 -> 2
```

### Compare

```text
1 == 1
2 == 2
```

All values match.

### Result

```text
true
```

---

# Algorithm

```text
1. Find the middle using slow and fast pointers.

2. If the length is odd:
      Move slow one step ahead
      to skip the middle node.

3. Reverse the second half of the list.

4. Compare:
      First half
      Reversed second half

5. If any value differs:
      return false

6. Otherwise:
      return true
```

---

# Complexity Analysis

### Time Complexity

```text
Finding middle      : O(n)
Reversing half      : O(n)
Comparing halves    : O(n)
```

Total:

```text
O(n)
```

---

### Space Complexity

Only a few pointers are used:

```text
slow
fast
prev
curr
p1
p2
```

No extra array, stack, vector, or string is created.

```text
O(1)
```

---

# Key Observation

The crucial insight is that we do **not** need extra memory to remember the first half of the list.

By reversing the second half in-place:

```text
1 -> 2 -> 3 -> 2 -> 1
```

becomes logically:

```text
1 -> 2        1 -> 2
```

which allows a direct node-by-node comparison.

This transforms a problem that initially seems to require extra storage into an **O(1) space** solution using only pointer manipulation.

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
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // odd
        if (fast) {
            slow = slow->next;
        }

        // reverse the right side
        ListNode* curr = slow;
        ListNode* prev = nullptr;
        while (curr) {
            ListNode* nextNode = curr->next;

            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }

        ListNode* p1 = head;
        ListNode* p2 = prev;

        while (p2) {
            if (p1->val != p2->val)
                return false;

            p1 = p1->next;
            p2 = p2->next;
        }

        return true;
    }
};
```