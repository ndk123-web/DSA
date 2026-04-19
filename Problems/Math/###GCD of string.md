# Greatest Common Divisor of Strings

## Intuition

The problem is analogous to finding the greatest common divisor (GCD) of two numbers, but applied to strings.

A valid divisor string `X` must be able to construct both `s` and `t` by repeated concatenation. Before computing anything, we must ensure that both strings share the same repeating pattern.

The condition `s + t == t + s` guarantees that both strings are composed of the same base substring. If this condition fails, no common divisor string exists.

Once the pattern is validated, the length of the largest possible divisor string is the GCD of the lengths of the two strings.

---

## Logic

1. Check if both strings share the same base pattern:

   * If `s + t != t + s`, return an empty string.
2. Compute the GCD of the lengths of `s` and `t`.
3. The result is the prefix of length `gcd(len(s), len(t))`.
4. Return that prefix.

---

## Approach

### Steps

* Validate pattern compatibility using concatenation check.
* Use Euclidean algorithm to compute GCD of lengths.
* Extract substring of that length from either string.

---

## Code

```cpp id="v6clg2"
class Solution {
public:
    
    // Euclidean algorithm to compute gcd of two integers
    int gcd(int a, int b) {
        if (b == 0)
            return a;
        
        return gcd(b, (a % b));
    }

    string gcdOfStrings(string s, string t) {
        string res = "";

        // check if both strings are built from same base pattern
        if (s + t != t + s) 
            return res;

        // compute gcd of lengths
        int idx = gcd(s.size(), t.size());

        // return prefix of gcd length
        return t.substr(0, idx);   
    }
};
```

---

## Complexity Analysis

* Time Complexity: O(n + m)
  Concatenation and comparison take linear time.

* Space Complexity: O(n + m)
  Temporary strings are created during concatenation.

---

## Key Insight

* `s + t == t + s` ensures both strings share a common repeating structure.
* The problem reduces to finding GCD of lengths once structure is validated.
* The prefix of length equal to the GCD gives the largest valid divisor string.

---

## Notes

* Either `s.substr(0, idx)` or `t.substr(0, idx)` works since both share the same base pattern.
* The recursive GCD implementation follows the standard Euclidean algorithm.
* This approach avoids explicitly simulating string division, making it efficient and clean.
