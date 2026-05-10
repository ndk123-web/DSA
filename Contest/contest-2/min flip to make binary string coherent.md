# 3922. Minimum Flips to Make Binary String Coherent

## Problem Link

3922. Minimum Flips to Make Binary String Coherent 

## Problem Description

You are given a binary string `s`. A string is considered **coherent** if it does not contain **"011"** or **"110"** as **subsequences**.

In one operation, you can flip any character in `s` ('0' to '1' or '1' to '0'). Return an integer denoting the **minimum number of modifications** required to make `s` coherent.

### Examples

* **Input:** `s = "1010"`
* **Output:** `1`
* 
**Explanation:** Flip `s[0]` to get `"0010"`, which contains no `"011"` or `"110"` subsequences.


* **Input:** `s = "0110"`
* **Output:** `1`
* 
**Explanation:** Flip `s[1]` to get `"0010"`, removing all forbidden subsequences `"011"` and `"110"`.



---

## My Playbook Entry (The "Tell")

* 
**Pattern Used:** Shape Recognition / String Properties.


* **The "Trick":** Instead of manually fixing forbidden triplets, identify valid end-states. A coherent string with at least one `0` can only have at most two `1`s, and those `1`s must be at the absolute boundaries.


* 
**Time Complexity:** $O(N)$.


* 
**Space Complexity:** $O(1)$.



---

## Approach: Target State Analysis

Brute-forcing every triplet results in a $O(N^4)$ complexity, which is too slow for large inputs. Instead, we calculate the cost to transform `s` into one of the four possible **coherent shapes**:

| Shape       | Description | Logic / Cost Calculation |
| ----------- | ----------- | ------------------------ |
| **Shape 1** | All `0`s    | Count of existing `1`s.  |

 |
| **Shape 2** | All `1`s | Count of existing `0`s.

 |
| **Shape 3** | Exactly one `1` | (Total `1`s) - 1. We keep one existing `1` and flip all others.

 |
| **Shape 4** | Boundary `1`s | Flip ends to `1` if they are `0` + Flip all middle `1`s to `0`.

 |

---

## Implementation

```cpp
class Solution {
public:
    int minFlips(string s) {
        int n = s.size();
        int zeroes = count(s.begin(), s.end(), '0');
        int ones = n - zeroes;

        // Shape 1 & 2: All 0s or All 1s
        int res = min(ones, zeroes);

        // Shape 3: Exactly one '1' anywhere in the string
        if (ones > 0) {
            res = min(res, ones - 1);
        }

        // Shape 4: Two '1's at the absolute boundaries (100...001)
        if (n > 2) {
            int cost = 0;
            if (s[0] == '0') cost++;       // Flip first to 1
            if (s[n - 1] == '0') cost++;   // Flip last to 1
            
            for (int i = 1; i < n - 1; i++) {
                if (s[i] == '1') cost++;   // Flip all middle 1s to 0
            }
            res = min(res, cost);
        }

        return res;
    }
};

```

---

## Complexity Analysis

* **Time Complexity:** $O(N)$, where $N$ is the length of the string. We perform one pass to count characters and one pass for the boundary cost.


* 
**Space Complexity:** $O(1)$, as we only use a few integer variables regardless of input size.