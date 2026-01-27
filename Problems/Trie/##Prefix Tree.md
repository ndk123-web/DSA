# 📌 Trie (Prefix Tree) 

## 📖 What is this?

This project implements a **Trie (Prefix Tree)** data structure in C++.
Trie is used for **fast string insertion, search, and prefix-based queries**, commonly seen in **autocomplete, spell-checkers, search suggestions, and dictionaries**.

---

## 🧠 Why Trie?

Normal arrays / hash sets fail when:

- You want **prefix search**
- You want **autocomplete**
- You want performance independent of number of words

Trie solves this by:

- Sharing common prefixes
- Searching in **O(length of word)** time

---

## 🧱 Trie Node Structure (Mental Model)

Each node represents:

- One character
- Links to next possible characters (`a–z`)
- A flag to mark **end of word**

```cpp
struct TrieNode {
    char ch;
    TrieNode* children[26];
    bool isEnd;
};
```

Key idea:

- **Nodes are reused**
- **Paths are shared**
- Words = paths from root to nodes with `isEnd = true`

---

## 🌱 Root Node

- Root does **not** represent any character
- It is just an entry point

```cpp
root = new TrieNode('\0');
```

---

## ⚙️ Operations Implemented

### 1️⃣ Insert a word

- Start from root
- For each character:
  - If node exists → reuse
  - Else → create new node

- Mark last node as `isEnd = true`

```cpp
insert("apple");
```

---

### 2️⃣ Search a word (exact match)

- Traverse character by character
- If path breaks → false
- At end → return `isEnd`

```cpp
search("apple");  // true
search("app");    // false (unless explicitly inserted)
```

---

### 3️⃣ startsWith (prefix check)

- Only checks if prefix path exists
- Does NOT require `isEnd = true`

```cpp
startsWith("app");  // true
startsWith("apx");  // false
```

---

## 🧩 Where Trie is Used (Real World)

- Autocomplete (Google, VS Code, phone keyboard)
- Spell checker
- Command suggestions
- Product search
- Dictionary apps

Autocomplete logic:

1. User types `"app"`
2. Trie node for `"app"` is found
3. DFS from that node
4. Return top-K suggestions (lexicographic or frequency-based)

---

## ❗ Your Confusions (And Why They Happened)

### ❓ Confusion 1: “Prefix sum vs Prefix tree”

- **Prefix sum** → numbers, arrays, cumulative addition
- **Prefix tree (Trie)** → strings, characters, paths

Same word “prefix”, completely different universe.

---

### ❓ Confusion 2: Vector / array initialization inside struct

You tried:

```cpp
array<TrieNode*,26> others;
others.resize(26, nullptr);  // ❌
```

Reality:

- `resize()` → only for `vector`
- `array` → fixed size, use `fill()`
- Raw array → use loop

Correct:

```cpp
for (int i = 0; i < 26; i++)
    children[i] = nullptr;
```

---

### ❓ Confusion 3: Overwriting nodes during insert

You initially did:

```cpp
curr->children[idx] = new TrieNode(c);
```

Problem:

- Existing paths were getting destroyed

Correct Trie rule:

> **Create node only if it does not exist**

```cpp
if (curr->children[idx] == nullptr)
    curr->children[idx] = new TrieNode(c);
```

---

### ❓ Confusion 4: search() vs startsWith()

You initially returned `true` just because path existed.

Reality:

- `search()` → checks **complete word**
- `startsWith()` → checks **prefix path**

That’s why `isEnd` exists.

---

### ❓ Confusion 5: Can we use raw array instead of vector?

Yes. And for Trie, **raw array is the best choice**.

Reason:

- Fixed alphabet size (26)
- No resizing needed
- Faster and simpler
- Common in interviews and production

---

## 🧠 Key Takeaways (Very Important)

- Trie nodes are **never overwritten**
- `isEnd` differentiates word vs prefix
- Root is a dummy node
- Raw arrays are ideal for Trie
- Trie is backend logic, not UI
