---

# #️⃣ **Subarray Sum Equals K — LeetCode 560**

**Pattern:** Prefix Sum + HashMap
**Difficulty:** Medium
**Topics:** Arrays, Prefix Sum, Hashing

---

# 🔥 **WHY**

We want to count **all subarrays** whose sum = **k**.
Brute-force checks all possible subarrays → **O(n²)**.
But observe:

**Subarray(i+1..j) = prefix[j] − prefix[i]**

So if:

```
prefix[i] = prefix[j] − k
```

→ subarray ending at j has sum k.

This means every prefix sum is a **potential starting point**.
HashMap stores frequencies of prefix sums so we can check in O(1).

---

# 🔥 **WHAT**

Use:

- `currentSum` → running prefix sum
- `prefixMap[sum]` → how many times this prefix sum appeared
- For each index j:

```
difference = currentSum − k
count += prefixMap[difference]
prefixMap[currentSum]++
```

This counts all valid subarrays ending at j.

---

# 🔥 **HOW**

1. Start with `prefixMap[0] = 1`
   → handles cases where subarray starting from index 0 has sum k.

2. Add numbers to build running prefix.

3. At each index, check if we have seen `(currentSum − k)` before.

4. If yes, every occurrence = one valid subarray.

5. Store current prefix for future indexes.

---

# 🔥 **EXAMPLE (Quick Visualization)**

For nums = `[2, -1, 1, 2]`, k = 2

| j   | num | curSum | diff=curSum−k | prefixMap[diff] | Count gained |
| --- | --- | ------ | ------------- | --------------- | ------------ |
| -1  | -   | 0      | -             | prefixMap={0:1} | -            |
| 0   | 2   | 2      | 0             | 1               | +1           |
| 1   | -1  | 1      | -1            | 0               | 0            |
| 2   | 1   | 2      | 0             | 1               | +1           |
| 3   | 2   | 4      | 2             | 2               | +2           |

Total = **4 subarrays**.

---

# 🔥 **LOGIC (Short & Clear)**

- Every prefix sum is a checkpoint.

- If at index j:

  ```
  currentSum - k = old prefix sum
  ```

  → removing that old prefix gives a subarray of sum k.

- If that old prefix appeared multiple times,
  → multiple valid subarrays exist.

---

# 🧩 **CODE — Prefix Sum + HashMap (Optimal O(n))**

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> prefixMap;
        int count = 0 , currentSum = 0;

        // because if first sum is k then it wont go to wrong direction
        prefixMap[0] = 1;

        for (auto& num : nums) {

            // add the number sequentially
            currentSum = currentSum + num;

            // get the difference
            int difference = currentSum - k;

            // if 0 / count then just add into the count
            count = count + prefixMap[difference];

            // its important because if 2 time sum is there
            // it means there are 2 subarrays whose sum is currentSum
            prefixMap[currentSum]++;
        }

        return count;
    }
};
```

---

# 🧩 **CODE — Brute Force (O(n²))**

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int count = 0;

        for (int i = 0; i < n; i++) {
            int sum = 0;

            for (int j = i; j < n; j++) {
                sum += nums[j];
                if (sum == k) count++;
            }
        }

        return count;
    }
};
```

---

# ⚙️ **COMPLEXITY**

| Approach         | Time     | Space    |
| ---------------- | -------- | -------- |
| Brute-force      | O(n²)    | O(1)     |
| Prefix + HashMap | **O(n)** | **O(n)** |

---

# 📝 **SUMMARY**

- Subarray sum = difference of prefix sums
- `difference = currentSum − k`
- `prefixMap[difference]` gives number of valid start points
- Every prefix creates future opportunities
- HashMap makes it O(n)

---
