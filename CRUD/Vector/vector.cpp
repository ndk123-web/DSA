#include <iostream>
#include <vector>

using namespace std;

vector<int> CreateVector()
{
    vector<int> arr = {1, 2, 3};
    return arr;
}

void ReadVector(vector<int> arr)
{
    for (int i : arr)
    {
        cout << i << "\n";
    }
    return;
}

void UpdateVector(vector<int> arr)
{
    // arr[0] = 100;
    arr.at(0) = 100;
}

void DeleteVector(vector<int> arr)
{
    auto it = arr.erase(arr.begin() + 3);
    if (it != arr.end())
    {
        cout << "Found and Deleted" << endl;
    }
    else
    {
        cout << "Not Found" << endl;
    }

    return;
}

int main()
{

    // create vector
    vector<int> vect = CreateVector();

    ReadVector(vect);
    UpdateVector(vect);
    DeleteVector(vect);

    return 0;
}