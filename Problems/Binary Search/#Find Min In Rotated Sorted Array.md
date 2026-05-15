# Intuition

In a rotated sorted array, one side of the array is always sorted.

Example:

```txt id="jlwm0w"
4 5 1 2 3
```

Here:

```txt id="pjlwm7"
4 5
```

is sorted and:

```txt id="8jlwmr"
1 2 3
```

is also sorted.

The minimum element always lies near the rotation point.

So during binary search:

* if left side is sorted, then `nums[low]` can be a possible minimum
* otherwise rotation exists on left side and `nums[mid]` can be minimum

We keep shrinking the search space while updating the minimum answer.

---

# Approach

We use Binary Search.

Initialize:

```cpp id="x’wini1"
low = 0
high = n-1
```

At every step:

```cpp id="yjlwm4"
mid = low + (high-low)/2
```

---

## Case 1

```cpp id="0jlwmy"
nums[low] <= nums[mid]
```

This means:

```txt id="7’winin"
left half is sorted
```

So:

```txt id="2’wina5"
nums[low]
```

is the minimum value of that sorted half.

Update answer:

```cpp id="sjlwmo"
res = min(res, nums[low])
```

Since minimum cannot be inside this sorted portion anymore:

```cpp id="q0gqz0"
low = mid + 1
```

---

## Case 2

Otherwise:

```txt id="mwo6rw"
rotation exists in left half
```

and:

```txt id="ahj9pp"
nums[mid]
```

can be minimum.

Update:

```cpp id="uf9yxn"
res = min(res, nums[mid])
```

Then continue searching left half:

```cpp id="rzjdc7"
high = mid
```

---

# Complexity

* Time complexity:

```txt id="7o2qee"
O(log n)
```

Because binary search removes half search space every iteration.

---

* Space complexity:

```txt id="kfigjf"
O(1)
```

No extra space used.

---

# Code

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {

        int low = 0;
        int high = nums.size() - 1;

        if (nums.size() == 1)
            return nums[0];

        int res = 1e9;

        while (low < high) {

            int mid = low + (high - low) / 2;

            // left side sorted
            if (nums[low] <= nums[mid]) {

                res = min(res, nums[low]);

                low = mid + 1;
            }

            // rotation exists in left side
            else {

                res = min(res, nums[mid]);

                high = mid;
            }
        }

        return min(res, nums[low]);
    }
};
```
