```cpp
struct DLL {

    DLL* prev;
    DLL* next;

    unordered_set<string> keys;
    int count;

    DLL(int c) : count(c), prev(nullptr), next(nullptr) {}
};

class AllOne {
public:
    unordered_map<string, DLL*> mapp;
    DLL* head;
    DLL* tail;

    AllOne() {
        head = new DLL(0);
        tail = new DLL(0);

        head->next = tail;
        tail->prev = head;
    }

    void inc(string key) {

        // if no key present
        if (!mapp.count(key)) {

            // if not in mapp and count != 1 means we need to create new one
            if (head->next->count != 1) {
                DLL* bucket = new DLL(1);
                bucket->keys.insert(key);

                mapp[key] = bucket;

                insertAfter(head, bucket);
            }

            // we already have bucket for count 1
            else {
                DLL* bucket = head->next;

                bucket->keys.insert(key);
                mapp[key] = bucket;
            }

            return;
        }

        // if key is present
        DLL* bucket = mapp[key];

        // if bucket->next is not that count bucket
        if (bucket->next->count != bucket->count + 1) {

            DLL* newBucket = new DLL(bucket->count + 1);

            insertAfter(bucket, newBucket);

            newBucket->keys.insert(key);
            bucket->keys.erase(key);

            mapp[key] = newBucket;

            if (bucket->keys.size() == 0) {
                removeNode(bucket);
                delete bucket;
            }
        }

        // next count bucket already exists
        else {
            DLL* nextBucket = bucket->next;

            nextBucket->keys.insert(key);
            mapp[key] = nextBucket;

            bucket->keys.erase(key);
            if (bucket->keys.size() == 0) {
                removeNode(bucket);
                delete bucket;
            }
        }
    }

    void insertAfter(DLL* curr, DLL* newNode) {
        newNode->prev = curr;
        newNode->next = curr->next;

        curr->next->prev = newNode;
        curr->next = newNode;
    }

    void removeNode(DLL* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void dec(string key) {

        // question sayin that already present in mapp

        DLL* bucket = mapp[key];

        // if key in first bucket
        if (bucket->count == 1) {
            mapp.erase(key);
            bucket->keys.erase(key);

            if (bucket->keys.size() == 0) {
                removeNode(bucket);
                delete bucket;
            }
        }

        // if not in first bucket
        else if (bucket->prev->count == bucket->count - 1) {
            DLL* prevBucket = bucket->prev;

            prevBucket->keys.insert(key);

            mapp[key] = prevBucket;

            bucket->keys.erase(key);
            if (bucket->keys.size() == 0) {
                removeNode(bucket);
                delete bucket;
            }
        }

        // mid bucket is missing
        else {
            DLL* newBucket = new DLL(bucket->count - 1);

            insertAfter(bucket->prev, newBucket);
            newBucket->keys.insert(key);
            mapp[key] = newBucket;

            bucket->keys.erase(key);

            if (bucket->keys.size() == 0) {
                removeNode(bucket);
                delete bucket;
            }
        }
    }

    string getMaxKey() {
        if (tail->prev == head)
            return "";
        return *tail->prev->keys.begin();
    }

    string getMinKey() {
        if (head->next == tail)
            return "";
        return *head->next->keys.begin();
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
```