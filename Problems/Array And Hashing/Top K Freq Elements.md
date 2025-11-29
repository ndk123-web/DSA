# Top K Frequent Elements — Three Approaches
---

## 1. Min-Heap Approach

### Code

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freqMap; // frequency map

        for (auto& num : nums) {
            freqMap[num]++;
        }

        // min heap storing (frequency, number)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;

        for (const auto& p : freqMap) {
            heap.push({p.second, p.first});
            if (heap.size() > k) {
                heap.pop(); // removes smallest frequency
            }
        }

        vector<int> res;
        for (int i = 0; i < k; i++) {
            res.push_back(heap.top().second);
            heap.pop();
        }

        return res;
    }
};
```

### Time Complexity

* Building frequency map: **O(n)**
* Heap push/pop for each unique element: **O(m log k)** (m = number of unique numbers)
* Final extraction: **O(k log k)**

Overall: **O(n log k)**

### Space Complexity

* Frequency map: **O(m)**
* Heap of size k: **O(k)**

Overall: **O(m)**

### Reason

A min-heap of size k keeps only the top k highest frequency elements. Any element with lower frequency is removed immediately.

---

## 2. Bucket Sort Approach

### Code

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> freqMap;
        vector<int> res;

        // max possible frequency = nums.size()
        vector<vector<int>> buckets(nums.size() + 1);

        for (auto& num : nums) {
            freqMap[num]++;
        }

        // group numbers by frequency
        for (auto& p : freqMap) {
            buckets[p.second].push_back(p.first);
        }

        // gather results from high frequency to low
        for (int i = buckets.size() - 1; i > 0; i--) {
            for (int n : buckets[i]) {
                res.push_back(n);
                if (res.size() == k) return res;
            }
        }

        return res;
    }
};
```

### Time Complexity

* Frequency map: **O(n)**
* Bucket construction: **O(m)**
* Collecting top k: **O(n)** in worst case

Overall: **O(n)**

### Space Complexity

* Frequency map: **O(m)**
* Buckets: **O(n)**

Overall: **O(n)**

### Reason

Bucket sort groups numbers by their frequency. Since maximum frequency is bounded by n, scanning from highest frequency downwards gives top k elements efficiently.

---

## 3. Sorting Pairs Approach

### Code

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> freqMap;

        for (auto& num : nums) {
            freqMap[num]++;
        }

        vector<pair<int,int>> arr; // (frequency, number)
        for (const auto& p : freqMap) {
            arr.push_back({p.second, p.first});
        }

        // sort in descending order by frequency
        sort(arr.rbegin(), arr.rend());

        vector<int> result;
        for (int i = 0; i < k; i++) {
            result.push_back(arr[i].second);
        }

        return result;
    }
};
```

### Time Complexity

* Frequency map: **O(n)**
* Sorting m unique elements: **O(m log m)**
* Extracting top k: **O(k)**

Overall: **O(n + m log m)**

### Space Complexity

* Frequency map: **O(m)**
* Array of pairs: **O(m)**

Overall: **O(m)**

### Reason

Convert frequency map into a vector of pairs and sort them in descending order by frequency. The first k elements after sorting are the required top k frequent elements.

---

# Summary Table

| Method      | Time Complexity | Space Complexity | Notes                 |
| ----------- | --------------- | ---------------- | --------------------- |
| Min-Heap    | O(n log k)      | O(m)             | Good when k is small  |
| Bucket Sort | O(n)            | O(n)             | Fastest overall       |
| Sorting     | O(n + m log m)  | O(m)             | Simplest to implement |

---