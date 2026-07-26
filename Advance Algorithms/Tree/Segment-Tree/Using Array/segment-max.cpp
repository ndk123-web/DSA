#include <iostream>
#include <vector>

using namespace std;

vector<long long> segmentTree;

vector<long long> nums = {0, 5, 4, 2, 6, 8, 9, 1, 23, 42};

/*
    index 1: (0...7) max
    index 2: (0...4) max
    index 3: (5...7) max
    .
    .
    .
*/
void build(int node, int st, int end)
{

    if (st == end)
    {
        segmentTree[node] = nums[st];
        return;
    }

    int mid = st + (end - st) / 2;

    build(node * 2, st, mid);
    build(node * 2 + 1, mid + 1, end);

    segmentTree[node] = max(segmentTree[2 * node], segmentTree[2 * node + 1]);
    return;
}

int query(int node, int ql, int qr, int l, int r)
{
    if (l > qr || r < ql)
        return 0;

    if (l >= ql && r <= qr)
        return segmentTree[node];

    int mid = l + (r - l) / 2;
    return query(node * 2, ql, qr, l, mid) +
           query(node * 2 + 1, ql, qr, mid + 1, r);
}

int update(int idx, int value, int l, int r, int node)
{
    if (l == r)
    {
        segmentTree[node] = value;
        return;
    }

    int mid = l + (r - l) / 2;

    if (idx <= mid)
        update(idx, value, l, mid, node * 2);

    else
        update(idx, value, mid + 1, r, node * 2 + 1);

    segmentTree[node] = max(segmentTree[node * 2], segmentTree[2 * node + 1]);
}

int main()
{

    int N = nums.size();

    // in worst case, nodes will lower than 4*N
    segmentTree.assign(LLONG_MIN, 4 * N);

    build(1, 0, nums.size() - 1);
    return 0;
}