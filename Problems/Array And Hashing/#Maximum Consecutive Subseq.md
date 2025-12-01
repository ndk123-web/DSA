
---

# **Longest Consecutive Sequence — C++ Solutions (HashSet + Sorting)**

Given an unsorted array of integers `nums`,
return the length of the **longest consecutive sequence** (numbers that appear one after another).

Example:

```
Input:  [100,4,200,1,3,2]
Output: 4   // because 1,2,3,4
```

---

# #️⃣ **1. Optimal O(n) Solution — HashSet + Starting-Point Check**

### **Idea**

* Insert all numbers inside a hash set
* For each number, check if it is the **start** of a sequence
  → i.e., `(num - 1)` does NOT exist
* Count how long the streak continues (`num + len`)
* Track the longest streak

### **Why It Works**

Because every number is processed **only once**,
and only numbers that begin a sequence trigger a scan.

---

## **Code (Optimal, O(n))**

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        if (nums.empty()) return 0;

        // unique values stored
        unordered_set<int> sett(nums.begin(), nums.end());
        int res = 1;

        for (auto num : nums) {

            // check if 'num' is a sequence start
            if (sett.find(num - 1) == sett.end()) {
                int len = 1;

                // count forward
                while (sett.find(num + len) != sett.end()) {
                    len++;
                }

                res = max(res, len);
            }
        }

        return res;
    }
};
```

### **Complexity**

| Operation              | Complexity |
| ---------------------- | ---------- |
| Building set           | O(n)       |
| Loop + streak building | O(n)       |
| **Total**              | **O(n)**   |

---

# #️⃣ **2. HashSet (Brute Force-ish) — O(n²) In Worst Case**

### **Idea**

* Insert everything in a hash set
* For every number in nums:

  * Continuously check `num+1`, `num+2`, … until it stops
* Track the longest chain

### **Why Slower?**

Because this scans forward for *every* number,
not only for numbers that start a sequence.

---

## **Code (Brute-ish, Simple to Understand)**

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> sett(nums.begin(), nums.end());
        int res = 0;
        
        for (auto num : nums) {
            int curr = num;
            int streak = 0;

            while (sett.find(curr) != sett.end()) {
                curr++;
                streak++;
            }

            res = max(res, streak);
        }

        return res;
    }
};
```

### **Complexity**

Worst case (like `[1,2,3,4,...n]`) →
every element walks through full chain → **O(n²)**.

---

# #️⃣ **3. Sorting Based — O(n log n)**

### **Idea**

* Sort the array
* Walk through and count consecutive numbers
* Skip duplicates
* Reset streak when gap > 1

---

## **Code (Sorting Approach, Clean & Safe)**

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;

        sort(nums.begin(), nums.end());

        int streak = 1, maxSeq = 1;

        for (int i = 0; i < nums.size() - 1; i++) {

            // skip duplicates
            if (nums[i] == nums[i + 1]) continue;

            // if not consecutive → reset
            if (nums[i] + 1 != nums[i + 1]) {
                streak = 1;
                continue;
            }

            // consecutive
            maxSeq = max(maxSeq, ++streak);
        }

        return maxSeq;
    }
};
```

### **Complexity**

| Step        | Time           |
| ----------- | -------------- |
| Sorting     | O(n log n)     |
| Single Pass | O(n)           |
| **Total**   | **O(n log n)** |

---

# #️⃣ **Comparison Table**

| Approach                             | Time       | Space       | Notes            |
| ------------------------------------ | ---------- | ----------- | ---------------- |
| **HashSet Starting-Point (Optimal)** | **O(n)**   | O(n)        | Best method      |
| HashSet Forward Scan                 | O(n²)      | O(n)        | Simple but slow  |
| Sorting                              | O(n log n) | O(1) / O(n) | Clean but slower |

---

# #️⃣ **Summary**

* Use **Method 1** in interviews → O(n) and clean.
* Method 2 is conceptually easy but slow.
* Method 3 is solid and easy but not truly optimal.

---