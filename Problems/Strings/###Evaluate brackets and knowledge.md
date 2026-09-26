## 1807. Evaluate the Bracket Pairs of a String1807. Evaluate the Bracket Pairs of a String

```cpp
class Solution {
public:
    // map<pair<int, int>, string> mapp;
    unordered_map<string, string> know;
    string res;

    int inside_bracker(int position, string& s) {
        int n = s.size();
        // int initial_i = position - 1;

        string key = "";
        while (position < n && s[position] != ')') {
            key.push_back(s[position]);
            position++;
        }

        if (know.find(key) != know.end()) {
            res += know[key];
        } else {
            res.push_back('?');
        }
        // mapp[{initial_i, position}] = key;

        // go to the next position after ")" this

        return position;
    }

    string evaluate(string s, vector<vector<string>>& knowledge) {
        int n = s.size();

        // O(1) operation for future
        for (auto& v : knowledge) {
            know[v[0]] = v[1];
        }

        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                i = inside_bracker(i + 1, s);
            } else {
                res.push_back(s[i]);
            }
        }

        return res;
    }
};
```
