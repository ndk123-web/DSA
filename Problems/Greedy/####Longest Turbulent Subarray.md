# 📘 Longest Turbulent Subarray

## 🧾 Problem Summary

Given an integer array `arr`, return the length of the longest subarray where the comparison between adjacent elements **alternates** between greater-than and less-than.

---

## 🔍 Definition of Turbulence

A subarray is **turbulent** if:

For every adjacent pair:

* `arr[i-1] < arr[i] > arr[i+1] < arr[i+2] ...`
  OR
* `arr[i-1] > arr[i] < arr[i+1] > arr[i+2] ...`

👉 In simple terms:

> The comparison signs must **flip at every step**

---

## 🧠 Key Insight

Instead of tracking "up" and "down" manually, track the **sign of comparison**:

* `+1` → increasing (`arr[i] > arr[i-1]`)
* `-1` → decreasing (`arr[i] < arr[i-1]`)
* `0` → equal (breaks turbulence)

### Core condition:

```id="t0g4q7"
current_cmp * previous_cmp == -1
```

✔ Means: sign flipped → valid turbulence
❌ Means: same sign or zero → break/reset

---

## 📊 Example

Input:

```id="9sv2co"
arr = [2,4,3,2,2,5,1,4]
```

Comparisons:

```id="i7m1ap"
2→4  +1
4→3  -1  ✅ flip
3→2  -1  ❌ same → break
2→2   0  ❌ break
2→5  +1
5→1  -1  ✅ flip
1→4  +1  ✅ flip
```

Longest turbulent subarray:

```id="pmu4dp"
[2,5,1,4] → length = 4
```

---

## ⚙️ Approach (Sliding Window)

We scan the array once and maintain:

* `curr_len` → current turbulent length
* `max_len` → maximum found
* `prev_cmp` → previous comparison sign

---

### 🧩 Transition Rules

For each index `i`:

1. Compute:

   ```cpp
   cmp = compare(arr[i], arr[i-1])
   ```

2. Cases:

   * **If `cmp == 0`**

     * Reset → `curr_len = 1`

   * **If sign flips**

     ```id="knsx84"
     cmp * prev_cmp == -1
     ```

     * Extend → `curr_len++`

   * **Else**

     * Restart from current pair → `curr_len = 2`

3. Update:

   ```cpp
   max_len = max(max_len, curr_len);
   prev_cmp = cmp;
   ```

---

## 💻 Implementation (C++)

```cpp
int maxTurbulenceSize(vector<int>& arr) {
    int n = arr.size();
    if (n == 1) return 1;

    int max_len = 1, curr_len = 1;
    int prev_cmp = 0;

    for (int i = 1; i < n; i++) {
        int cmp = (arr[i] > arr[i-1]) ? 1 : (arr[i] < arr[i-1]) ? -1 : 0;

        if (cmp == 0) {
            curr_len = 1;
        } else if (cmp * prev_cmp == -1) {
            curr_len++;
        } else {
            curr_len = 2;
        }

        max_len = max(max_len, curr_len);
        prev_cmp = cmp;
    }

    return max_len;
}
```

---

## ⏱️ Complexity

* **Time:** `O(n)` (single pass)
* **Space:** `O(1)` (no extra memory)

---

## ⚠️ Common Mistakes

1. ❌ Trying two passes (start with up / down)
   → unnecessary

2. ❌ Tracking expected direction manually
   → leads to messy logic

3. ❌ Forgetting equal elements reset everything

---

## 🧩 Pattern Recognition Tip

This problem is a variation of:

* Alternating sequence
* Wiggle subarray
* Peak-valley pattern

👉 Whenever you see:

> “alternating”, “zig-zag”, “flip condition”

Think:

```id="i9gq6y"
compare signs, not values
```

---

## 🧠 Final Takeaway

> Don’t predict direction — **observe sign changes**

That’s the difference between struggling and solving this cleanly.