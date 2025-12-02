
---

# **Majority Element II — LeetCode 229**

## 🔍 **Why**

We must find elements appearing **more than ⌊n/3⌋ times**.
At most **2 such elements** can exist.
Brute (hashing) works but costs extra space.
Optimal: **Boyer–Moore Voting Algorithm (extended)**.

---

## **1️⃣ Approach 1 — HashMap (Simple)**

### **What**

Count frequencies using a map and collect elements > n/3.

### **How**

* Traverse and fill `freqMap`
* Check which keys have freq > n/3

### **Complexity**

* **Time:** O(n)
* **Space:** O(n)

---

## **✔ Code (HashMap Solution)**

```cpp
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        unordered_map<int, int> freq; 
        int n = nums.size();
        vector<int> res;

        // count freq
        for (int x : nums) freq[x]++;

        // pick freq > n/3
        for (auto &p : freq)
            if (p.second > n / 3)
                res.push_back(p.first);

        return res;
    }
};
```

---

# **2️⃣ Approach 2 — Boyer–Moore Voting (Optimal)**

## **Why**

For majority > n/3, there can be **max 2 candidates**.
Use vote cancellation logic to keep only potential winners.

## **What**

* Maintain `num1`, `num2` candidates
* Maintain their counters
* First pass → find candidates
* Second pass → verify them

## **How (Short Logic)**

* If match candidate → increment
* Else if counter is 0 → assign new candidate
* Else decrease both counters
* Recount and return valid ones

## **Complexity**

* **Time:** O(n)
* **Space:** O(1)

---

## **✔ Code (Boyer–Moore Optimal)**

```cpp
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int cnt1 = 0, cnt2 = 0;
        int num1 = -1, num2 = -1;
        int n = nums.size();

        // 1st pass → find candidates
        for (int x : nums) {
            if (x == num1) cnt1++;               // vote for candidate1
            else if (x == num2) cnt2++;          // vote for candidate2
            else if (cnt1 == 0) num1 = x, cnt1++; // assign candidate1
            else if (cnt2 == 0) num2 = x, cnt2++; // assign candidate2
            else cnt1--, cnt2--;                 // cancel votes
        }

        // 2nd pass → verify
        cnt1 = cnt2 = 0;
        for (int x : nums) {
            if (x == num1) cnt1++;
            else if (x == num2) cnt2++;
        }

        vector<int> res;
        if (cnt1 > n/3) res.push_back(num1);
        if (cnt2 > n/3) res.push_back(num2);

        return res;
    }
};
```

---

# ✅ **Summary**

| Method      | Time | Space | Notes                      |
| ----------- | ---- | ----- | -------------------------- |
| HashMap     | O(n) | O(n)  | Easiest                    |
| Boyer–Moore | O(n) | O(1)  | Best + interview-favourite |

---