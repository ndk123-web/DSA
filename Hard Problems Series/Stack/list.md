### Stack Lists

### [Pattern-1: Basic Foundation]
1. Valid Parentheses [Leetcode 20](https://leetcode.com/problems/valid-parentheses/)
   - Trick: Use a stack to keep track of opening brackets and check for matching closing brackets.
   - Use Map to store the mapping of opening and closing brackets for easy lookup.
  
2. Min Stack [Leetcode 155](https://leetcode.com/problems/min-stack/)
   - Trick: Use 1 stack and each node in stack will store the value and the minimum value at that point.

### [Pattern-2: Monotonic Stack]
1. Next Greater Element [Leetcode 496](https://leetcode.com/problems/next-greater-element-i/)
   - Trick: Use a stack to keep track of elements for which we haven't found the next greater element yet. Iterate through the array and update the stack accordingly.
   - Time -> O(N + M), Space -> O(N) 
```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res(nums2.size(), -1);
        vector<int> fres(nums1.size(), -1);
        unordered_map<int, int> mapp;

        for (int i = 0; i < nums2.size(); i++) {
            mapp[nums2[i]] = i;
        }

        stack<pair<int, int>> st;
        for (int i = 0; i < nums2.size(); i++) {

            while (!st.empty() && st.top().first < nums2[i]) {
                res[st.top().second] = nums2[i];
                st.pop();
            }

            st.push({nums2[i], i});
        }

        for (int i = 0; i < nums1.size(); i++) {
            fres[i] = res[mapp[nums1[i]]];
        }

        return fres;
    }
};
```

2. Next Greater Element II [Leetcode 503](https://leetcode.com/problems/next-greater-element-ii/)
   - Trick: Similar to Next Greater Element, but since the array is circular, we can iterate through the array twice ((current index + 1) - end - start - (current index - 1)).
   - Time -> O(N), Space -> O(N)
```cpp
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        /*
            means at most 1 time it will traverse
            assume
            1 2 1 | 1 2 1 thats how if we imagined it
            2 -1 -2
        */
        int n = nums.size();
        vector<int> res(n, -1);

        stack<pair<int, int>> st;

        for (int i = 0; i < 2 * n; i++) {

            while (!st.empty() && st.top().first < nums[i % n]) {
                res[st.top().second] = nums[i % n];
                st.pop();
            }

            st.push({nums[i % n], i % n});
        }

        return res;
    }
};
```

3. Daily Temperatures [Leetcode 739](https://leetcode.com/problems/daily-temperatures/)
   - Trick: Use a stack to keep track of the indices of the temperatures. For each temperature, pop from the stack until you find a warmer temperature and calculate the difference in indices.
   - Time -> O(N), Space -> O(N)
```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<pair<int, int>> st;
        int n = temperatures.size();
        vector<int> res(n, 0);

        for (int i = 0; i < n; i++) {

            while (!st.empty() && st.top().first < temperatures[i]) {
                res[st.top().second] = (i - st.top().second);
                st.pop();
            }

            st.push({temperatures[i], i});
        }

        return res;
    }
};
```

### [Pattern-3: Stack with String Manipulation]
1. Simplify Path [Leetcode 71](https://leetcode.com/problems/simplify-path/)
   - Trick: Use a stack to process the path components. Push valid directory names onto the stack and pop for "..". Ignore "." and empty components.
   - Time -> O(N), Space -> O(N)
```cpp
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> st;
        string word = "";

        for (char& ch : path + "/") {
            if (ch == '/') {

                if (word == "..") {
                    if (!st.empty())
                        st.pop_back();
                }

                else if (!word.empty() && word != ".")
                    st.push_back(word);

                word.clear();
            }

            else {
                word += ch;
            }
        }

        string res = st.empty() ? "/" : "";

        for (int i = 0; i < st.size(); i++) {
            res = res + "/" + st[i];
        }

        return res;
    }
};
```