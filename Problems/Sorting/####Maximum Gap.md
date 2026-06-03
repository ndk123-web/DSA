# 164. Maximum Gap

## Intuition

A straightforward approach is:

```cpp
sort(nums.begin(), nums.end());
```

and then compute:

```text
nums[i+1] - nums[i]
```

for all adjacent elements.

However:

```text
Sorting = O(n log n)
```

while the problem requires:

```text
O(n)
```

time.

---

## Key Observation

Suppose:

```text
nums = [1,3,6,9]
```

After sorting:

```text
1 3 6 9
```

Gaps:

```text
2
3
3
```

Maximum Gap:

```text
3
```

---

Let:

```text
min = 1
max = 9
```

Then:

```text
Range = max - min = 8
```

---

After sorting:

```text
1 _ 3 _ 6 _ 9
```

there are:

```text
n - 1 = 3
```

gaps.

---

Notice:

```text
(3-1)
+
(6-3)
+
(9-6)
=
8
```

Therefore:

```text
Range
=
Sum of all adjacent gaps
```

---

## Pigeonhole Principle

We have:

```text
Range = 8
```

distributed among:

```text
3 gaps
```

Average gap:

```text
8 / 3
=
2.67
```

---

Therefore:

```text
At least one gap
must be >= 2.67
```

Otherwise the total range could never reach 8.

This implies:

```text
Maximum Gap
>=
Range / (n-1)
```

---

## Bucket Idea

Since the answer is guaranteed to be at least:

```text
Range / (n-1)
```

we create buckets of approximately that size.

```cpp
bucketSize =
max(1, (max-min)/(n-1));
```

---

### Example

```text
1 3 6 9
```

Range:

```text
8
```

Gaps:

```text
3
```

Bucket Size:

```text
8/3 = 2
```

---

Bucket Count:

```text
8/2 + 1
=
5
```

Buckets:

```text
Bucket0
Bucket1
Bucket2
Bucket3
Bucket4
```

---

## Why Buckets Work

A bucket covers only:

```text
bucketSize
```

worth of range.

Therefore:

```text
Any two numbers
inside the same bucket
have difference < bucketSize
```

---

But we already proved:

```text
Maximum Gap
>= bucketSize
```

---

Therefore:

```text
Maximum Gap
cannot exist inside a bucket.
```

It must occur:

```text
between two buckets.
```

This is the crucial insight.

---

## What Do We Store?

We do **not** store every element.

For each bucket we only store:

```text
bucketMin
bucketMax
```

because:

```text
Internal bucket gaps
can never be the answer.
```

---

## Finding the Answer

For two neighboring non-empty buckets:

```text
Previous Bucket:
[min, max]

Current Bucket:
[min, max]
```

The candidate gap is:

```cpp
currentBucketMin
-
previousBucketMax
```

---

Why?

Because there are no elements between:

```text
previousBucketMax
and
currentBucketMin
```

Otherwise some bucket between them would be non-empty.

Thus this is a real adjacent gap in the sorted order.

---

## Dry Run

### Input

```text
[3,6,9,1]
```

---

### Step 1

```text
min = 1
max = 9
n = 4
```

---

### Step 2

```text
holes = n-1
      = 3
```

---

### Step 3

```text
bucketSize
=
(9-1)/3
=
2
```

---

### Step 4

```text
bucketCount
=
8/2 + 1
=
5
```

---

### Step 5

Insert numbers

```text
1 -> Bucket0

3 -> Bucket1

6 -> Bucket2

9 -> Bucket4
```

---

Stored values:

```text
Bucket0:
min=1 max=1

Bucket1:
min=3 max=3

Bucket2:
min=6 max=6

Bucket3:
empty

Bucket4:
min=9 max=9
```

---

### Step 6

Start:

```text
prevMax = 1
```

---

Bucket1:

```text
3 - 1 = 2
```

```text
ans = 2
```

```text
prevMax = 3
```

---

Bucket2:

```text
6 - 3 = 3
```

```text
ans = 3
```

```text
prevMax = 6
```

---

Bucket4:

```text
9 - 6 = 3
```

```text
ans = 3
```

---

Final Answer:

```text
3
```

---

## Correctness Proof

### Lemma 1

The sum of all adjacent sorted gaps equals:

```text
maxElement - minElement
```

because:

```text
(x₂-x₁)+(x₃-x₂)+...+(xₙ-xₙ₋₁)
=
xₙ-x₁
```

∎

---

### Lemma 2

At least one adjacent gap is greater than or equal to:

```text
(maxElement-minElement)/(n-1)
```

by the pigeonhole principle.

∎

---

### Lemma 3

Any two numbers inside the same bucket differ by less than:

```text
bucketSize
```

∎

---

### Lemma 4

The maximum gap cannot occur inside a bucket.

From Lemma 2:

```text
Maximum Gap >= bucketSize
```

From Lemma 3:

```text
Any internal bucket gap < bucketSize
```

Therefore the maximum gap must occur between buckets.

∎

---

### Theorem

The algorithm returns the maximum adjacent gap of the sorted array.

Since the maximum gap cannot occur inside a bucket, checking:

```cpp
currentBucketMin
-
previousBucketMax
```

for every pair of neighboring non-empty buckets examines every possible location of the maximum gap.

Therefore the largest computed gap is the answer.

∎

---

## Complexity Analysis

### Time Complexity

Finding min/max:

```text
O(n)
```

Bucket insertion:

```text
O(n)
```

Bucket traversal:

```text
O(n)
```

Total:

```text
O(n)
```

---

### Space Complexity

Bucket arrays:

```text
O(n)
```

---

## Final Complexity

```text
Time  : O(n)
Space : O(n)
```

```cpp
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();

        // if n < 2 means no gap is threr
        if (n < 2)
            return 0;

        int minElement = *min_element(nums.begin(), nums.end());
        int maxElement = *max_element(nums.begin(), nums.end());

        if (maxElement - minElement == 0)
            return 0;

        int holes = n - 1; // n = 4 means 3 holes are there

        // bucker range if , (9-1) = 8 then 8/3 = 2.67 approx 3 bucket size
        // range
        int bucketSize = max(1, (maxElement - minElement) / holes);

        // if bucketSize = 3 means 9-1/3 = 8/3 = 2 + 1= 3 buckets requires
        int bucketCount = (maxElement - minElement) / bucketSize + 1;

        vector<int> bucketMax(bucketCount, INT_MIN);
        vector<int> bucketMin(bucketCount, INT_MAX);
        vector<bool> used(bucketCount, false);

        for (int i = 0; i < n; i++) {
            int bucketIndex = (nums[i] - minElement) / bucketSize;

            bucketMax[bucketIndex] = max(bucketMax[bucketIndex], nums[i]);
            bucketMin[bucketIndex] = min(bucketMin[bucketIndex], nums[i]);
            used[bucketIndex] = true;
        }

        int res = INT_MIN;
        int prevMax = minElement;

        for (int i = 0; i < bucketCount; i++) {
            if (!used[i])
                continue;

            res = max(res, (bucketMin[i] - prevMax));
            prevMax = bucketMax[i];
        }

        return res;
    }
};
```