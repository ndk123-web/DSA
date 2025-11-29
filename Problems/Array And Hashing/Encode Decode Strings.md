# Encode and Decode Strings
---

## Problem Overview

You need to convert a list of strings into a single encoded string. Later, you should be able to decode that single string back into the original list of strings. The format should be unambiguous and reliable, even when strings contain special characters.

---

# Encoding Logic

The encoding format used is:

```
<length>#<string><length>#<string>...
```

Example:

```
["neet", "code"] → "4#neet4#code"
```

### Why this format?

- The length prefix tells exactly how many characters belong to the string.
- `#` acts as a separator between the number and the string.
- This avoids ambiguity even if the string contains numbers or special characters.

---

# Encode Code

```cpp
string encode(vector<string>& strs) {
    string res;

    // Format: <length>#<string>
    for (const string& s : strs) {
        res = res + to_string(s.size()) + "#" + s;
    }
    return res;
}
```

### How it works

- For each string `s` in the list:

  - Convert length to string using `to_string()`.
  - Append `#`.
  - Append the actual string.

- Concatenate everything into one encoded string.

---

# Decoding Logic

The decoding scans through the encoded string and reconstructs the original list.

### Steps

1. Start from index `i`.
2. Move index `j` forward until you reach `#`.
3. The substring from `i` to `j` (excluded) is the length.
4. Convert it to integer using `stoi()`.
5. Move `i` to the character right after `#`.
6. Extract the next `length` characters.
7. Add the extracted string to the result.
8. Move `i` forward and repeat.

---

# Decode Code

```cpp
vector<string> decode(string s) {
    vector<string> res;
    int i = 0;

    while (i < s.size()) {
        int j = i;
        // Move j until '#'
        while (s[j] != '#') {
            j++;
        }

        // Extract length
        int length = stoi(s.substr(i, j - i));

        // Move i to first char of the string
        i = j + 1;

        // Extract the string of `length` characters
        res.push_back(s.substr(i, length));

        // Move i to next segment
        i = i + length;
    }

    return res;
}
```

---

# Example Walkthrough

Encoded string:

```
4#neet4#code
```

Decoding:

- Start: i = 0
- Move j until '#': substring = "4" → length = 4
- Extract next 4 chars → "neet"
- Move forward
- Again find next length → "4"
- Extract next 4 chars → "code"

Output:

```
["neet", "code"]
```

---

# Time Complexity

- Encoding: O(total characters)
- Decoding: O(total characters)

# Space Complexity

- Encoding output: O(total characters)
- Decoding array: O(total characters)

---
