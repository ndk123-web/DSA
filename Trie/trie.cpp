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
        TrieNode* root;

        Trie(){
            root = new TrieNode();
        }

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

        bool search(string str) {
            TrieNode* current = root;

            for (auto c : str) {
                int idx = c - 'a';
                if (current->child[idx] == nullptr) {
                    return false; 
                }
                current = current->child[idx];
            }


            return (current->isEnd == true ? true : false);
        }

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

        void visualize() {
            cout << "Trie Structure:\n";
            printTrie(root, "");
        }
};

int main (){
    Trie trie;

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

    trie.visualize();
}