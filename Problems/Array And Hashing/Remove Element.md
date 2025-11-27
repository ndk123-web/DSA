
---

# 📌 **Remove Element — LeetCode (C++ Solutions)**

This folder contains **3 clean & professional solutions** for the LeetCode problem:
**“27. Remove Element”**

You are given an array and a value `val`.
Remove all occurrences of `val` **in-place** and return the count `k` of elements that are **not equal to `val`**.
The first `k` elements of the array must contain the valid values.
The remaining values do not matter.

---

##  **1. Why This Problem Matters**

This question teaches:

* in-place array modifications
* two-pointer pattern
* overwrite technique
* constant-space operations
* optimization thinking
* avoiding reallocation & erase shifts

Very common in interviews (FAANG level).

---

#  **2. Approaches Summary**

| Method                                  | Time | Space | Stability | Description                                          |
| --------------------------------------- | ---- | ----- | --------- | ---------------------------------------------------- |
| **Brute (Extra Vector)**                | O(n) | O(n)  | Yes       | Build a new list of non-val elements, then copy back |
| **Two-Pointer Overwrite (Recommended)** | O(n) | O(1)  | Yes       | Rewrite valid elements at front                      |
| **Replace-with-Last Trick (Fastest)**   | O(n) | O(1)  | No        | Replace val with last valid element, shrink size     |

---

#  **3. Approach: Extra Vector (Easy Brute)**

✔ Simple
✔ Clean
❌ Not constant space

### **Code**

```cpp
int removeElement(vector<int>& nums, int val) {
    vector<int> tmp;

    for (int num : nums) {
        if (num != val) {
            tmp.push_back(num);
        }
    }

    for (int i = 0; i < tmp.size(); i++) {
        nums[i] = tmp[i];
    }

    return tmp.size();
}
```

**Idea:** Collect non-val → copy to nums → return size.

---

#  **4. Approach: Two-Pointer Overwrite (Optimal & Stable)**

✔ In-place
✔ Constant space
✔ Recommended
✔ Order preserved for valid elements

### **Code**

```cpp
int removeElement(vector<int>& nums, int val) {
    int k = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != val) {
            nums[k] = nums[i];
            k++;
        }
    }

    return k;
}
```

**Idea:**

* `k` tracks where the next valid element should go
* Copy only valid numbers
* Return `k`

---

#  **5. Approach: Replace With Last (Fastest Trick)**

✔ O(1) operations
✔ No shifting
✔ Best when order does NOT matter
❌ Order changes

### **Code**

```cpp
int removeElement(vector<int>& nums, int val) {
    int i = 0, n = nums.size();

    while (i < n) {
        if (nums[i] == val) {
            nums[i] = nums[--n];   // replace with last valid
        } else {
            i++;
        }
    }

    return n;
}
```

### **Why it works?**

* When we see `val`, we overwrite it using the **last element**
* Shrink the “valid size” using `--n`
* Elements after index `n` are ignored

---

#  **6. Complexity Comparison**

| Approach              | Time | Space | Notes                          |
| --------------------- | ---- | ----- | ------------------------------ |
| Extra Vector          | O(n) | O(n)  | Easiest                        |
| Two-Pointer Overwrite | O(n) | O(1)  | Best overall                   |
| Replace-with-Last     | O(n) | O(1)  | Best when order doesn’t matter |

---

#  **7. Final Notes**

* Don’t use `erase()` → expensive O(n) shifts
* Don’t sort the array → violates in-place requirement
* Last method is the most optimized for unordered outputs

---