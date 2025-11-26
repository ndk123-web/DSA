***

# Longest Common Prefix

Given an array of strings `strs`, find the longest common prefix string among them. If there is no common prefix, return an empty string `""`.

***

## 1. Why (Intuition)

This problem checks:

- String scanning basics, prefix logic, and boundaries.
- Understanding of how sorting simplifies global string relation questions.
- Clean, efficient algorithms versus character-by-character comparisons.

Goal → Find the maximum-length substring starting from the first character that appears at the start of every string.

***

## 2. Problem Breakdown

### Input

- Array `strs` of `n` strings (can be empty strings or very short/long values).

### Output

- The longest string that is a prefix of **every** string in the array.
- Return `""` if no such prefix exists.

### Edge Cases

- Empty array → return `""`.
- Single string → return the string itself.
- No common prefix at all → return `""`.
- Very short array or strings, e.g., ["a"], ["ab","ac"].

***

## 3. Sorting Approach (Efficient)

### Idea

Sorting places the "most different" strings lexicographically first and last. The common prefix of these two is the answer for the whole array.

### Steps

1. Sort the array of strings.
2. Compare the first and last string, character-by-character.
3. The substring where they are identical (from index 0 to mismatch) is the result.

### Dry Run

```
strs = ["flower","flow","flight"]
sort → ["flight","flow","flower"]
strFirst = "flight", strLast = "flower"
Compare: 'f' == 'f', 'l' == 'l'
Mismatch at position 2 → "fl" is result.
```

### Complexity

- **Time:** O(n·k·log n + k), where $$k$$ is the average string length, due to sorting and single scan.
- **Space:** O(1) extra (if sort is in-place).

### Code

```cpp
string longestCommonPrefix(vector<string>& strs) {
    int idx = 0;
    int n = strs.size();
    if (n == 0) return "";
    sort(strs.begin(), strs.end());
    string strFirst = strs[0];
    string strLast = strs[n - 1];
    while (idx < strFirst.size() && idx < strLast.size()) {
        if (strFirst[idx] == strLast[idx]) idx++;
        else break;
    }
    return strFirst.substr(0, idx);
}
```

***

## 4. Examples

```bash
- Example 1

Input:
["flower","flow","flight"]
Output:
"fl"

- Example 2

Input:
["dog","racecar","car"]
Output:
""

- Example 3

Input:
["apple","applepie","applesauce"]
Output:
"apple"
```

***

## 5. Notes

- Sorting-based trick limits comparisons to only two strings, making the code clean and fast.
- Direct character-by-character scan works for non-sorted lists but is less efficient for large n.
- Always check for empty input or edge cases.
- Prefix must be continuously shared from index 0 for all strings.

***

This structure makes the intuition, logic, core code, and gotchas clear for interviews or review.