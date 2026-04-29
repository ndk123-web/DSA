## Single Number (XOR)

## 🔹 Intuition

Every element appears twice except one.
We need an operation that **cancels duplicates automatically**.

👉 XOR is perfect:

* same numbers → cancel (`a ^ a = 0`)
* remaining → unique element

---

## 🔹 Approach

* Initialize `res = 0`
* XOR all elements with `res`
* duplicates cancel out, leaving only unique

---

## 🔹 Code

```cpp
int singleNumber(vector<int>& nums) {
    int res = 0;
    for (int x : nums) {
        res ^= x;
    }
    return res;
}
```

---

## 🔹 Dry Run

```
nums = [5, 6, 5]

res = 0
res = 0 ^ 5 = 5
res = 5 ^ 6 = 3
res = 3 ^ 5 = 6
```

👉 Answer = 6

---

## 🔹 Complexity

* Time: O(n)
* Space: O(1)

---

## 🔹 Key Concept

> XOR = bitwise cancellation
> duplicates vanish, unique survives

---