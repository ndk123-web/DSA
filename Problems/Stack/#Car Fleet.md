# 🚗 Car Fleet — Detailed Explanation (Monotonic Stack)
---

## 📘 Problem Recap

You are given:

* `position[i]` → starting position of the `i-th` car
* `speed[i]` → speed of the `i-th` car
* `target` → destination position

### Rules:

* All cars move towards the same destination
* **Overtaking is NOT allowed**
* A faster car may catch a slower car and then move with it

### Definition: Car Fleet

> A **car fleet** is a group of cars that arrive at the destination **together**, at the **same time and speed**.

A **single car** is also considered a fleet.

---

## 🎯 Key Insight (Most Important)

> **Car fleets are decided by `time to reach destination`, not by speed alone.**

Once two cars have the same arrival time (or the rear one arrives earlier), they merge into **one fleet**.

---

## 🧠 Core Strategy

### Step 1: Combine position & speed

We bundle each car as:

```
(position, speed)
```

---

### Step 2: Sort cars by position (descending)

```cpp
sort(pr.rbegin(), pr.rend());
```

#### ❓ Why descending order?

Because:

* A car can only be affected by the **car directly in front of it**
* A rear car needs to know **what happens ahead** before deciding if it can catch up

So we always process:

```
closest to destination → farthest
```

This guarantees correct dependency handling.

---

## ⏱️ Step 3: Convert cars into arrival times

For each car:

```
time = (target - position) / speed
```

This time tells us:

> "How long will this car (or fleet) take to reach the destination?"

---

## 📚 Step 4: Monotonic Stack Logic

We use a stack (`st`) that stores:

```
arrival times of fleets
```

Each element in the stack represents **one fleet**.

---

### 🔥 The Critical Condition

```cpp
if (st.size() >= 2 && st.back() <= st[st.size() - 2]) {
    st.pop_back();
}
```

#### What does this mean?

Let:

* `st.back()` → time of **current (rear) car / fleet**
* `st[st.size()-2]` → time of **nearest front fleet**

If:

```
rear_time ≤ front_time
```

Then:

* Rear car is **faster or equal**
* It WILL catch the front fleet
* Overtaking is not allowed

➡️ They merge into **one fleet**
➡️ Rear fleet is removed (`pop_back()`)

### 🚧 Why only compare with `st[size-2]`?

Because:

* A fleet can only interact with the **nearest fleet in front**
* If it cannot catch that one, it can never reach further fleets

This is why **only one comparison is enough**.

---

## 🧪 Example Walkthrough

### Input

```
target = 10
position = [4,1,0,7]
speed    = [2,2,1,1]
```

### After sorting (descending position)

```
(7,1) → time = 3
(4,2) → time = 3
(1,2) → time = 4
(0,1) → time = 10
```

### Stack evolution

```
[3]
[3,3]   → merge → [3]
[3,4]
[3,4,10]
```

### Result

```
Number of fleets = 3
```

---

## 💻 Final Code

```cpp
class Solution {
private:
    vector<double> st;
    vector<pair<int,int>> pr;
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();

        for (int i = 0 ; i < n ; i++){
            pr.push_back({position[i],speed[i]});
        }

        sort(pr.rbegin(),pr.rend());

        for (auto& p : pr) {
            st.push_back((double)(target-p.first)/p.second);
            if (st.size() >= 2 && st.back() <= st[st.size() - 2]) {
                st.pop_back();
            }
        }

        return st.size();
    }
};
```

---

## ⏱️ Complexity Analysis

* **Time Complexity:** `O(n log n)` (sorting)
* **Space Complexity:** `O(n)` (stack)

---

## 🧠 Final Mental Model (Remember This)

> **Process cars from front to back.**
> **Convert them into arrival times.**
> **If a rear car arrives earlier → it merges.**
> **Stack size = number of fleets.**

---

