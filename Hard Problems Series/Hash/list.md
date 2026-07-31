## Hash 

### [Pattern 1: Foundation]
1. Sort Characters by Frequency
   - Trick -> stored in a hash map and then use a priority queue to sort by frequency.
   - *Take Care -> when you are adding characters to the result string, use `res += p.second;` or `res.push_back(p.second);` instead of `res = res + p.second;` to avoid O(n^2) time complexity*. 
```cpp
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> mapp;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            mapp[s[i]]++;
        }
        
        priority_queue<pair<int, char>> pq;
        for (const pair<char, int>& p : mapp) {
            pq.push({p.second, p.first});
        }

        string res = "";
        while (!pq.empty()) {
            pair<int, char> p = pq.top();
            for (int i = 0; i < p.first; i++)

                // literally take care here because (res = res + p.second) will be O(n^2) time complexity, so we need to use res += p.second; instead or res.push_back(p.second);
                res += p.second;

            pq.pop();
        }

        return res;
    }
};
```

1. First Unique Character in a String
   - Trick -> store the 27 vector size to store frequency of each character and then use a hash map to store the index of each character.
```cpp
class Solution {
public:
    int firstUniqChar(string s) {
        int n = s.size();
        vector<int> sizes(27, 0);

        unordered_map<char, int> mapp;

        for (int i = 0; i < n; i++) {
            sizes[s[i] - 'a']++;
            mapp[s[i]] = i;
        }

        for (int i = 0; i < n; i++) {
            if (sizes[s[i] - 'a'] == 1)
                return mapp[s[i]];
        }

        return -1;
    }
};
```

### [Pattern 2: Lexicographical Order]
1. Largest Number [leetcode](https://leetcode.com/problems/largest-number/)
   - Trick -> sort the numbers in a custom way, if `a + b > b + a` then `a` should come before `b`.
   - Take Care -> cpp concept sort , here that comaprator generrally means `a < b` means `a` should come before `b` in the sorted order, but here we are using `a + b > b + a` which means `a` should come before `b` if `a + b > b + a`.
  
i. Solution-1 using custom comparator and sorting mechanism
```cpp
class Solution {
public:
    string largestNumber(vector<int>& nums) {

        /*
            a < b
            i. 2 < 4 (true 2 comes first)
            ii. 4 < 2 (false 2 comes first)
            iii. 2 < 2 (false 2 comes (right one) first)

            a > b
            i. 2 > 4 (false 4 comes first)
            ii. 4 > 2 (true 4 comes first)
            iii. 2 > 2 (false 2 comes first (right one))
        */

        sort(nums.begin(), nums.end(), [](const int& a, const int& b) {
            return (to_string(a) + to_string(b)) >
                   (to_string(b) + to_string(a));
        });

        string s = "";
        for (int i = 0; i < nums.size(); i++) {
            if (s + to_string(nums[i]) > to_string(nums[i]) + s) {
                s += to_string(nums[i]);
            } else {
                s = to_string(nums[i]) + s;
            }
        }

        int cnt = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '0')
                cnt++;
        }

        return (cnt == s.size()) ? "0" : s;
    }
};
```

ii. Solution-2 without using custom comparator and sorting mechanism 
- Trick -> use DFS to generate the numbers in lexicographical order. 
```cpp
class Solution {
public:
    void dfs(vector<int>& nums, int startDigit, int n) {

        if (startDigit > n)
            return;

        for (int digit = 0; digit <= 9; digit++) {
            int next = startDigit * 10;

            if (next + digit > n)   
                return;
            
            nums.push_back(next + digit);
            dfs(nums, (next + digit), n);
        }

        return;
    }

    vector<int> lexicalOrder(int n) {
        vector<int> nums;

        for (int i = 0; i < 9; i++) {
            if (i + 1 > n) 
                break;

            nums.push_back(i+1);
            dfs(nums, i + 1, n);
        }

        return nums;
    }
};
```