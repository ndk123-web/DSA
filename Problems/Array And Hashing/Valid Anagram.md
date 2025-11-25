***

# Valid Anagram

Given two strings, `s` and `t`, return **true** if `t` is an anagram of `s` (i.e., both contain the same characters with the same frequency), otherwise return **false**.

***

## 1. Why (Intuition)

This question tests:

- Grasp of **hashing** and frequency counting for strings.
- Knowledge of **efficient string comparison** and matching.
- Comfort with sorting as a universal comparison trick.
- Awareness of **time-space tradeoffs** in frequency-based algorithms.

Goal → check whether two strings hold the same multiset of characters.

***

## 2. Problem Breakdown

### Input

- Two strings `s` and `t`, both containing only lowercase letters.
- Lengths can vary; may be large.

### Output

- `true` if `t` is an anagram of `s`.
- `false` if not.

### Edge Cases

- Strings of different lengths → always `false`.
- Empty strings are anagrams of each other.
- Strings with repeated characters.

***

## 3. Brute Force — Sorting Approach

### Idea

Sort both strings; anagrams have identical sorted forms.

### Steps

1. Check lengths: If `s.size() != t.size()`, return `false`.
2. Sort both `s` and `t`.
3. Compare sorted strings.

### Dry Run

```
s = "rat"
t = "tar"
sorted(s) = "art"
sorted(t) = "art"
Strings match → return true
```

### Complexity

- **Time:** O(n log n)
- **Space:** O(1) extra (can be in-place)

### Code

```cpp
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
}
```

***

## 4. Optimal Approach — Hashing (Counting Frequency)

### Approach A — Using `unordered_map`

- Count character frequency for both strings.
- Compare frequency maps for every character.

#### Steps

1. If `s.size() != t.size()`, return `false`.
2. Build maps for `s` and `t`.
3. Compare frequency of all characters.

### Dry Run

```
s = "cat"
t = "tac"
sMap: {'c':1,'a':1,'t':1}
tMap: {'t':1,'a':1,'c':1}
Maps match → return true
```

### Complexity

- **Time:** O(n)
- **Space:** O(n)

### Code

```cpp
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    unordered_map<char, int> sMap, tMap;
    for (auto ch : s) sMap[ch]++;
    for (auto ch : t) tMap[ch]++;
    for (auto ch : t)
        if (tMap[ch] != sMap[ch]) return false;
    return true;
}
```

***

## 5. Examples

```bash
- Example 1

Input:
s = "listen", t = "silent"
Output:
true
Explanation: "listen" and "silent" contain same characters.

- Example 2

Input:
s = "hello", t = "world"
Output:
false

- Example 3

Input:
s = "aabb", t = "abab"
Output:
true
```

***

## 6. Final Complexity Comparison

| Approach         | Time     | Space   | Notes                |
|------------------|----------|---------|----------------------|
| Sorting          | O(n log n)| O(1)    | Fast, in-place       |
| HashMap counting | O(n)     | O(n)    | Best for large n     |

***

## 7. Notes

- Sorting is very practical for short strings.
- Hashing is fastest for very large strings and supports any alphabet.
- No need to track order—only counts matter.
- For limited alphabet (e.g., lowercase a-z), frequency array is also possible (faster, not shown).

***