    # Intuition

A brute force solution would generate every subarray and compute its minimum.

However, this becomes too slow because:

* total subarrays = (O(n^2))
* finding minimum for each subarray can take (O(n))

Overall complexity becomes:

```text
O(n³)
```

Instead of generating all subarrays, we can think differently:

> For every element `arr[i]`, calculate:
>
> * in how many subarrays it becomes the minimum
> * then add its total contribution directly

If an element appears as the minimum in `k` subarrays, then its contribution becomes:

arr[i] \times k

To find `k`, we compute:

* Previous Smaller Element (PSE)
* Next Smaller Element (NSE)

using a monotonic increasing stack.

---

# Approach

For every element `arr[i]`:

* `pse[i]` → index of previous smaller element
* `nse[i]` → index of next smaller element

Then:

* possible left boundaries:

i - pse[i]

* possible right boundaries:

nse[i] - i

Thus total subarrays where `arr[i]` is the minimum:

(i-pse[i]) \times (nse[i]-i)

Contribution of current element:

arr[i] \times (i-pse[i]) \times (nse[i]-i)

We sum contributions for all elements.

---

# Duplicate Handling

For duplicate values, we must avoid double counting.

So:

* NSE uses `>=`
* PSE uses `>`

This ensures equal elements are counted consistently only once.

Example:

```text
[5,9,5]
```

The subarray `[5,9,5]` should belong to only one `5`.

---

# Complexity

* Time complexity:

```text
O(n)
```

Each element is pushed and popped from the stack at most once.

---

* Space complexity:

```text
O(n)
```

For:

* stack
* NSE array
* PSE array

---

# Code

```cpp
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {

        int n = arr.size();

        int nse[n];
        int pse[n];

        // default:
        // no next smaller element
        for (int i = 0; i < n; i++) {
            nse[i] = n;
        }

        // default:
        // no previous smaller element
        for (int i = 0; i < n; i++) {
            pse[i] = -1;
        }

        stack<int> st;

        // Next Smaller Element
        for (int i = 0; i < n; i++) {

            // >= for duplicate handling
            while (!st.empty() &&
                   arr[st.top()] >= arr[i]) {

                nse[st.top()] = i;

                st.pop();
            }

            st.push(i);
        }

        st = stack<int>();

        // Previous Smaller Element
        for (int i = n - 1; i >= 0; i--) {

            // > for duplicate handling
            while (!st.empty() &&
                   arr[st.top()] > arr[i]) {

                pse[st.top()] = i;

                st.pop();
            }

            st.push(i);
        }

        long long sum = 0;

        int MOD = 1e9 + 7;

        for (int i = 0; i < n; i++) {

            long long left =
                i - pse[i];

            long long right =
                nse[i] - i;

            long long contribution =
                left * right * arr[i];

            sum =
                (sum + contribution) % MOD;
        }

        return sum;
    }
};
```
