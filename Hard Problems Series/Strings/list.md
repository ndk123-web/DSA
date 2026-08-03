## String List             

### Advance String 

1. ZigZag Conversion
    - Trick -> Use a `row` variable to keep track of current row and `step` variable to determine the direction of movement (down or up). Append characters to the corresponding row and finally concatenate all rows.
```cpp
class Solution {
public:
    string convert(string s, int numRows) {
        /*
            P   A   H   N
            A P L S I I G
            Y   I   R
        */

        if (numRows == 1)
            return s;

        vector<string> matrix(numRows, "");

        int step = 0;
        int row = 0;

        for (int i = 0; i < s.size(); i++) {

            matrix[row].push_back(s[i]);

            if (row == 0)
                step = 1;
            else if (row == numRows - 1)
                step = -1;

            row += step;
        }

        string res = "";
        for (int i = 0; i < matrix.size(); i++) {
            res += matrix[i];
        }

        return res;
    }
};
```

2. String Compression
   - Trick -> Use 2 pointer to keep track `readIndex` and `writeIndex`. Count the frequency of each character and write the character and its count to the string.
```cpp
class Solution {
public:
    int compress(vector<char>& chars) {

        int readIndex = 0, writeIndex = 0;
        int n = chars.size();
        int res = 0;

        while (readIndex < n) {

            char currentChar = chars[readIndex];
            int count = 0;

            res++;

            while (readIndex < n && currentChar == chars[readIndex]) {
                readIndex++;
                count++;
            }

            chars[writeIndex++] = currentChar;

            if (count > 1) {
                string sCount = to_string(count);
                int i = 0;
                while (i < sCount.size()) {
                    res++;
                    chars[writeIndex++] = sCount[i++];
                }
            }
        }

        return res;
    }
};
```