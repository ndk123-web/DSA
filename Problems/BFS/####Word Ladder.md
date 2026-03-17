# Intuition

We are given a **beginWord**, an **endWord**, and a dictionary `wordList`.
We need to transform `beginWord` into `endWord` such that:

1. Only **one letter can change at a time**.
2. Each intermediate word must exist in the **wordList**.
3. We must return the **length of the shortest transformation sequence**.

Example:

```
beginWord = "hit"
endWord   = "cog"
wordList  = ["hot","dot","dog","lot","log","cog"]
```

Valid transformation:

```
hit → hot → dot → dog → cog
```

Length = **5**

The key observation is that every word can be seen as a **node in a graph**.

Two words are connected if they differ by **exactly one letter**.

Example graph:

```
hit
 |
hot
 / \
dot lot
 |   |
dog log
  \ /
  cog
```

The problem now becomes:

```
Find the shortest path from beginWord to endWord
```

Since the graph is **unweighted**, the best algorithm for finding the shortest path is **Breadth First Search (BFS)**.

---

# Approach

### Step 1 — Convert the dictionary into a set

A set allows **O(1) lookup** when checking whether a transformed word exists in the dictionary.

```
unordered_set<string> words(wordList.begin(), wordList.end());
```

---

### Step 2 — BFS traversal

We use a **queue** to explore transformations level by level.

Each BFS level represents the **number of transformations performed so far**.

```
queue<string> q
```

Initialize:

```
q.push(beginWord)
steps = 1
```

---

### Step 3 — Generate all possible transformations

For every word we take from the queue:

1. Try changing every character.
2. Replace it with `'a'` to `'z'`.

Example:

```
hit
```

Possible transformations:

```
ait, bit, cit ... zit
hat, hbt, hct ... hzt
hia, hib, hic ... hiz
```

If a generated word exists in the dictionary:

```
push it into queue
remove it from set (mark visited)
```

Removing it ensures we **don't revisit the same word again**.

---

### Step 4 — BFS level expansion

At each level:

```
size = queue size
```

Process all nodes in that level.

If we encounter `endWord`, we return:

```
steps
```

because BFS guarantees that the **first time we reach it is the shortest path**.

---

# Code

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

        unordered_set<string> words(wordList.begin(), wordList.end());

        if(words.find(endWord) == words.end())
            return 0;

        queue<string> q;
        q.push(beginWord);

        int steps = 1;

        while(!q.empty()){

            int size = q.size();

            for(int i = 0; i < size; i++){

                string word = q.front();
                q.pop();

                if(word == endWord)
                    return steps;

                for(int j = 0; j < word.size(); j++){

                    string temp = word;

                    for(char c = 'a'; c <= 'z'; c++){

                        temp[j] = c;

                        if(words.find(temp) != words.end()){

                            q.push(temp);
                            words.erase(temp);
                        }
                    }
                }
            }

            steps++;
        }

        return 0;
    }
};
```

---

# Complexity

### Time Complexity

```
O(N × L × 26)
```

Where:

- `N` = number of words in the dictionary
- `L` = length of each word
- `26` = number of possible character replacements

For each word we try **26 transformations per character**.

---

### Space Complexity

```
O(N)
```

Used for:

- the queue
- the dictionary set

---

# Key Concepts

### Graph Representation

Each word acts as a **node** and edges exist when two words differ by **one character**.

---

### Why BFS?

Because BFS explores nodes **level by level**, it guarantees the **shortest transformation sequence**.

---

### Why remove words from the set?

To prevent revisiting the same word multiple times.

Without this, the algorithm could:

```
revisit nodes → create cycles → cause TLE
```

---

# Summary

This problem is essentially:

```
Shortest Path in an Unweighted Graph
```

Technique used:

```
BFS + String Transformation
```

Core idea:

```
For each word
    change each letter from 'a' to 'z'
    check if it exists in dictionary
    push into queue
```

The first time BFS reaches the **endWord**, we have found the **shortest transformation sequence**.
