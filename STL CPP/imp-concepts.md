# 🟨 FLASH CARD 1 — Lambda (Basic)

### ❓ Lambda kya hota hai?

➡️ Inline **function object**

```cpp
auto cmp = [](int a, int b) {
    return a < b;
};
```

### 🔑 Yaad rakh

- Lambda ka **return type = bool** (comparator case)
- `cout` bool ko:

  - `true` → `1`
  - `false` → `0` print karta hai

- Internally **true / false** hi hota hai

---

# 🟨 FLASH CARD 2 — Comparator Universal Rule (MOST IMPORTANT)

### ❗ Golden Rule (kabhi mat bhoolna)

```text
cmp(a,b) == true  → a comes BEFORE b
cmp(a,b) == false → a does NOT come before b
```

❌ “after” word dimaag se nikaal do
Comparator **sirf YES / NO** bolta hai

---

# 🟨 FLASH CARD 3 — `<` aur `>` ka actual role

### Ascending sort

```cpp
return a < b;
```

- chhota pehle

### Descending sort

```cpp
return a > b;
```

- bada pehle

👉 `<` / `>` **rule nahi** hain
👉 ye sirf **true / false banane ke tools** hain

---

# 🟨 FLASH CARD 4 — sort() ka rule

### sort ka goal

➡️ **Poora container order mein**

```cpp
sort(v.begin(), v.end(), cmp);
```

### Yaad rakh

- Comparator **bahut baar call hota hai**
- `a` aur `b` ka order **guaranteed nahi**
- sort **cmp ke bina andha hai**

---

# 🟨 FLASH CARD 5 — priority_queue Syntax

```cpp
priority_queue<T, Container, Comparator> pq(comparator);
```

Example:

```cpp
priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
```

### Parts:

- `T` → data type
- `Container` → storage (mostly vector)
- `Comparator` → priority rule

---

# 🟨 FLASH CARD 6 — decltype (one-liner)

```cpp
decltype(cmp)
```

➡️ “`cmp` ka jo type hai, wahi use karo”

Reason:

- Lambda ka **naam nahi hota**
- Isliye `decltype` use hota hai

---

# 🟨 FLASH CARD 7 — Heap Rules (CONFUSION KILLER)

### MIN HEAP

```cpp
return a > b;
```

➡️ chhota element = **higher priority** = top()

### MAX HEAP

```cpp
return a < b;
```

➡️ bada element = **higher priority** = top()

⚠️ Rule same hai:

```text
true → a before b
```

Bas **goal alag** hai

---

# 🟨 FLASH CARD 8 — sort vs heap (ONE LOOK TABLE)

| Feature    | sort         | priority_queue  |
| ---------- | ------------ | --------------- |
| Goal       | full order   | only top        |
| Output     | sorted array | max/min element |
| Comparator | ordering     | priority        |
| Guarantee  | full         | only top        |

---

# 🟨 FLASH CARD 9 — MOST COMMON MISTAKES ❌

❌ `>` means after
❌ heap ka rule ulta hota hai
❌ comparator ek baar call hota hai
❌ lambda returns int

✅ **true = a before b**
Bas ye yaad rakho

---
