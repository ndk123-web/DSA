# Candy Distribution

## Problem

There are `n` children standing in a line. Each child is assigned a rating value.

You must distribute candies such that:

1. Each child gets at least one candy.
2. A child with a higher rating than an adjacent neighbor gets more candies than that neighbor.

Return the minimum number of candies required.

---

## Intuition

This is a **constraint satisfaction problem** where each child must satisfy conditions relative to both neighbors.

* If `ratings[i] > ratings[i-1]`, then `candies[i] > candies[i-1]`
* If `ratings[i] > ratings[i+1]`, then `candies[i] > candies[i+1]`

These constraints act independently from the left and right sides.

---

## Key Idea

We process the array in two passes:

### 1. Left to Right (L array)

Ensures:

```
ratings[i] > ratings[i-1] ⇒ candies[i] = candies[i-1] + 1
```

This pass satisfies all **left neighbor constraints**.

---

### 2. Right to Left (R array)

Ensures:

```
ratings[i] > ratings[i+1] ⇒ candies[i] = candies[i+1] + 1
```

This pass satisfies all **right neighbor constraints**.

---

## Why take max(L[i], R[i])?

At index `i`:

* `L[i]` = minimum candies required to satisfy left constraint
* `R[i]` = minimum candies required to satisfy right constraint

To satisfy both:

```
candies[i] ≥ L[i]
candies[i] ≥ R[i]
```

Therefore:

```
candies[i] = max(L[i], R[i])
```

This ensures:

* All constraints are satisfied
* Total candies are minimized

---

## Example

### Input

```
ratings = [1,2,3,2,1]
```

### Left pass

```
L = [1,2,3,1,1]
```

### Right pass

```
R = [1,1,3,2,1]
```

### Final

```
max(L,R) = [1,2,3,2,1]
```

### Output

```
1 + 2 + 3 + 2 + 1 = 9
```

---

## Complexity

* Time: `O(n)`
* Space: `O(n)` (can be optimized to `O(1)`)

---

## Key Takeaway

Each pass enforces one directional constraint.
The final answer is the minimum value that satisfies both, obtained by taking the maximum at each index.
