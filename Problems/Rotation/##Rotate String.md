## Rotate String

### Intuition

A string rotation means:

* take the first character
* move it to the end

Example:

```text id="jlwm21"
abcde → bcdea
```

We repeatedly rotate the string and check whether it becomes equal to `goal`.

Since a string of length `n` returns to its original form after `n` rotations, we only need to try at most `n - 1` shifts (excluding the original string check).

---

### Approach

#### Step 1: Handle Direct Match

If:

```cpp id="jlwm22"
s == goal
```

return `true`.

---

#### Step 2: Left Shift the String

For one rotation:

```text id="jlwm23"
abcde → bcdea
```

Process:

* store first character
* shift remaining characters left
* place stored character at the end

---

#### Step 3: Try All Rotations

Repeat shifting and compare with `goal`.

If any rotation matches:

```cpp id="jlwm24"
return true;
```

Otherwise:

```cpp id="jlwm25"
return false;
```

---

### Code

```cpp id="jlwm26"
class Solution {
public:
    // left shift
    void shiftS(string& s) {
        int n = s.size();

        char t = s[0];

        for (int i = 0; i < n - 1; i++) {
            s[i] = s[i + 1];
        }

        s[n - 1] = t;
    }

    bool rotateString(string s, string goal) {
        int n = s.size();

        int k = n - 1;

        if (s == goal)
            return true;

        for (int i = 0; i < k; i++) {
            shiftS(s);

            if (s == goal)
                return true;
        }

        return false;
    }
};
```

---

### Dry Run

Input:

```text id="jlwm27"
s = "abcde"
goal = "cdeab"
```

---

### Initial

```text id="jlwm28"
abcde != cdeab
```

---

### Rotation 1

```text id="jlwm29"
bcdea
```

Not equal.

---

### Rotation 2

```text id="jlwm30"
cdeab
```

Equal:

```text id="jlwm31"
return true
```

---

### Complexity

#### Time

Each rotation:

```text id="jlwm32"
O(n)
```

Total rotations:

```text id="jlwm33"
O(n)
```

Overall:

```text id="jlwm34"
O(n²)
```

---

#### Space

```text id="jlwm35"
O(1)
```

---

### Key Insight

A valid rotated string must appear after repeatedly shifting characters.

The solution directly simulates rotation instead of using advanced string tricks.

---

### Optimization Insight

A more optimal solution exists using string concatenation:

```cpp id="jlwm36"
(s + s).find(goal) != string::npos
```

Reason:

* every possible rotation of `s`
  exists inside `s + s`

This reduces implementation complexity and runs in:

```text id="jlwm37"
O(n)
```