#include <bits/stdc++.h>

using namespace std;

void radixSort(vector<int>& v) {

    int n = v.size();

    int maxElement = *max_element(v.begin(), v.end());

    for (int exp = 1; maxElement / exp > 0; exp = exp * 10) {
        
        vector<vector<int>> digits(10);
        
        // push values according to last digit
        for (int i = 0; i < n; i++) {
            int num = v[i];

            int index = (num / exp) % 10;
            digits[index].push_back(num);
        }

        v.clear();

        for (int k = 0; k < 10; k++) {
            for (int j = 0; j < digits[k].size(); j++) {
                v.push_back(digits[k][j]);
            }
        }
    }
}

int main() {

    vector<int> arr = {4,12,41,12,4,2,124,42};

    cout << "BEFORE: " <<endl;
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    radixSort(arr);

    cout << "AFTER: " <<endl;
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}