# 204. Count Primes

## Intuition

A brute force approach would be:

```cpp
for(int i = 2; i < n; i++) {
    check if i is prime;
}
```

For each number we perform a prime check up to:

```text
sqrt(i)
```

This leads to a large amount of repeated work.

---

### Key Observation

If a number is prime:

```text
2
```

then all of its multiples:

```text
4, 6, 8, 10, 12, ...
```

are definitely not prime.

Instead of checking every number individually, we can eliminate many composite numbers at once.

This idea leads to the **Sieve of Eratosthenes**.

---

## Approach

Create a boolean array:

```cpp
vector<bool> primes(n, true);
```

Initially assume every number is prime.

---

Mark:

```text
0 → not prime
1 → not prime
```

---

Now iterate through the numbers.

If a number is still marked as prime:

```text
2
```

then it is a genuine prime.

Mark all of its multiples as composite:

```text
4
6
8
10
...
```

---

Example:

### n = 10

Initially:

```text
Index:
0 1 2 3 4 5 6 7 8 9

Prime:
F F T T T T T T T T
```

---

Process:

```text
2
```

Mark:

```text
4 6 8
```

Result:

```text
F F T T F T F T F T
```

---

Process:

```text
3
```

Mark:

```text
6 9
```

Result:

```text
F F T T F T F T F F
```

---

Process:

```text
4
```

Already marked composite.

Skip.

---

Remaining primes:

```text
2 3 5 7
```

Count:

```text
4
```

---

## Algorithm

1. Create a boolean array of size `n`.
2. Mark every number as prime.
3. Set:

   ```cpp
   primes[0] = false;
   primes[1] = false;
   ```
4. For every prime number:

   * Mark all of its multiples as composite.
5. Count the remaining prime numbers.

---

## Code

```cpp
class Solution {
public:
    int countPrimes(int n) {

        if (n <= 2)
            return 0;

        vector<bool> primes(n, true);

        primes[0] = false;
        primes[1] = false;

        for (int i = 2; i < n; i++) {

            if (!primes[i])
                continue;

            for (int j = i * 2; j < n; j += i) {
                primes[j] = false;
            }
        }

        int res = 0;

        for (int i = 2; i < n; i++) {
            if (primes[i])
                res++;
        }

        return res;
    }
};
```

---

## Optimization

Instead of:

```cpp
for(int i = 2; i < n; i++)
```

we only need:

```cpp
for(int i = 2; i * i < n; i++)
```

because any composite number greater than `√n` must have already been marked by a smaller factor.

---

Similarly, instead of:

```cpp
j = i * 2
```

we can start from:

```cpp
j = i * i
```

because smaller multiples have already been processed by smaller primes.

Optimized version:

```cpp
for (int i = 2; i * i < n; i++) {

    if (!primes[i])
        continue;

    for (int j = i * i; j < n; j += i) {
        primes[j] = false;
    }
}
```

---

## Correctness Proof

### Lemma 1

Every composite number is marked as non-prime.

A composite number `x` can be written as:

```text
x = a × b
```

where:

```text
2 ≤ a ≤ √x
```

When processing factor `a`, all multiples of `a`, including `x`, are marked as composite.

Therefore every composite number is marked.

---

### Lemma 2

No prime number is marked as composite.

The algorithm only marks multiples of smaller numbers.

A prime number has no divisor other than:

```text
1 and itself
```

Therefore it is never marked.

---

### Theorem

After the sieve finishes:

```text
primes[i] == true
```

if and only if `i` is prime.

Thus counting all remaining `true` values gives the correct answer.

---

## Complexity Analysis

### Your Version

For each prime:

```cpp
j = i * 2
```

Time:

```text
O(n log log n)
```

Space:

```text
O(n)
```

---

### Optimized Sieve

Using:

```cpp
i * i < n
j = i * i
```

Time:

```text
O(n log log n)
```

Space:

```text
O(n)
```

---

## Pattern Recognition

Whenever you see:

```text
Count all primes ≤ N
Generate all primes ≤ N
Prime queries on a range
```

Think:

```text
Sieve of Eratosthenes
```

Just like:

```text
Range Sum           → Prefix Sum
Many Updates        → Segment Tree
Count Primes ≤ N    → Sieve of Eratosthenes
```

This is one of the most important precomputation techniques in DSA. 🔥

```cpp
class Solution {
public:
    int countPrimes(int n) {

        if (n <= 2)
            return 0;

        vector<bool> primes(n, true);
        /*
            n = 10
            f f t t f t f t f f
            0 1 2 3 4 5 6 7 8 9
        */
        int res = 0;
        primes[0] = false;
        primes[1] = false;

        for (int i = 2; i < n; i++) {
            if (primes[i] == false)
                continue;

            for (int j = i * 2; j < n; j = j + i) {
                primes[j] = false;
            }
        }

        for (int i = 2; i < n; i++) {
            if (primes[i])
                res++;
        }

        return res;
    }
};
```