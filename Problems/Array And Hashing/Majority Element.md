
---

# 📌 **Majority Element — Boyer–Moore (+ HashMap Method)**

(LeetCode / NeetCode — Arrays & Hashing)

---

## **1. Why does this problem matter?**

Because the majority element appears **more than n/2 times**, it dominates the array.
This property allows an *O(n), O(1)* solution (Boyer–Moore), which is a classic interview trick.

---

## **2. What are we trying to do?**

Given `nums`, return the element that appears **strictly more than half** of the array size.

This element is **guaranteed to exist**.

---

## **3. How do we solve it?**

There are two main approaches:

---

## **A. HashMap Counting (Simple, but O(n) extra space)**

* Count frequencies
* Return the one whose count > n/2

✔ Clear, easy
✘ Uses extra memory

---

## **B. Boyer–Moore Voting Algorithm (Optimal)**

* Maintain a **candidate** and a **counter**
* Increase counter when same element
* Decrease counter when different element
* When counter becomes 0 → choose new candidate

Why it works?
Because majority element’s frequency is so high that it can never be fully canceled out.

✔ O(n) time
✔ O(1) space
✔ Professional, expected in interviews

---

## **4. Example Walkthrough**

Input: `[2,2,1,1,1,2,2]`

* Pick 2 → count = 1
* Next 2 → count = 2
* Next 1 → count = 1
* Next 1 → count = 0 → new candidate
* Next 1 → count = 1
* Next 2 → count = 0 → new candidate
* Next 2 → count = 1

Final candidate = **2**

---

## **5. Logic Summary**

### **HashMap**

* Count everything
* Return value occurring > n/2

### **Boyer–Moore**

* Use majority dominance
* Candidate survives cancellation
* The last standing value is the majority

---

## **6. C++ Code (Clean, short comments)**

### ✅ **Method 1: HashMap (O(n) space)**

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> freq;
        
        // Count occurrences
        for (int x : nums) {
            freq[x]++;
        }

        // Majority is guaranteed to exist
        int n = nums.size();
        for (auto &p : freq) {
            if (p.second > n / 2) {
                return p.first;
            }
        }

        return -1; // unreachable for valid input
    }
};
```

---

### ✅ **Method 2: Boyer–Moore Voting Algorithm (O(1) space)**

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = 0;  
        int count = 0;

        for (int x : nums) {

            // If count drops to zero, choose new candidate
            if (count == 0) {
                candidate = x;
                count = 1;
            }
            // Same as candidate → reinforce it
            else if (x == candidate) {
                count++;
            }
            // Different element → cancel out
            else {
                count--;
            }
        }

        return candidate; // majority guaranteed
    }
};
```

---

## **7. Complexity**

| Method      | Time | Space |
| ----------- | ---- | ----- |
| HashMap     | O(n) | O(n)  |
| Boyer–Moore | O(n) | O(1)  |

---

## **8. Notes for Interview / GitHub**

* Boyer–Moore is the **expected** answer.
* HashMap is okay for warm-up or clarity.
* No need to verify candidate (LeetCode guarantees majority).
* Boyer–Moore is a key pattern used in frequency-dominance problems.

---
