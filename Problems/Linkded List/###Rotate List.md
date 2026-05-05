## Rotate List

---

# 📌 Solution 1: Repeated Tail Rotation (Brute Force - Linked List)

### Intuition

Rotate the list one step at a time:

* Take the last node
* Move it to the front
* Repeat `k` times

---

### Approach

* Find the length of the list
* Reduce `k` using `k % n`
* For each rotation:

  * Traverse to the last node
  * Detach it and move it to the front

---

### Code

```cpp
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) return nullptr;

        ListNode* start = head;
        ListNode* newHead = start;
        ListNode *prev, *temp, *end;
        temp = start;

        int c = 1;
        while (temp && temp->next != nullptr) {
            prev = temp;
            temp = temp->next;
            end = temp;
            c++;
        }

        if (c == 1) return head;

        k = k % c;

        for (int i = 0; i < k; i++) {
            while (temp->next != nullptr) {
                prev = temp;
                temp = temp->next;
                end = temp;
            }

            newHead = end;
            prev->next = nullptr;
            end->next = start;
            start = end;
        }

        return newHead;
    }
};
```

---

### Complexity

* Time: O(n × k) → worst case O(n²)
* Space: O(1)

---

### Key Insight

Simulates rotation step-by-step, but inefficient due to repeated traversal.

---

---

# 📌 Solution 2: Array Rotation

### Intuition

Convert linked list → array, rotate array, rebuild list.

---

### Approach

* Store values in vector
* Rotate array `k` times
* Build new linked list from rotated values

---

### Code

```cpp
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) return nullptr;

        ListNode* temp = head;
        vector<int> nums;

        while (temp) {
            nums.push_back(temp->val);
            temp = temp->next;
        }

        int n = nums.size();
        k = k % n;

        for (int i = 0; i < k; i++) {
            int last = nums[n - 1];
            for (int j = n - 1; j >= 1; j--) {
                nums[j] = nums[j - 1];
            }
            nums[0] = last;
        }

        ListNode* dummy = new ListNode(-1);
        ListNode* curr = dummy;

        for (int num : nums) {
            curr->next = new ListNode(num);
            curr = curr->next;
        }

        return dummy->next;
    }
};
```

---

### Complexity

* Time: O(n × k)
* Space: O(n)

---

### Key Insight

Correct but inefficient. Avoids pointer complexity but sacrifices performance.

---

---

# 📌 Solution 3: Optimal (Cut and Reconnect)

### Intuition

Instead of rotating step-by-step:

* Find where the list should be cut
* Reconnect two parts

---

### Approach

1. Compute length `n`
2. Reduce `k = k % n`
3. Find new tail at position `n - k - 1`
4. Split list
5. Attach second part to front
6. Connect end to original head

---

### Code

```cpp
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) return nullptr;

        ListNode* temp = head;
        int n = 0;

        while (temp) {
            n++;
            temp = temp->next;
        }

        k = k % n;
        int newLast = n - k - 1;

        temp = head;
        for (int i = 0; i < newLast; i++) {
            temp = temp->next;
        }

        ListNode* secondPart = temp->next == nullptr ? nullptr : temp->next;
        temp->next = nullptr;

        if (secondPart == nullptr) {
            return head;
        }

        ListNode* newHead = secondPart;

        temp = secondPart;
        while (temp && temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = head;

        return newHead;
    }
};
```

---

### Complexity

* Time: O(n)
* Space: O(1)

---

### Key Insight

Convert the problem from “rotate k times” → “find cut position and reconnect”.

---

# 🔥 Final Comparison

| Solution   | Time  | Space | Remarks                |
| ---------- | ----- | ----- | ---------------------- |
| Brute (LL) | O(n²) | O(1)  | Repeated traversal     |
| Array      | O(n²) | O(n)  | Easier but inefficient |
| Optimal    | O(n)  | O(1)  | Best approach          |

---

# 🔥 Final Takeaway

The problem is not about rotating nodes repeatedly.
It is about identifying the **correct split point** and rebuilding the list efficiently.
