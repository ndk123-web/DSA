## Rotating the Box

### Intuition

After rotating the box 90° clockwise:

* gravity acts downward in the rotated matrix
* which is equivalent to stones falling to the **right** before rotation

So instead of rotating first and simulating gravity later:

1. simulate gravity toward the right
2. rotate the matrix clockwise

This simplifies the problem significantly.

---

### Approach

#### Step 1: Simulate Gravity to the Right

For each row:

* maintain an `empty` pointer representing the rightmost available position
* traverse from right → left

Rules:

* `*` (obstacle)

  * stones cannot cross it
  * reset `empty = j - 1`

* `#` (stone)

  * move it directly to `empty`
  * decrement `empty`

* `.` (empty)

  * ignore

This ensures every stone lands at its final valid position in O(n).

---

#### Step 2: Rotate the Matrix

For clockwise rotation:

```cpp id="mgq6ba"
res[j][r - 1 - i] = grid[i][j];
```

Mapping logic:

* old column becomes new row
* old row becomes reversed column

---

### Code

```cpp id="3vhgkn"
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& grid) {
        int r = grid.size();
        int c = grid[0].size();

        vector<vector<char>> res(c, vector<char>(r, '.'));

        // simulate gravity toward right
        for (int i = 0; i < r; i++) {
            int empty = c - 1;

            for (int j = c - 1; j >= 0; j--) {

                if (grid[i][j] == '*') {
                    empty = j - 1;
                }

                else if (grid[i][j] == '#') {
                    swap(grid[i][j], grid[i][empty]);
                    empty--;
                }
            }
        }

        // rotate clockwise
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {

                res[j][r - 1 - i] = grid[i][j];
            }
        }

        return res;
    }
};
```

---

### Dry Run

Input:

```text id="8w69w0"
# . * .
# # * .
```

---

### Step 1: Gravity to Right

Row 0:

```text id="t9srf6"
# . * .
→ . # * .
```

Row 1:

```text id="n9uqp0"
# # * .
→ # # * .
```

Matrix becomes:

```text id="u7n7x5"
. # * .
# # * .
```

---

### Step 2: Rotate Clockwise

Using:

```cpp id="k8x8je"
res[j][r - 1 - i] = grid[i][j];
```

Final:

```text id="3ls63k"
# .
# #
* *
. .
```

---

### Complexity

#### Time

* Gravity simulation: O(r × c)
* Rotation: O(r × c)

Total:

```text id="3dpc61"
O(r × c)
```

---

#### Space

```text id="a5kh4q"
O(r × c)
```

for the rotated matrix.

---

### Key Insights

#### 1. Gravity Simplification

Instead of thinking:

```text id="1sksh8"
rotate first → stones fall downward
```

Think:

```text id="p3wltu"
stones fall right first → then rotate
```

---

#### 2. Efficient Simulation

Do not move stones step-by-step.

Track:

```text id="n8j0qo"
rightmost available position
```

and place stones directly there.

---

#### 3. Clockwise Rotation Mapping

```cpp id="jlwmkl"
res[j][r - 1 - i] = grid[i][j];
```

means:

* columns become rows
* rows get reversed after rotation
