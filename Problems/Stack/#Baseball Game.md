
---
# 📘 **Baseball Game — Stack Simulation (Two Approaches)**

You are given a list of operations representing scoring actions in a baseball game.
You must simulate the game and compute the **final score** after all operations.
---

# ## 🎯 **Problem Summary (English)**

You start with **an empty record**.

For each operation in `operations`:

### **1. Integer x**

Record a new score `x`.

### **2. "+"**

Record a score equal to **the sum of the previous two scores**.

### **3. "D"**

Record a score equal to **double the previous score**.

### **4. "C"**

Remove (**invalidate**) the most recent score.

Return the **total sum** of all valid scores after processing all operations.

---

# ## 🧠 Example

Input:

```
["5","-2","4","C","D","+"]
```

Processing:

- 5 → record 5
- -2 → record -2
- 4 → record 4
- C → remove 4
- D → double last (-2 → -4)
- - → sum last two (-2 + -4 = -6)

Final scores: `[5, -2, -4, -6]`
Total = `-7`

---

---

# ## 🥉 **Approach 1 — Use Stack, Sum at the End**

### **Time: O(n)**

### **Space: O(n)**

### **Idea**

- Push scores onto a stack
- Apply operations directly
- At the end, pop all values to compute final sum

### **Code**

```cpp
class Solution {
public:
    int calPoints(vector<string>& operations) {
        int finalSum = 0;
        stack<int> st;

        for (auto &op : operations) {

            if (op == "+") {
                int first = st.top(); st.pop();
                int second = st.top();
                st.push(first);
                st.push(first + second);
            }

            else if (op == "D") {
                st.push(st.top() * 2);
            }

            else if (op == "C") {
                st.pop();
            }

            else {
                st.push(stoi(op));
            }
        }

        while (!st.empty()) {
            finalSum += st.top();
            st.pop();
        }

        return finalSum;
    }
};
```

### **Short Comment**

- Simple and clean
- Uses stack to track valid scores
- Final sum computed at the end

---

# ## 🥈 **Approach 2 — Stack + Running Sum (More Efficient)**

### **Time: O(n)**

### **Space: O(n)**

### **(Slightly better because sum maintained on the fly)**

### **Idea**

- Same stack logic
- But maintain running sum `res`
- Update sum during each operation
- Avoids summing stack at the end

### **Code**

```cpp
class Solution {
public:
    int calPoints(vector<string>& operations) {
        stack<int> st;
        int res = 0;

        for (string &op : operations) {

            if (op == "+") {
                int first = st.top(); st.pop();
                int second = st.top();
                st.push(first);
                st.push(first + second);
                res += (first + second);
            }

            else if (op == "D") {
                int newScore = st.top() * 2;
                st.push(newScore);
                res += newScore;
            }

            else if (op == "C") {
                res -= st.top();
                st.pop();
            }

            else {
                int x = stoi(op);
                st.push(x);
                res += x;
            }
        }

        return res;
    }
};
```

### **Short Comment**

- Faster sum calculation
- Maintains final score incrementally
- Still uses stack for rule operations

---

# ## 🏁 Summary Table

| Approach            | Time | Space | Notes                      |
| ------------------- | ---- | ----- | -------------------------- |
| Stack + sum at end  | O(n) | O(n)  | Easy to follow             |
| Stack + running sum | O(n) | O(n)  | More efficient in practice |

---

# 🎯 Key Takeaway

This problem is a **pure stack simulation**:
you simply track scores using push/pop and apply game rules exactly.

---
