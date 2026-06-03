#include <bits/stdc++.h>

using namespace std; 

/*
    can be used when numbers are uniformly distributed 
*/ 

vector<long long> bucketSort(vector<long long>& v, int bucketSize) {
    long long minElement = *min_element(v.begin(), v.end());
    long long maxElement = *max_element(v.begin(), v.end());
    int n = v.size();

    vector<vector<long long>> buckets(bucketSize); 

    // push values in according to in the buckets
    for (int i = 0; i < v.size(); i++) {
        long long num = v[i];

        int bucketIndex = (num - minElement) / bucketSize;
        buckets[bucketIndex].push_back(num);
    }

    // sort the each bucket
    for (int i = 0; i < bucketSize; i++) {
        if (buckets[i].size() >= 2) 
            sort(buckets[i].begin(), buckets[i].end());
    }

    // concatenate
    vector<long long> res;

    for (int i = 0; i < bucketSize; i++) {

        for (int j = 0; j < buckets[i].size(); j++) {
            res.push_back(buckets[i][j]);
        }
    }

    v = res;
    return res;
}

int main() {
    vector<long long> arr = {1,99,12,42,15,74,5};


    cout << "BEFORE: " << endl;
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    long long minElement = *min_element(arr.begin(), arr.end());
    long long maxElement = *max_element(arr.begin(), arr.end());
    

    /*
        if we dont know each bucket size then ?
        n = 10 means 9 holes are there
        max =100, min=1
        100-1=99 is range and holes = bucketSize 

        we need 99 to store in 9 holes
        99/9 = atleast 11 each bucket size need if size/hole = 9

        here 11 each bucket size and 99 range 
        99/11+1 = 10 
        here 10 is the bucketCount that is actual buckets need overall
    */

    int eachBucketSize = 10;
    int bucketCount = (maxElement - minElement) / (eachBucketSize + 1);
    bucketSort(arr, bucketCount);
    
    cout << "AFTER: " << endl;
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}