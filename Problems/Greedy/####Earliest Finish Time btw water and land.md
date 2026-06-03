# 3633. Earliest Finish Time for Land and Water Rides II

## Intuition

A tourist must take:

* Exactly **one land ride**
* Exactly **one water ride**

and can choose either order:

```text
Land -> Water
```

or

```text
Water -> Land
```

A straightforward approach would try every pair of rides:

```text
Land[i] with Water[j]
```

which leads to:

```text
O(n * m)
```

However, we can do better.

---

## Key Observation

For the order:

```text
Land -> Water
```

the finish time is:

```text
max(landFinish, waterStart) + waterDuration
```

where:

```text
landFinish = landStart + landDuration
```

For a fixed water ride, the only information we need from all land rides is:

```text
minimum possible landFinish
```

because:

```text
max(landFinish, waterStart)
```

is minimized when `landFinish` is minimized.

Therefore, instead of checking every land ride, we only need:

```text
minLandFinish
```

---

Similarly, for:

```text
Water -> Land
```

we only need:

```text
minWaterFinish
```

where:

```text
waterFinish = waterStart + waterDuration
```

---

## Greedy Insight

Let:

```text
minLandFinish
=
minimum(landStart[i] + landDuration[i])
```

and

```text
minWaterFinish
=
minimum(waterStart[j] + waterDuration[j])
```

Then:

### Land → Water

For every water ride:

```text
finish =
max(minLandFinish, waterStart[j])
+
waterDuration[j]
```

---

### Water → Land

For every land ride:

```text
finish =
max(minWaterFinish, landStart[i])
+
landDuration[i]
```

The minimum among all such values is the answer.

---

## Why does this work?

Suppose we are evaluating a particular water ride.

The finish time is:

```text
max(landFinish, waterStart)
+
waterDuration
```

The water ride is fixed.

To minimize the expression, we should choose the smallest possible:

```text
landFinish
```

Therefore only the globally minimum land finish time matters.

The same argument applies symmetrically for:

```text
Water -> Land
```

---

## Algorithm

### Step 1

Compute:

```text
minLandFinish
=
min(landStart[i] + landDuration[i])
```

---

### Step 2

For every water ride:

```text
candidate =
max(minLandFinish, waterStart[i])
+
waterDuration[i]
```

Update answer.

Also compute:

```text
minWaterFinish
=
min(waterStart[i] + waterDuration[i])
```

---

### Step 3

For every land ride:

```text
candidate =
max(minWaterFinish, landStart[i])
+
landDuration[i]
```

Update answer.

---

## Dry Run

### Input

```text
landStartTime = [2,8]
landDuration  = [4,1]

waterStartTime = [6]
waterDuration  = [3]
```

---

### Compute minimum land finish

```text
Land 0:
2 + 4 = 6

Land 1:
8 + 1 = 9
```

Therefore:

```text
minLandFinish = 6
```

---

### Land → Water

Water ride:

```text
start = 6
duration = 3
```

Finish time:

```text
max(6,6) + 3
=
9
```

---

### Compute minimum water finish

```text
6 + 3
=
9
```

Therefore:

```text
minWaterFinish = 9
```

---

### Water → Land

Land 0:

```text
max(9,2) + 4
=
13
```

Land 1:

```text
max(9,8) + 1
=
10
```

---

Minimum:

```text
min(9,13,10)
=
9
```

Answer:

```text
9
```

---

## Correctness Proof

We prove that the algorithm returns the earliest possible finish time.

### Lemma 1

For any fixed water ride, the optimal land ride is the one with the minimum land finish time.

**Proof**

The finish time for:

```text
Land -> Water
```

is:

```text
max(landFinish, waterStart)
+
waterDuration
```

Since the water ride is fixed, minimizing `landFinish` minimizes the entire expression.

Therefore only the minimum land finish time needs to be considered.

∎

---

### Lemma 2

For any fixed land ride, the optimal water ride is the one with the minimum water finish time.

By symmetric reasoning.

∎

---

### Theorem

The algorithm considers the optimal completion time for both possible ride orders.

From Lemma 1, every optimal:

```text
Land -> Water
```

schedule is examined.

From Lemma 2, every optimal:

```text
Water -> Land
```

schedule is examined.

Therefore the minimum value produced by the algorithm is the globally optimal finish time.

∎

---

## Complexity Analysis

Let:

```text
n = number of land rides
m = number of water rides
```

### Time Complexity

```text
O(n)
+
O(m)
+
O(n)
=
O(n + m)
```

---

### Space Complexity

```text
O(1)
```

Only a few variables are used.

---

## Reference Implementation

```cpp
class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime,
                           vector<int>& landDuration,
                           vector<int>& waterStartTime,
                           vector<int>& waterDuration) {

        long long minL = LLONG_MAX;
        long long minW = LLONG_MAX;
        long long ans = LLONG_MAX;

        for (int i = 0; i < landStartTime.size(); i++) {
            minL = min(minL,
                       1LL * landStartTime[i] + landDuration[i]);
        }

        for (int i = 0; i < waterStartTime.size(); i++) {
            minW = min(minW,
                       1LL * waterStartTime[i] + waterDuration[i]);

            ans = min(ans,
                      max(minL, 1LL * waterStartTime[i]) +
                      waterDuration[i]);
        }

        for (int i = 0; i < landStartTime.size(); i++) {
            ans = min(ans,
                      max(minW, 1LL * landStartTime[i]) +
                      landDuration[i]);
        }

        return (int)ans;
    }
};
```
