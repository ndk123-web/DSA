
---
# 📘 **Valid Parentheses — Stack Simulation**

Given a string containing `'(' , ')' , '{' , '}' , '[' , ']'`,
determine whether **all brackets are properly opened and closed in correct order**.
---

# ## 🎯 **Problem Summary**

The string is valid if:

1. Open brackets must be closed by the **same type** of brackets.
2. Open brackets must be closed **in the correct order**.
3. Every closing bracket must match a previously opened bracket.

Examples:

| Input      | Output | Explanation      |
| ---------- | ------ | ---------------- |
| `"()"`     | true   | Correct match    |
| `"({[]})"` | true   | Nested correctly |
| `"(]"`     | false  | Wrong match      |
| `"("`      | false  | Unclosed bracket |

---

# ## 🧠 **Core Idea**

Use a **stack**:

- Push opening brackets: `(`, `{`, `[`
- For closing brackets:

  - Stack must NOT be empty
  - Stack top must match corresponding opening bracket

- At the end, stack must be empty

This ensures proper order and type matching.

---

---

# ## 🥇 **Solution (Your Code Cleaned With Comments)**

### **Time: O(n)**

### **Space: O(n)**

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (char c : s) {

            // Push all opening brackets
            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            }

            // Closing bracket
            else {
                // No corresponding opening bracket
                if (st.empty()) return false;

                char top = st.top();

                // Mismatch cases
                if (c == ')' && top != '(') return false;
                if (c == '}' && top != '{') return false;
                if (c == ']' && top != '[') return false;

                st.pop(); // matched pair removed
            }
        }

        // All brackets must be closed
        return st.empty();
    }
};
```

---

# ## ✔ Why This Works

- Stack ensures **correct order**
  (last opened = first closed)
- Type checking ensures **correct bracket types**
- Ending with empty stack ensures no bracket remains unmatched

---

# ## 🧪 Example Dry Run

Input:

```
s = "{[()]}"
```

Stack operations:

```
{ → push
[ → push
( → push
) → match with ( → pop
] → match with [ → pop
} → match with { → pop
```

Stack empty → valid.

---

# ## 🏁 Summary Table

| Operation       | What Happens?        |
| --------------- | -------------------- |
| Opening bracket | push to stack        |
| Closing bracket | must match stack top |
| End of string   | stack must be empty  |

---

# 🎯 Key Takeaway

Valid Parentheses is a classic **stack problem**.
It checks **matching** and **ordering** using simple rules:

> _Push opens → check closes → pop on match → empty stack = valid._

---
