
---

# Contains Nearby Duplicate — LeetCode 219

**Pattern:** Hash Map, Sliding Window
**Difficulty:** Easy–Medium
**Problem:**
Return true if there exist two indices `i` and `j` such that:

```
nums[i] == nums[j]  
and  
|i - j| ≤ k
```

Else return false.

---

# 1. Brute Force (Using HashMap of Vectors)

### Idea

Store all indices of each number.
Whenever we see the same number again, check the last index stored.
If the distance is ≤ k, return true.

### Code

```cpp
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, vector<int>> hashMap;

        for (int i = 0; i < n; i++) {
            if (hashMap.find(nums[i]) != hashMap.end()) {
                // check last occurrence
                if (i - hashMap[nums[i]].back() <= k)
                    return true;
            }
            hashMap[nums[i]].push_back(i);
        }
        return false;
    }
};
```

### Complexity

* Time: O(n) average (but each number may store many indices)
* Space: O(n)

---

# 2. Better Approach — HashMap (Store Last Seen Index Only)

### Idea

Instead of storing all positions, store the **latest index** of each value.
When encountering the same number again:

```
i - lastIndex <= k → true
```

### Code

```cpp
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> hashMap;

        for (int i = 0; i < nums.size(); i++) {
            if (hashMap.find(nums[i]) != hashMap.end()) {
                if (i - hashMap[nums[i]] <= k)
                    return true;
            }
            hashMap[nums[i]] = i;
        }
        return false;
    }
};
```

### Complexity

* Time: O(n)
* Space: O(n)

This is the standard solution used in most interviews.

---

# 3. Optimal Approach — Sliding Window + HashSet

### Idea

Use a sliding window of size `k`:

* Keep at most `k` elements in a hash set
* Before adding `nums[right]`, ensure the window size is ≤ k
* If the element already exists in the window → duplicate within distance k

This avoids storing indices entirely.

### Code

```cpp
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> hashSet;
        int left = 0;

        for (int right = 0; right < nums.size(); right++) {
            // maintain window size <= k
            if (right - left > k) {
                hashSet.erase(nums[left]);
                left++;
            }

            if (hashSet.find(nums[right]) != hashSet.end()) {
                return true;
            }

            hashSet.insert(nums[right]);
        }

        return false;
    }
};
```

### Complexity

* Time: O(n)
* Space: O(k)

This is the **best** solution: minimal memory, clean logic.

---

# Summary

| Method                   | Idea                       | Time | Space |
| ------------------------ | -------------------------- | ---- | ----- |
| HashMap (vector indices) | Track all indices          | O(n) | O(n)  |
| HashMap (last index)     | Track only last occurrence | O(n) | O(n)  |
| Sliding Window + Set     | Keep window of size k      | O(n) | O(k)  |

Sliding Window is the cleanest and most optimized approach.

---
