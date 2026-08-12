# SQL JOINs — Relational Pattern Mastery

## 🎯 Why JOINs Exist

Relational databases split data across multiple tables (normalization) to eliminate redundancy. **JOINs** allow us to stitch related tables back together using shared keys.

```text
  Table A (Employees)                 Table B (Departments)
+----+-------+---------+           +----+------------+
| id | name  | dept_id |           | id | dept_name  |
+----+-------+---------+           +----+------------+
| 1  | Alice | 10      |─────┐     | 10 | IT         |
| 2  | Bob   | 20      |───┐ └───► | 20 | HR         |
+----+-------+---------+   └─────► +----+------------+
                               JOIN ON Employees.dept_id = Departments.id
```

---

## ⚡ The Ultimate JOIN Decision Flowchart

When reading a problem, ask yourself **"Which rows MUST survive in the final output?"**

```text
                            Which rows must survive?
                                       │
         ┌─────────────────────────────┼─────────────────────────────┐
         ▼                             ▼                             ▼
   Only matching rows           ALL rows from Table A       ALL rows from Table B
   in BOTH tables               (Left table)                (Right table)
         │                             │                             │
         ▼                             ▼                             ▼
    INNER JOIN                     LEFT JOIN                     RIGHT JOIN
                                                              (or swap & LEFT)
         │                             │                             │
         ├─────────────────────────────┴─────────────────────────────┤
         │
         ├─────────────────────────────┬─────────────────────────────┐
         ▼                             ▼                             ▼
   ALL rows from               Same table related            Every possible
   BOTH tables                 to ITSELF                     combination
         │                             │                             │
         ▼                             ▼                             ▼
  FULL OUTER JOIN                  SELF JOIN                     CROSS JOIN
```

---

# Sample Reference Datasets (Used in Examples Below)

### 📥 Input Table A: `Employees` (`e`)
| id | name | dept_id |
|---|---|---|
| 1 | Alice | 10 |
| 2 | Bob | 20 |
| 3 | Charlie | 30 |
| 4 | David | NULL |

### 📥 Input Table B: `Departments` (`d`)
| id | dept_name |
|---|---|
| 10 | IT |
| 20 | HR |
| 40 | Finance |

---

# 1. INNER JOIN — Intersection ($A \cap B$)

⚡ **Memory Hook**: `INNER JOIN` keeps **ONLY** rows that match in **BOTH** tables. Unmatched rows are dropped.

```text
  Table A         Table B
┌─────────┐     ┌─────────┐
│         │ ┌─┐ │         │
│         │ │ ║ │         │   <── Only the middle intersection survives!
│         │ └─┘ │         │
└─────────┘     └─────────┘
```

### 💻 Query
```sql
SELECT e.name, d.dept_name
FROM Employees AS e
INNER JOIN Departments AS d
   ON e.dept_id = d.id;
```

### 📤 Output Table
| name | dept_name |
|---|---|
| Alice | IT |
| Bob | HR |

### 💡 Why did Charlie & David disappear?
- **Charlie** (`dept_id = 30`) has no matching `id = 30` in `Departments`.
- **David** (`dept_id = NULL`) has no match in `Departments`.
- **Finance** (`id = 40`) has no employee assigned.

---

# 2. LEFT JOIN — Preserve Left Table ($A + \text{matching } B$)

⚡ **Memory Hook**: `LEFT JOIN` keeps **EVERY SINGLE ROW** from the left table (`Employees`). If there is no match in the right table (`Departments`), right-side columns display `NULL`.

```text
  Table A (Left)     Table B (Right)
┌──────────────┐    ┌─────────┐
│              │ ┌─┐│         │
│  ALL ROWS    │ │ ││ MATCHES │   <── Left side preserved 100%!
│  SURVIVE     │ └─┘│  ONLY   │
└──────────────┘    └─────────┘
```

### 💻 Query
```sql
SELECT e.name, d.dept_name
FROM Employees AS e
LEFT JOIN Departments AS d
  ON e.dept_id = d.id;
```

### 📤 Output Table
| name | dept_name |
|---|---|
| Alice | IT |
| Bob | HR |
| Charlie | NULL |
| David | NULL |

### 💡 Why use LEFT JOIN?
Use `LEFT JOIN` whenever the problem says: *"Show all employees, along with their department names if available."*

---

# 3. RIGHT JOIN — Preserve Right Table ($\text{matching } A + B$)

⚡ **Memory Hook**: `RIGHT JOIN` keeps **EVERY SINGLE ROW** from the right table (`Departments`). Unmatched left-side attributes display `NULL`.

### 💻 Query
```sql
SELECT e.name, d.dept_name
FROM Employees AS e
RIGHT JOIN Departments AS d
  ON e.dept_id = d.id;
```

### 📤 Output Table
| name | dept_name |
|---|---|
| Alice | IT |
| Bob | HR |
| NULL | Finance |

> [!TIP]
> **Pro Tip**: In real-world SQL engineering, almost all developers write queries as `LEFT JOIN` by swapping table positions, because it reads more naturally left-to-right:
> ```sql
> -- Equivalent LEFT JOIN
> FROM Departments AS d
> LEFT JOIN Employees AS e ON d.id = e.dept_id
> ```

---

# 4. FULL OUTER JOIN — Complete Union ($A \cup B$)

⚡ **Memory Hook**: `FULL OUTER JOIN` keeps **EVERY ROW FROM BOTH TABLES**. Matches are linked; unmatched rows get `NULL` fillers on the missing side.

### 💻 Query
```sql
SELECT e.name, d.dept_name
FROM Employees AS e
FULL OUTER JOIN Departments AS d
  ON e.dept_id = d.id;
```

### 📤 Output Table
| name | dept_name |
|---|---|
| Alice | IT |
| Bob | HR |
| Charlie | NULL |
| David | NULL |
| NULL | Finance |

---

# 5. SELF JOIN — Table Related to Itself

⚡ **Memory Hook**: A table joined with itself using different table aliases (`e` for employee, `m` for manager).

### 📥 Input Table: `Employees`
| id | name | manager_id |
|---|---|---|
| 1 | Alice | NULL |
| 2 | Bob | 1 |
| 3 | Charlie | 1 |
| 4 | David | 2 |

### 💻 Query (Find each employee and their direct manager)
```sql
SELECT 
    e.name AS employee,
    m.name AS manager
FROM Employees AS e
LEFT JOIN Employees AS m
  ON e.manager_id = m.id;
```

### 📤 Output Table
| employee | manager |
|---|---|
| Alice | NULL |
| Bob | Alice |
| Charlie | Alice |
| David | Bob |

---

# 6. CROSS JOIN — Cartesian Product ($A \times B$)

⚡ **Memory Hook**: Pairs **every row** of Table A with **every row** of Table B. Result count = $\text{Rows}(A) \times \text{Rows}(B)$.

### 📥 Input Tables
Table `Colors`: [Red, Blue] (2 rows)  
Table `Sizes`: [S, M, L] (3 rows)

### 💻 Query
```sql
SELECT c.color, s.size
FROM Colors AS c
CROSS JOIN Sizes AS s;
```

### 📤 Output Table ($2 \times 3 = 6$ rows)
| color | size |
|---|---|
| Red | S |
| Red | M |
| Red | L |
| Blue | S |
| Blue | M |
| Blue | L |

---

# 7. CRITICAL GOTCHA: `ON` vs `WHERE` in `LEFT JOIN`

> [!CAUTION]
> Putting a filter in the `WHERE` clause can silently convert a `LEFT JOIN` into an `INNER JOIN`!

### 📥 Input Data
Employees: Alice (IT), Bob (HR), Charlie (No Dept)

### ❌ Scenario 1: Filter in `WHERE` clause
```sql
SELECT e.name, d.dept_name
FROM Employees AS e
LEFT JOIN Departments AS d ON e.dept_id = d.id
WHERE d.dept_name = 'IT';
```
**Result**:
| name | dept_name |
|---|---|
| Alice | IT |

*Why?* The `WHERE` clause runs **after** the JOIN. Because `d.dept_name` for Charlie is `NULL`, `NULL = 'IT'` evaluates to `UNKNOWN`, discarding Charlie!

---

### ✅ Scenario 2: Filter in `ON` clause
```sql
SELECT e.name, d.dept_name
FROM Employees AS e
LEFT JOIN Departments AS d ON e.dept_id = d.id AND d.dept_name = 'IT';
```
**Result**:
| name | dept_name |
|---|---|
| Alice | IT |
| Bob | NULL |
| Charlie | NULL |

*Why?* The `ON` clause condition controls **matching**, not row removal. Non-matching departments become `NULL`, preserving all employees!

---

# 8. JOIN + GROUP BY Pattern (Zero-Count Groups)

⚡ **Memory Hook**: To count items per group including groups with **0 items**, use `LEFT JOIN` + `COUNT(column)`.

> [!IMPORTANT]
> Always use `COUNT(e.id)` instead of `COUNT(*)` when counting right-table matches in a `LEFT JOIN`! `COUNT(*)` counts the row itself and will incorrectly return `1` for zero-match groups!

### 📥 Input Tables
Departments: `IT` (id: 10), `HR` (id: 20), `Sales` (id: 30)  
Employees: Alice (10), Bob (10), Charlie (20)

### 💻 Query
```sql
SELECT 
    d.dept_name,
    COUNT(e.id) AS employee_count
FROM Departments AS d
LEFT JOIN Employees AS e
  ON d.id = e.dept_id
GROUP BY d.dept_name;
```

### 📤 Output Table
| dept_name | employee_count |
|---|---|
| IT | 2 |
| HR | 1 |
| Sales | 0 |

---

# 9. SQL JOIN Pattern Matrix

| Problem Wording | Recommended JOIN | Output Characteristic |
|---|---|---|
| "Find records present in both tables" | `INNER JOIN` | Drops unmatched rows |
| "Show all main records, and secondary details if available" | `LEFT JOIN` | Unmatched secondary details become `NULL` |
| "Find records in Table A that have NO match in Table B" | `LEFT JOIN` + `WHERE B.key IS NULL` | Anti-join pattern |
| "Show every group even if count is 0" | `LEFT JOIN` + `GROUP BY` + `COUNT(B.id)` | Group count with zero handling |
| "Find employee-manager or parent-child hierarchy" | `SELF JOIN` | Join table to alias of itself |
| "Generate all possible pairings/combinations" | `CROSS JOIN` | $N \times M$ Cartesian product |
