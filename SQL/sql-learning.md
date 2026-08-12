# SQL Pattern Mastery — Core Fundamentals

## 🎯 The Goal

Learn SQL using **DSA-style Pattern Recognition**:

```text
Problem Wording ──► Identify Concept ──► Recognize SQL Pattern ──► Write Query
```

Instead of memorizing syntax, train your mind to look at a problem description and instantly map it to the right SQL pattern and visual table transformation.

---

## ⚡ Logical Query Execution Order

When writing SQL, you write in **Syntax Order**. But the SQL database engine processes your query in **Logical Execution Order**:

```text
Syntax Order (How you write it)       Logical Processing Order (How SQL executes it)
───────────────────────────────       ───────────────────────────────────────────────
1. SELECT                             1. FROM       ──► Pick table(s) to fetch raw data
2. FROM                               2. WHERE      ──► Filter rows BEFORE grouping
3. WHERE                              3. GROUP BY   ──► Group rows into buckets
4. GROUP BY                           4. HAVING     ──► Filter aggregated groups
5. HAVING                             5. SELECT     ──► Choose & compute final columns
6. ORDER BY                           6. DISTINCT   ──► Remove duplicate rows
7. LIMIT / OFFSET                     7. ORDER BY   ──► Sort the final output rows
                                      8. LIMIT      ──► Restrict number of rows returned
```

> [!KEY TAKEAWAY]
> You cannot use a `SELECT` column alias in a `WHERE` clause because `WHERE` executes **BEFORE** `SELECT`!

---

# 1. Table Structure

A table contains **Rows** (individual records) and **Columns** (attributes/properties).

### 📥 Input Table: `employees`
| id | name | department | salary | manager_id |
|---|---|---|---|---|
| 1 | Amit | IT | 70000 | 3 |
| 2 | Rahul | HR | 50000 | 3 |
| 3 | Priya | IT | 90000 | NULL |
| 4 | Neha | Sales | 60000 | 2 |
| 5 | Vikram | IT | 45000 | 3 |

---

# 2. SELECT — Choosing Columns

⚡ **Memory Hook**: `SELECT` = Choose attributes | `FROM` = Choose source table

### 💻 Query (Specific Columns)
```sql
SELECT name, salary
FROM employees;
```

### 📤 Output Table
| name | salary |
|---|---|
| Amit | 70000 |
| Rahul | 50000 |
| Priya | 90000 |
| Neha | 60000 |
| Vikram | 45000 |

### 💡 Pattern Rule
- Use `SELECT name, salary` when you only need specific columns.
- Avoid `SELECT *` in production/interviews unless explicitly requested, to optimize network I/O and performance.

---

# 3. WHERE — Filtering Rows

⚡ **Memory Hook**: `WHERE` filters individual **rows** based on conditions.

### 💻 Query
```sql
SELECT name, salary
FROM employees
WHERE department = 'IT';
```

### 📤 Output Table
| name | salary |
|---|---|
| Amit | 70000 |
| Priya | 90000 |
| Vikram | 45000 |

---

# 4. Comparison Operators

SQL supports standard comparison operators: `= `, `!=` (or `<>`), `>`, `<`, `>=`, `<=`.

### 💻 Query (`salary > 60000`)
```sql
SELECT name, department, salary
FROM employees
WHERE salary > 60000;
```

### 📤 Output Table
| name | department | salary |
|---|---|---|
| Amit | IT | 70000 |
| Priya | IT | 90000 |

---

# 5. AND / OR / NOT — Logical Operators

⚡ **Memory Hook**: 
- `AND` = All conditions must be TRUE.
- `OR` = At least one condition must be TRUE.
- `NOT` = Inverts the condition condition.

### 💻 Query (`AND`)
```sql
SELECT name, salary
FROM employees
WHERE department = 'IT'
  AND salary >= 70000;
```

### 📤 Output Table
| name | salary |
|---|---|
| Amit | 70000 |
| Priya | 90000 |

---

### 💻 Query (`OR`)
```sql
SELECT name, department
FROM employees
WHERE department = 'HR'
   OR department = 'Sales';
```

### 📤 Output Table
| name | department |
|---|---|
| Rahul | HR |
| Neha | Sales |

---

# 6. IN — Matching a Set of Values

⚡ **Memory Hook**: `IN ('A', 'B')` is shorthand for `x = 'A' OR x = 'B'`. Think $x \in \{A, B\}$.

### 💻 Query
```sql
SELECT name, department
FROM employees
WHERE department IN ('HR', 'Sales');
```

### 📤 Output Table
| name | department |
|---|---|
| Rahul | HR |
| Neha | Sales |

---

# 7. BETWEEN — Range Filtering

⚡ **Memory Hook**: `BETWEEN low AND high` is **inclusive** ($low \le x \le high$).

### 💻 Query
```sql
SELECT name, salary
FROM employees
WHERE salary BETWEEN 50000 AND 70000;
```

### 📤 Output Table
| name | salary |
|---|---|
| Amit | 70000 |
| Rahul | 50000 |
| Neha | 60000 |

---

# 8. LIKE — String Pattern Matching

⚡ **Memory Hook**:
- `%` = Zero or more characters (any length)
- `_` = Exactly ONE character

| Pattern | Meaning | Example Matches |
|---|---|---|
| `'A%'` | Starts with 'A' | `Amit`, `Anil`, `A` |
| `'%\'` | Ends with 'a' | `Priya`, `Neha` |
| `'`%it%'` | Contains 'it' | `Amit`, `Vikram` |
| `'A_i%'` | 'A' + 1 char + 'i' + anything | `Anil`, `Abhi` |

### 📥 Input Table: `employees`
| id | name |
|---|---|
| 1 | Amit |
| 2 | Priya |
| 3 | Neha |
| 4 | Anil |

### 💻 Query (`LIKE 'A%'`)
```sql
SELECT name
FROM employees
WHERE name LIKE 'A%';
```

### 📤 Output Table
| name |
|---|
| Amit |
| Anil |

---

# 9. NULL Logic & Three-Valued Logic

> [!WARNING]
> `NULL` means **UNKNOWN / MISSING**. It is NOT `0`, NOT `''` (empty string), and NOT `FALSE`.

### Three-Valued Logic Table
In SQL, comparing anything with `NULL` returns `UNKNOWN`:

| Comparison | Result |
|---|---|
| `5 = NULL` | `UNKNOWN` |
| `NULL = NULL` | `UNKNOWN` |
| `NULL != 2` | `UNKNOWN` |

Because a `WHERE` clause **ONLY** keeps rows where the condition is `TRUE`, `WHERE manager_id = NULL` or `WHERE manager_id != 2` will silently discard rows where `manager_id` is `NULL`!

### 💻 WRONG Query ❌
```sql
-- Returns ZERO rows because NULL = NULL evaluates to UNKNOWN!
SELECT name FROM employees WHERE manager_id = NULL;
```

### 💻 CORRECT Query ✅
```sql
SELECT name, department
FROM employees
WHERE manager_id IS NULL;
```

### 📥 Input Table: `employees`
| id | name | manager_id |
|---|---|---|
| 1 | Amit | 3 |
| 2 | Rahul | 3 |
| 3 | Priya | NULL |

### 📤 Output Table (`WHERE manager_id IS NULL`)
| name | department |
|---|---|
| Priya | IT |

### ⚡ Permanent Rule for NULL:
```text
= NULL      ❌ WRONG
!= NULL     ❌ WRONG
IS NULL     ✅ CORRECT
IS NOT NULL ✅ CORRECT
```

---

# 10. AS — Aliasing (Renaming Columns & Tables)

⚡ **Memory Hook**: `AS` gives a temporary display name in query results. It does **NOT** mutate database schemas.

### 💻 Query
```sql
SELECT 
    name AS employee_name,
    salary * 12 AS annual_salary
FROM employees;
```

### 📤 Output Table
| employee_name | annual_salary |
|---|---|
| Amit | 840000 |
| Rahul | 600000 |
| Priya | 1080000 |
| Neha | 720000 |
| Vikram | 540000 |

---

# 11. DISTINCT — Removing Duplicates

⚡ **Memory Hook**: `DISTINCT` eliminates duplicate rows from the final result set.

### 📥 Input Table: `employees`
| name | department |
|---|---|
| Amit | IT |
| Rahul | HR |
| Priya | IT |
| Neha | Sales |
| Vikram | IT |

### 💻 Query
```sql
SELECT DISTINCT department
FROM employees;
```

### 📤 Output Table
| department |
|---|
| IT |
| HR |
| Sales |

---

# 12. ORDER BY — Sorting Results

⚡ **Memory Hook**: `ORDER BY` sorts rows (`ASC` = default ascending, `DESC` = descending).

### 💻 Single-Column Sort (Salary Descending)
```sql
SELECT name, salary
FROM employees
ORDER BY salary DESC;
```

### 📤 Output Table
| name | salary |
|---|---|
| Priya | 90000 |
| Amit | 70000 |
| Neha | 60000 |
| Rahul | 50000 |
| Vikram | 45000 |

---

### 💻 Multi-Column Sort (`ORDER BY department ASC, salary DESC`)
Like a custom DSA comparator: first sort by department alphabetically, then by salary highest first.

```sql
SELECT name, department, salary
FROM employees
ORDER BY department ASC, salary DESC;
```

### 📤 Output Table
| name | department | salary |
|---|---|---|
| Rahul | HR | 50000 |
| Priya | IT | 90000 |
| Amit | IT | 70000 |
| Vikram | IT | 45000 |
| Neha | Sales | 60000 |

---

# 13. LIMIT & OFFSET — Pagination Pattern

⚡ **Memory Hook**:
- `LIMIT N` = Pick at most $N$ rows.
- `OFFSET M` = Skip the first $M$ rows.

### 📐 Pagination Formula
To get Page $P$ with Page Size $S$:
$$\text{LIMIT } S \quad \text{OFFSET } ((P - 1) \times S)$$

### 💻 Query (Page 2, 2 items per page: `LIMIT 2 OFFSET 2`)
Sorted dataset: [Priya (90k), Amit (70k), Neha (60k), Rahul (50k), Vikram (45k)]

```sql
SELECT name, salary
FROM employees
ORDER BY salary DESC
LIMIT 2 OFFSET 2;
```

### 📤 Output Table (Skips Priya & Amit)
| name | salary |
|---|---|
| Neha | 60000 |
| Rahul | 50000 |

---

# 14. Comprehensive Real-World Master Example

### Question:
> "Find the top 2 highest-paid IT employees earning more than 50,000."

### 🧠 Pattern Recognition Step-by-Step:
1. "IT employees" ──► `WHERE department = 'IT'`
2. "earning > 50000" ──► `AND salary > 50000`
3. "highest paid first" ──► `ORDER BY salary DESC`
4. "top 2" ──► `LIMIT 2`

### 💻 SQL Query
```sql
SELECT name, salary
FROM employees
WHERE department = 'IT'
  AND salary > 50000
ORDER BY salary DESC
LIMIT 2;
```

### 📤 Output Table
| name | salary |
|---|---|
| Priya | 90000 |
| Amit | 70000 |

---

# 15. SQL Pattern Recognition Cheat Sheet Matrix

| English Problem Keyword | SQL Clause / Operator | Quick Mental Model |
|---|---|---|
| "Filter rows by condition" | `WHERE` | Row-by-row filter |
| "One of multiple values" | `IN (val1, val2)` | $x \in \{val1, val2\}$ |
| "Value within range" | `BETWEEN low AND high` | $low \le x \le high$ (inclusive) |
| "Starts with / Contains" | `LIKE 'A%'` / `LIKE '%A%'` | `%` wildcard match |
| "Missing / unknown value" | `IS NULL` | Never use `= NULL` |
| "Unique values only" | `DISTINCT` | Deduplicate output |
| "Sort highest to lowest" | `ORDER BY column DESC` | Descending order |
| "Top N records" | `ORDER BY ... LIMIT N` | Heap / Top-K |
| "Skip first N records" | `OFFSET N` | Pagination skip |
