## Counting Bits

## 🔹 Intuition

For every number `i`, count its set bits.

Your approach:
👉 brute force using bit checking

---

## 🔹 Approach

* Loop from `0 → n`
* For each number:

  * count bits using `& 1`
  * shift right

---

## 🔹 Code

```cpp
vector<int> countBits(int n) {
    vector<int> result;

    for (int i = 0; i <= n; i++) {
        int count = 0;
        int t = i;
        while (t > 0) {
            if (t & 1) count++;
            t >>= 1;
        }
        result.push_back(count);
    }

    return result;
}
```

---

## 🔹 Dry Run

```
n = 5

0 → 000 → 0
1 → 001 → 1
2 → 010 → 1
3 → 011 → 2
4 → 100 → 1
5 → 101 → 2
```

👉 Output = [0,1,1,2,1,2]

---

## 🔹 Complexity

* Time: O(n * log n)
* Space: O(n)

---

## 🔹 Optimization Insight (IMPORTANT)

Better solution exists:

```cpp
result[i] = result[i >> 1] + (i & 1);
```

👉 reuse previous results (DP)

---

## 🔹 Key Concept

> each number = previous number / 2 + last bit

---

# 🔥 FINAL SUMMARY (Lock this)

| Problem          | Core Idea                     |
| ---------------- | ----------------------------- |
| Single Number    | XOR cancels duplicates        |
| Number of 1 Bits | remove set bits (`n & (n-1)`) |
| Counting Bits    | reuse results (DP)            |

---

If you want next step:
👉 I’ll give you **advanced bit problems (interview level)** like

* Single Number II
* Two unique numbers
* Subsets using bitmask

That’s where this topic actually becomes powerful.
