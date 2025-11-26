---

# Group Anagrams

Given an array of strings `strs`, group the anagrams together. You can return the hashMapwer in any order.

---

## 1. Why (Intuition)

This problem checks:

- Understanding of what an anagram is: same characters, same frequencies, different order.
- Ability to design a good “key” that uniquely represents an anagram group.
- Use of hash maps to efficiently group related items.

Goal → For each string, compute a unique key that is identical for all its anagrams and use that key to group them.

---

## 2. Problem Breakdown

### Input

- `strs`: vector of strings, length `m`.
- Let `n` be the average length of each string.

### Output

- `vector<vector<string>>` where each inner vector contains strings that are anagrams of each other.
- Order of groups and order inside each group does not matter.

### Edge Cases

- Empty input → return empty `vector<vector<string>>`.
- Single string → one group with that string.
- Strings with no anagrams → each one becomes its own group.

---

## 3. Approach 1 — Sort Each String (O(m · n log n))

You already implemented this.

### Idea

- Sort each string; all anagrams share the same sorted version (signature).
- Use the sorted string as the key in an unordered_map.
- Group original strings under that key.[3][1]

### Steps

1. Create `unordered_map<string, vector<string>> mapp`.
2. For each string `str`:
   - Store original `t = str`.
   - Sort `str`.
   - Push original `t` into `mapp[sorted_str]`.
3. Collect all map values into `result` and return.

### Code

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        unordered_map<string, vector<string>> mapp;

        for (auto& str : strs) {

            string t = str;              // store original
            sort(str.begin(), str.end()); // sort to get key

            mapp[str].push_back(t);      // group by sorted key
        }

        vector<vector<string>> result;
        for (auto& pair : mapp) {
            result.push_back(move(pair.second));
        }

        return result;
    }
};
```

### Complexity

- Let:
  - `m` = number of strings.
  - `n` = average length of each string.
- For each string:
  - Sorting cost: O(n log n).
- Total time: O(m · n log n).[5][1]
- Extra space: O(m · n) to store groups (output) plus map overhead.[1]

So yes, this one is effectively O(m · n log n).

---

## 4. Approach 2 — Frequency-Count Key (O(m · n))

You also implemented the optimized version.

### Idea

- Instead of sorting, build a 26-length frequency array for each string (assuming lowercase a–z).
- Convert that frequency array into a string key (e.g., `"1#0#0#..."`).
- All anagrams will produce the same frequency pattern.[3][1]

### Steps

1. Create `unordered_map<string, vector<string>> hashMap`.
2. For each string `str`:
   - Create `array<int,26> count = {0}`.
   - Count characters: `count[c - 'a']++`.
   - Build key string by concatenating counts with a separator like `'#'`.
   - Push `str` into `hashMap[key]`.
3. Move all map values into `result` and return.

### Code

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        unordered_map<string,vector<string>> hashMap; // hashmap

        for (string &str : strs) {
            array<int,26> count = {0}; // count key for hashMap as a key

            for (char c : str) {      // count the frequence for anagrams
                count[c - 'a']++;
            }

            string key;
            for (int num : count) {         // convert each number into string with # for uniqueness
                key += to_string(num) + "#";
            }

            hashMap[key].push_back(str);    // finally put it inside hashMap
        }

        vector<vector<string>> result;
        for (auto &entry : hashMap) {   // it returns pair so make sure to append pair.second
            result.push_back(move(entry.second));
        }

        return result;
    }
};
```

### Complexity

- For each string:
  - Counting characters: O(n).
  - Building key from 26 counts: O(26) ≈ O(1).
- Total time: O(m · n).[5][1]
- Space: O(m · n) for stored strings + O(m) keys; 26-int array is reused per loop.[1]

So this approach is O(m · n).

---

## 5. Final Complexity Summary

- Sorting-based key:
  - Time: O(m · n log n).
  - Space: O(m · n).
- Frequency-array key:
  - Time: O(m · n).
  - Space: O(m · n).

For large strings, the counting/frequency method is generally more optimal than sorting-based grouping
