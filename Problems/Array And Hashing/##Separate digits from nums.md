# 2553. Separate the Digits in an Array

### Problem Link

[Separate the Digits in an Array](https://leetcode.com/problems/separate-the-digits-in-an-array/)

### Problem Description

Given an array of positive integers `nums`, return an array `answer` that consists of the digits of each integer in `nums` after separating them in the same order they appear.

* **Example:** `nums = [13, 25, 83, 77]` $\rightarrow$ `[1, 3, 2, 5, 8, 3, 7, 7]`

---

### My Playbook Entry (The "Tell")

* 
**Pattern Used:** Digit Extraction & Result Construction.


* 
**The "Trick":** Since extracting digits using `% 10` gives them in reverse order, we must either fill a pre-allocated array from the **back** or use a **helper/string conversion** to maintain the original sequence.


* 
**The "Discovery":** Converting a numeric `char` to `int` is efficiently done via `c - '0'`, avoiding the common `stoi()` compiler error for single characters.



---

### Comparison of Approaches

| Feature          | Approach 1: Math + Back-Filling                             | Approach 2: String + ASCII Trick                               |
| ---------------- | ----------------------------------------------------------- | -------------------------------------------------------------- |
| **Logic**        | Counts total digits first, then fills from `size-1` to `0`. | Uses a helper function to reverse digits or convert to string. |
| **Memory**       | **More Efficient.** Pre-allocates exact size.               | Uses temporary strings and `push_back`.                        |
| **Key C++ Tool** | Manual Modulo (`%`) and Division (`/`).                     | `to_string()`, `reverse()`, and `char - '0'`.                  |
| **Complexity**   | $O(N \cdot K)$                                              | $O(N \cdot K)$                                                 |

---

### Implementation

#### Strategy 1: The "Back-Filling" Method

> **Why it works:** By knowing the total size of the final array beforehand, we can iterate through the input numbers in reverse and place their digits starting from the end of the result vector.

```cpp
// Pattern: Pre-allocation & Reverse Iteration
// Trick: Fill the result vector from the back to maintain digit order.
// Complexity: O(N*K) Time | O(N*K) Space
class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        int n = nums.size();
        int totalDigits = 0;

        // Pass 1: Find the exact size needed
        for (int num : nums) {
            int temp = num;
            while (temp > 0) {
                totalDigits++;
                temp /= 10;
            }
        }

        vector<int> res(totalDigits);
        int writeIdx = totalDigits - 1;

        // Pass 2: Fill from the back
        for (int i = n - 1; i >= 0; i--) {
            int temp = nums[i];
            while (temp > 0) {
                res[writeIdx--] = temp % 10;
                temp /= 10;
            }
        }
        return res;
    }
};

```

#### Strategy 2: The "String Conversion" Method (The Discovery Way)

> **Why it works:** This leverages your discovery of the ASCII property. We convert the number to a string to easily access digits from left-to-right.
> 
> 

```cpp
// Pattern: String Manipulation
// Trick: Use (char - '0') to convert ASCII values back to integers.
// Complexity: O(N*K) Time | O(N*K) Space
class Solution {
public:
    void addToRes(int num, vector<int>& res) {
        string s = to_string(num);
        for (char c : s) {
            [cite_start]// The "Aha!" moment: char to int conversion [cite: 726]
            res.push_back(c - '0'); 
        }
    }

    vector<int> separateDigits(vector<int>& nums) {
        vector<int> res;
        for (int num : nums) {
            addToRes(num, res);
        }
        return res;
    }
};

```

---

### Complexity Analysis

* **Time Complexity:** $O(N \cdot K)$, where $N$ is the number of integers in the array and $K$ is the maximum number of digits in any integer. We process every digit of every number exactly once.


* **Space Complexity:** $O(N \cdot K)$ to store the result vector.

---