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