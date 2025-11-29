
---

# **Sort Colors — Merge Sort Approach (C++ In-Place Indices)**

### **Problem**

You are given an array `nums` containing only:

```
0 → Red
1 → White
2 → Blue
```

Sort the array in **non-decreasing order**.

---

# **Approach: Merge Sort (In-Place Range Based)**

This is a full **divide & conquer** merge sort using:

* `merge(nums, l, m, r)` → merges two sorted halves (`[l..m]` and `[m+1..r]`)
* `mergeSort(nums, l, r)` → recursively sorts the array
* Entire sorting is **in-place index based** (no copying input vectors)
* Temporary vector only for merging between `l..r`

---

# **Why Merge Sort?**

Although Sort Colors can be solved using counting or 3-pointer Dutch flag method in `O(n)` time,
merge sort shows:

* clean divide and conquer logic
* stable merging
* index-based in-place sort
* classic interview-style implementation

---

# **How It Works**

### **Divide Step**

Split array into two halves:

```
Left  = [l .. m]
Right = [m+1 .. r]
```

### **Conquer Step**

Sort left half and right half recursively.

### **Merge Step**

Merge two sorted halves into a temporary array,
then copy the sorted values back into `nums[l..r]`.

---

# **Code (Clean + Short Comments)**

```cpp
class Solution {
public:

    // Merge two sorted halves: [l..m] and [m+1..r]
    void merge(vector<int>& nums, int l, int m, int r) {
        vector<int> temp;
        int i = l, j = m + 1;

        // merge both halves
        while (i <= m && j <= r) {
            if (nums[i] <= nums[j])
                temp.push_back(nums[i++]);
            else
                temp.push_back(nums[j++]);
        }

        // remaining left part
        while (i <= m)
            temp.push_back(nums[i++]);

        // remaining right part
        while (j <= r)
            temp.push_back(nums[j++]);

        // copy merged result back to nums
        for (i = l; i <= r; i++)
            nums[i] = temp[i - l];
    }

    // Recursive merge sort over range [l..r]
    void mergeSort(vector<int>& nums, int l, int r) {
        if (l >= r)
            return;

        int m = (l + r) / 2;

        mergeSort(nums, l, m);      // sort left half
        mergeSort(nums, m + 1, r);  // sort right half
        merge(nums, l, m, r);       // merge both halves
    }

    void sortColors(vector<int>& nums) {
        mergeSort(nums, 0, nums.size() - 1);
    }
};
```

---

# **Example**

Input:

```
[2,0,2,1,1,0]
```

After merge sort:

```
[0,0,1,1,2,2]
```

---

# **Complexity**

| Step         | Time           | Space           |
| ------------ | -------------- | --------------- |
| Merge Sort   | **O(n log n)** | O(n) temp space |
| sortColors() | O(n log n)     | O(n)            |

---

# **Note**

This method is correct and clean,
but not the optimal solution for Sort Colors (which can be done in O(n) using Dutch Flag Algorithm).

However, for demonstrating **perfect merge sort logic**,
this implementation is excellent.

---
