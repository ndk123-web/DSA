#include <iostream>

using namespace std;

struct TrieNode {

    // Minimum 26 character will be there thats why 26 size
    TrieNode* child[26];    
    bool isEnd;

    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 26 ; i++) {
            child[i] = nullptr;
        }
    }
};

class Trie {
    public:

        // root
        TrieNode* root;

        // created root in heap 
        Trie(){
            root = new TrieNode();
        }

        // insert string inside the trie 
        void insert(string str) {
            
            // current pointer pointing initially to the root 
            TrieNode* current = root;

            // loop through each character
            for (auto c : str) {
                int idx = c - 'a';
                if (current->child[idx] == nullptr) {
                    
                    // child[idx] will be storing pointer
                    current->child[idx] = new TrieNode(); 
                }

                // whether nullptr or not current will go to next node
                current = current->child[idx];
            }

            // it means end of string 
            current->isEnd = true;
        }

        // return t / f based on str present or not in trie
        bool search(string str) {
            TrieNode* current = root;

            for (auto c : str) {
                int idx = c - 'a';
                if (current->child[idx] == nullptr) {
                    return false; 
                }
                current = current->child[idx];
            }


            bool ans = current->isEnd == true ? true : false;

            return ans;
        }

        // actual function that is visualizing the entire trie using recursion
        void printTrie(TrieNode* node, string prefix) {

            for (int i = 0; i < 26; i++) {

                if (node->child[i] != nullptr) {

                    char c = 'a' + i;

                    cout << prefix << "|-- " << c << endl;

                    // child ke liye deeper prefix (recursion)
                    printTrie(node->child[i], prefix + "    ");
                }
            }
        }

        // visualize calls printTrie 
        void visualize() {
            cout << "Trie Structure:\n";
            printTrie(root, "");
        }

        // cleanup the root from heap 
        void destroy() {
            delete root;
        }
};

int main (){

    // created object of Trie and initilize root on heap
    Trie trie;

    // insert strings in heap 
    trie.insert("cat");
    trie.insert("cap");
    trie.insert("com");
    trie.insert("oom");
    trie.insert("qom");

    // if (trie.search("capassa")) {
    //     cout << "cat exists";
    // }else{
    //     cout << "cat not exists";
    // }

    // visualize entire trie from heap
    trie.visualize();


}