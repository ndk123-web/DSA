##  Number of 1 Bits (Hamming Weight)

## 🔹 Intuition

We need to count how many bits are set (1s).

👉 Two ways:

1. Check every bit
2. Remove set bits directly (optimized)

---

## 🔹 Approach (Optimal - Brian Kernighan)

Key trick:

```cpp
n = n & (n - 1);
```

👉 removes the **last set bit**

---

## 🔹 Code

```cpp
int hammingWeight(int n) {
    int count = 0;
    while (n) {
        n = n & (n - 1);
        count++;
    }
    return count;
}
```

---

## 🔹 Dry Run

```
n = 13 → 1101

Step 1: 1101 → 1100
Step 2: 1100 → 1000
Step 3: 1000 → 0000
```

👉 Count = 3

---

## 🔹 Complexity

* Time: O(number of set bits)
* Space: O(1)

---

## 🔹 Key Concept

> Instead of checking all bits, remove only the ones that matter
