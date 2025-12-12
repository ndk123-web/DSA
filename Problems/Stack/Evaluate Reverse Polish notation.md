---
# 📘 **Evaluate Reverse Polish Notation (RPN) — Stack Based Solution**

You are given an array of tokens representing an arithmetic expression in **Reverse Polish Notation (postfix notation)**.

You must evaluate the expression and return the final integer result.
---

# ## 🎯 **What is Reverse Polish Notation (RPN)?**

In RPN:

- Operands come **before** operators
- Example:

  ```
  ["2","1","+","3","*"]
  ```

  Means:

  ```
  (2 + 1) * 3 = 9
  ```

### 💡 Why RPN Works?

Because no parentheses or precedence rules needed.
RPN is always unambiguous.

---

# ## 🧠 **Core Idea — Use a Stack**

Process tokens left to right:

1. If token is a **number** → push onto stack
2. If token is an **operator**:

   - Pop top two numbers
   - Apply operation → push the result back

At the end, only one element remains → the final answer.

---

# ## ✔ Valid Operators

```
+ , - , * , /
```

For division → result should truncate toward **zero**
(as per C++ integer division rules).

---

# ## 🥇 **Stack-Based Implementation**

### **Time Complexity: O(n)**

### **Space Complexity: O(n)**

```cpp
class Solution {
private:
    stack<int> st;

    // process each token
    void evaluate(const string& op) {

        // if operator
        if (op == "+" || op == "-" || op == "*" || op == "/") {
            int a = st.top(); st.pop();       // right operand
            int b = st.top(); st.pop();       // left operand
            int result = 0;

            if (op == "+") result = b + a;
            else if (op == "-") result = b - a;
            else if (op == "*") result = b * a;
            else if (op == "/") result = b / a; // truncates toward zero

            st.push(result);
        }

        // if number
        else {
            st.push(stoi(op));
        }
    }

public:
    int evalRPN(vector<string>& tokens) {
        for (auto& t : tokens)
            evaluate(t);

        return st.top();              // final result
    }
};
```

---

# ## 🧪 **Example Dry Run**

### Input:

```
["2","1","+","3","*"]
```

| Token | Action         | Stack |
| ----- | -------------- | ----- |
| 2     | push           | [2]   |
| 1     | push           | [2,1] |
| +     | pop 1,2 → 2+1  | [3]   |
| 3     | push           | [3,3] |
| \*    | pop 3,3 → 3\*3 | [9]   |

**Output: 9**

---

# ## 🧪 Example 2

### Input:

```
["4","13","5","/","+"]
```

Steps:

- 13 / 5 = 2 (truncate toward zero)
- 4 + 2 = 6

**Output: 6**

---

# ## 🏁 Summary Table

| Token Type | Action                         |
| ---------- | ------------------------------ |
| Number     | push onto stack                |
| Operator   | pop two, apply op, push result |
| End        | stack top is result            |

---

# 🎯 Final Takeaway

RPN evaluation is a perfect fit for stack:

- Operators always use last two operands
- Push operands, pop when operator seen
- Works in one pass
- No parentheses or precedence handling needed

This is a **classic stack interview question**.

---
