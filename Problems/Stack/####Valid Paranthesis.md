## Valid Parenthesis String

### Intuition

The presence of `*` makes the problem non-trivial because it can represent `'('`, `')'`, or an empty string. A simple count-based approach fails since **order matters**. Parentheses must be matched respecting their positions.

To handle this, track indices of `'('` and `'*'` separately. This allows flexible matching while preserving ordering constraints.

---

### Key Idea

* Use two stacks:

  * `left` → stores indices of `'('`
  * `star` → stores indices of `'*'`

* While traversing:

  * Try to match `')'` with `'('` first
  * If not available, use `'*'` as `'('`
  * If neither is available, the string is invalid

* After traversal:

  * Match remaining `'('` with `'*'`
  * Ensure correct order: `'*'` must come **after** `'('` to act as `')'`

---

### Approach

1. Traverse the string:

   * If `'('` → push index into `left`
   * If `'*'` → push index into `star`
   * If `')'`:

     * If `left` not empty → pop from `left`
     * Else if `star` not empty → pop from `star`
     * Else → return false

2. Post-processing:

   * While both stacks are non-empty:

     * If top of `left` > top of `star` → invalid (order violated)
     * Else → pop both

3. Final check:

   * If `left` is empty → valid
   * Else → invalid

---

### Code

```cpp
class Solution {
public:
    bool checkValidString(string s) {
        stack<int> left, star;

        for (int i = 0 ; i < s.size(); i++) {

            if (s[i] == '(') {
                left.push(i);
            }
            
            else if (s[i] == '*') {
                star.push(i);
            }

            // means its close bracket 
            else {
                if (!left.empty()) left.pop();
                else if (!star.empty()) star.pop();
                else return false;
            }
        }

        while (!left.empty() && !star.empty()) {

            // if leftParaIndex greate than star para then we cant say that its valid 
            if (left.top() > star.top()) return false;

            // if valid then pop from both 
            left.pop();
            star.pop();            
        }

        // if in last left Para empty then true 
        return left.empty();
    }
};
```

---

### Example

```
Input: s = "(*))"

Step-by-step:
- '(' → push to left
- '*' → push to star
- ')' → match with '('
- ')' → match with '*'

Result: valid
```

---

### Complexity

* Time Complexity: O(n)
* Space Complexity: O(n)

---

### Why This Works

* Matching `')'` greedily with `'('` ensures correctness
* Using `'*'` as fallback preserves flexibility
* Index comparison guarantees valid ordering of parentheses
* Final matching ensures no unmatched `'('` remains
