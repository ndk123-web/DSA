# Intuition

A brute force approach would generate every possible subarray and calculate its sum.

For an array of size `n`, total subarrays are:

\frac{n(n+1)}{2}

which leads to:

```txt id="4jlwm1"
O(n²)
```

or worse if we calculate sums repeatedly.

Instead of checking all subarrays directly, we use:

# Prefix Sum + HashMap

The key observation is:

If:

```txt id="r9jlwm"
currentPrefix
```

is the sum from:

```txt id="1wjglmw"
0...i
```

and:

```txt id="m7jlwm"
previousPrefix
```

is the sum from:

```txt id="5-vesm"
0...j
```

then subtracting them removes the left portion:

currentPrefix - previousPrefix

This leaves:

```txt id="2jlwm5"
(j+1)...i
```

which is a subarray.

So if we want subarray sum:

```txt id="sjlwmo"
k
```

then:

currentPrefix - previousPrefix = k

Rearranging:

previousPrefix = currentPrefix - k

This means:

# If an earlier prefix sum equal to `(currentPrefix - k)` exists, then removing that earlier prefix leaves a subarray whose sum is exactly `k`.

---

# Core Idea

We store:

```txt id="q0gqz0"
prefixSum -> frequency
```

inside a hashmap.

At every index:

1. Update current prefix sum
2. Check how many earlier prefix sums equal:

currentPrefix-k

3. Every occurrence forms one valid subarray ending at current index.

---

# Why Frequency Matters

Suppose:

```txt id="mwo6rw"
currentPrefix = 4
k = 3
```

Then we need:

previousPrefix = 4-3=1

If prefix sum `1` appeared:

```txt id="ahj9pp"
2 times
```

then:

# 2 different subarrays end at current index with sum `3`.

That is why we store frequencies instead of just existence.

---

# Important Initialization

```cpp id="uf9yxn"
mapp[0] = 1;
```

This represents:

# a virtual prefix sum before the array starts.

Imagine:

```txt id="rzjdc7"
index = -1
prefixSum = 0
```

This helps detect subarrays starting from index `0`.

---

# Dry Run

Example:

```txt id="7o2qee"
nums = [1,-1,1,1,1,1]
k = 3
```

---

# Prefix Sums

```txt id="kfigjf"
index:   0  1 2 3 4 5
nums :   1 -1 1 1 1 1
pSum :   1  0 1 2 3 4
```

---

# At i = 4

Current:

```txt id="1wx5bc"
pSum = 3
```

Need:

3-3=0

Map contains:

```txt id="1bj01y"
mapp[0] = 2
```

Meaning prefix sum `0` appeared twice:

* before array started
* at index `1`

So two valid subarrays end at index `4`.

---

## Subarray 1

Using virtual prefix:

```txt id="qdog2r"
0...4
```

```txt id="cd6hpy"
1 -1 1 1 1
```

Sum:

```txt id="98odsr"
3
```

---

## Subarray 2

Using prefix at index `1`:

Remove:

```txt id="3u9xvj"
1 -1
```

Remaining:

```txt id="78kyes"
1 1 1
```

indices:

```txt id="cbdepk"
2...4
```

Sum:

```txt id="7tta57"
3
```

So:

```cpp id="vox4i4"
res += 2;
```

---

# Visualization of Removal

Suppose:

```txt id="wp8wke"
currentPrefix = sum(0...i)
previousPrefix = sum(0...j)
```

Then:

sum(0...i)-sum(0...j)=sum(j+1...i)

Subtracting removes the left prefix and leaves the middle subarray.

---

# Approach

1. Maintain running prefix sum.
2. Use hashmap to store frequency of prefix sums.
3. At every index:

   * compute:

prefixSum-k

* if it exists in map, add its frequency to answer

4. Store current prefix sum in hashmap.

---

# Complexity

* Time complexity:

```txt id="gx3jlwm"
O(n)
```

Each element processed once.

---

* Space complexity:

```txt id="x’wini1"
O(n)
```

HashMap may store up to `n` different prefix sums.

---

# Code

```cpp id="y’wini4"
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {

        int prefixSum = 0;
        int res = 0;

        unordered_map<int, int> mapp;

        // virtual prefix before array starts
        mapp[0] = 1;

        for (int& num : nums) {

            prefixSum += num;

            int need = prefixSum - k;

            // if earlier prefix exists,
            // removing it leaves subarray sum k
            if (mapp.count(need)) {
                res += mapp[need];
            }

            // store current prefix frequency
            mapp[prefixSum]++;
        }

        return res;
    }
};
```
