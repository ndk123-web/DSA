# 🧭 Simplify Path — Stack Based Solution (Detailed)

---

## 📘 Problem Summary

You are given an **absolute Unix-style path** (starting with `/`).

Your task is to **simplify** it into its **canonical form**.

---

## 🧱 Unix Path Rules (Very Important)

| Token    | Meaning           | Action               |
| -------- | ----------------- | -------------------- |
| `/`      | Separator         | Ignore extra slashes |
| `.`      | Current directory | Ignore               |
| `..`     | Parent directory  | Go one level up      |
| `folder` | Valid directory   | Add to path          |

---

## 🎯 Goal

Return the **shortest, canonical path**:

* Starts with `/`
* No extra slashes
* No `.` or `..`

---

## 🧠 Core Idea

> **Treat the path like folders on a stack**

* Enter folder → `push`
* `..` → `pop`
* `.` or empty → ignore

---

## 💻 Code (With Short Comments)

```cpp
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack; // stores valid folders
        string cur;           // current folder being read

        // extra '/' added to process last folder
        for (char c : path + "/") {
            if (c == '/') {
                if (cur == "..") {
                    // go one level up
                    if (!stack.empty()) stack.pop_back();
                }
                else if (!cur.empty() && cur != ".") {
                    // valid folder name
                    stack.push_back(cur);
                }
                cur.clear(); // reset for next folder
            } else {
                cur += c; // build folder name
            }
        }

        // rebuild canonical path
        string result = "/";
        for (int i = 0; i < stack.size(); i++) {
            if (i > 0) result += "/";
            result += stack[i];
        }

        return result;
    }
};
```

---

## 🔍 Key Line Explained (Most Confusing Part)

```cpp
else if (!cur.empty() && cur != ".")
```

### Meaning:

> **Push only real folder names**

### Why?

* `cur == ""` → extra `/` → ignore
* `cur == "."` → current folder → ignore
* `cur == ".."` → already handled above

Only **actual directory names** should be stored.

---

## 🧪 Full Dry Run Example

### Input

```
/a/./b/../../c/
```

---

### Step-by-step

| Read | cur  | stack     | Action |
| ---- | ---- | --------- | ------ |
| `/`  | ``   | []        | ignore |
| `a`  | `a`  | []        | build  |
| `/`  | ``   | [`a`]     | push   |
| `.`  | `.`  | [`a`]     | build  |
| `/`  | ``   | [`a`]     | ignore |
| `b`  | `b`  | [`a`]     | build  |
| `/`  | ``   | [`a`,`b`] | push   |
| `..` | `..` | [`a`]     | pop    |
| `..` | `..` | []        | pop    |
| `c`  | `c`  | []        | build  |
| `/`  | ``   | [`c`]     | push   |

---

### Final Stack

```
["c"]
```

### Output

```
/c
```

---

## 🧠 Mental Model (Remember This)

> **Split by `/`, process folders one by one, use stack to simulate directory movement**

---

## ⏱️ Complexity

* **Time:** `O(n)`
* **Space:** `O(n)`

---

## ✅ Final Takeaway

* Stack represents the current directory path
* `..` removes last directory
* `.` and empty tokens do nothing
* Final path is rebuilt from stack

---