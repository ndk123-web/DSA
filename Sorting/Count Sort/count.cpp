// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>

using namespace std;

int main() {
    
    vector<int> arr = {1,22,5,21,12,1};
    int max = *max_element(arr.begin(),arr.end());
    int min = *min_element(arr.begin(),arr.end());

    // important fora handling non negative and negative both 
    int range = max - min + 1;

    // max size of count bucket
    vector<int> count(range , 0);
    
    // frequencey of each element 
    for (int i = 0 ; i < arr.size(); i++) {
        count[arr[i] - min]++;
    }
    
    // loop through count bucket which is automatically sorted 
    // from 0 to max_element of array
    for (int i = 0 ; i < count.size();i++){
        if (count[i] != 0) {
            for (int j = 0 ; j < count[i]; j++) {
                cout << i + min << " ";
            }
        }
    }
    
    return 0;
}