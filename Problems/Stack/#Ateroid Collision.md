
---

# 📘 **Asteroid Collision — Stack Simulation (Important Problem)**

Asteroids move in **one dimension**:

* Positive value → moves **right**
* Negative value → moves **left**

When two asteroids collide:

| Case                      | Result            |
| ------------------------- | ----------------- |
| Larger magnitude survives | smaller destroyed |
| Equal magnitude           | both destroyed    |
| Moving in same direction  | no collision      |

---

# ## 🎯 **Key Concept**

**A collision happens ONLY when:**

```
stack.back() > 0   (moving right)
and
current asteroid < 0   (moving left)
```

This means the right-moving asteroid from the stack meets the left-moving asteroid from input.

For all other cases:
→ No collision possible → push directly.

---

# ## 🧠 **Why Use a Stack?**

As we process asteroids left to right:

- The stack stores asteroids that are still alive.
- When a new asteroid comes:

  - Check conflict with the **last asteroid in stack**
  - Resolve collisions
  - Continue until no more collisions possible

This allows O(n) simulation.

---

# ## 🥇 **Code (Your Solution Cleaned + Explained Comments)**

```cpp
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {

        vector<int> st;   // behaves like stack

        for (int ast : asteroids) {

            // Collision only when ast < 0 and st.back() > 0
            while (!st.empty() && ast < 0 && st.back() > 0) {
                int diff = ast + st.back();   // compare magnitudes

                if (diff < 0) {
                    // |ast| > |stack.top| → stack asteroid destroyed
                    st.pop_back();
                }
                else if (diff > 0) {
                    // |stack.top| > |ast| → current asteroid destroyed
                    ast = 0;
                }
                else {
                    // Equal size → both destroy each other
                    st.pop_back();
                    ast = 0;
                }

                // If current asteroid died, break loop
                if (ast == 0) break;
            }

            // If asteroid still alive, push to stack
            if (ast != 0)
                st.push_back(ast);
        }

        return st;
    }
};
```

---

# ## 🔍 **Why the while-loop condition matters?**

### Condition:

```cpp
while (!st.empty() && ast < 0 && st.back() > 0)
```

This means:

- **st.back() > 0** → asteroid on stack moving RIGHT
- **ast < 0** → current asteroid moving LEFT

➡ Only these two can collide.

### No other combination causes collision:

| st.back() | ast | Direction        | Collision? | Reason                    |
| --------- | --- | ---------------- | ---------- | ------------------------- |
| +         | +   | both right       | ❌         | Never meet                |
| -         | -   | both left        | ❌         | Never meet                |
| -         | +   | left meets right | ❌         | Already passed each other |
| +         | -   | right meets left | ✅         | Collision happens         |

Hence the while-loop is the **heart of the solution**.

---

# ## 🧪 **Dry Run Example**

Input:

```
[5, 10, -5]
```

Process:

1. 5 → stack = [5]
2. 10 → stack = [5, 10]
3. -5:

   - Compare 10 and -5 → 10 survives
   - stack = [5, 10]

Output: **[5, 10]**

---

# ## 🧪 Example 2

Input:

```
[10, 2, -5]
```

Steps:

- 10 vs -5 → 10 survives
- 2 vs -5 → |-5| > |2| → 2 destroyed
- Now 10 vs -5 → 10 survives

Output:

```
[10]
```

---

# ## 🏁 Summary

### **What you learned:**

- Collision only happens when stack asteroid moving **right** and new asteroid moving **left**
- Use stack to simulate destruction
- Compare magnitudes and decide survival
- Continue collisions until stable
- Time complexity → **O(n)**

### **This is an important pattern: "stack for simulations"**

---
