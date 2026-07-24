#include <iostream>
#include <vector>

using namespace std;

vector<int> fenwickTree;

int fenwickAdd(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        int idx = i + 1;

        while (idx <= arr.size())
        {
            fenwickTree[idx] += arr[i];

            // 2's completement idx then , & with original idx then add with origianl idx to get next idx
            idx = idx + (idx & -idx);
        }
    }
}

int update(int idx, int value)
{
    while (idx < fenwickTree.size())
    {
        fenwickTree[idx] += value;

        // go to next idx where we need to add value
        idx = idx + (idx & -idx);
    }
}

int query(int q)
{
    int sum = 0;
    while (q > 0)
    {
        sum += fenwickTree[q];

        // go to the prev index where we need to get the sum for q
        q = q - (q & -q);
    }
    return sum;
}

int rangeQuery(int l, int r)
{
    if (l == 0)
        return query(r);

    if (r >= fenwickTree.size())
        return 0;

    // l++;
    // r++;
    return query(r) - query(l - 1);
}

int main()
{

    vector<int> arr = {1, 4, 6, 4, 3, 2};
    fenwickTree.resize(arr.size() + 1, 0);

    // add O(N LogN)
    fenwickAdd(arr);
    for (int i = 0; i < arr.size() + 1; i++)
    {
        cout << fenwickTree[i] << " ";
    }
    cout << "\n";

    // query O(LogN)
    int idx = 4; // 0 to 4 sum ?
    int q = query(idx);
    cout << q;

    cout << "\n";

    // range
    int l = 2, r = 4;
    int range = rangeQuery(l, r);
    cout << range;

    return 0;
}