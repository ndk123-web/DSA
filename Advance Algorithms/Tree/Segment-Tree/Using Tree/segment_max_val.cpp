#include <bits/stdc++.h>

using namespace std;

struct SegmentNode {
    int l, r, val;
    SegmentNode *left, *right;

    SegmentNode(int l, int r) {
        this->l = l;
        this->r = r;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~SegmentNode() {
        delete left;
        delete right;
    }
};

class SegmentTree{
    public:

        SegmentNode *root;
        vector<int> arr;

        SegmentTree(vector<int> arr) {
            this->arr = arr;
            root = build(0, arr.size()-1);
        }

        SegmentNode* build(int l, int r) {
            
            SegmentNode* node = new SegmentNode(l,r);

            if (l == r) {
                node->val = arr[l];
                return node;
            }

            int mid = l + (r-l)/2;

            node->left = build(l,mid);
            node->right = build(mid+1,r);

            node->val = max(node->left->val, node->right->val);

            return node;
        }

        void visualize(SegmentNode* node) {
            if (!node) {
                return;
            }

            cout << "L: " << node->l << " R: " << node->r << " Val: " << node->val << "\n";

            visualize(node->left);
            visualize(node->right);

            return;
        }

        int query(SegmentNode* node, int ql, int qr) {
            
            if (!node) 
                return INT_MIN;
            
            int l = node->l;
            int r = node->r;

            // no overlap
            if (l > qr || r < ql) 
                return INT_MIN;
            
            // complete overlap
            if (l >= ql && r <= qr) 
                return node->val;
            
            // partial overlap 
            int lval = query(node->left, ql, qr);
            int rval = query(node->right, ql, qr);

            return max(lval, rval);
        }
 };


int main() {

    vector<int> arr = {2,5,9,-1,5,10};
    SegmentTree* segTree = new SegmentTree(arr);

    // visualize
    segTree->visualize(segTree->root);

    cout << "MAX: " << segTree->query(segTree->root, 3,5);

    return 0;
}