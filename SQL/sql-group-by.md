# SQL Aggregation — GROUP BY, Aggregations & HAVING Pipeline

## 🎯 The Core Mental Model: Bucketing

In programming/DSA, `GROUP BY` is equivalent to grouping items into a Hash Map of Buckets:

$$\text{unordered\_map}<\text{GroupKey}, \text{vector}<\text{Row}>>$$

```text
Raw Rows                   GROUP BY department           Aggregate Function: COUNT(*) / AVG()
┌──────────────┐          ┌─────────────────────────┐          ┌───────────────────────────┐
│ Amit  | IT   │          │ IT Group                │          │ IT  ──► 3 employees       │
│ Priya | IT   │ ───────► │ [Amit, Priya, Arjun]    │ ───────► │       ──► Avg Sal: 80000  │
│ Rahul | HR   │          ├─────────────────────────┤          ├───────────────────────────┤
│ Neha  | HR   │          │ HR Group                │          │ HR  ──► 2 employees       │
│ Arjun | IT   │          │ [Rahul, Neha]           │          │       ──► Avg Sal: 55000  │
└──────────────┘          └─────────────────────────┘          └───────────────────────────┘
```

> [!KEY TAKEAWAY]
> **`GROUP BY` does NOT calculate anything by itself.** It only creates the buckets. Aggregate functions (`COUNT`, `SUM`, `AVG`, `MIN`, `MAX`) compute values *inside* each bucket.

---

## ⚡ Logical Query Execution Order

```text
Syntax Order (How You Write It)         Logical Processing Order (How SQL Executes It)
───────────────────────────────         ──────────────────────────────────────────────────
1. SELECT                               1. FROM             ──► Fetch base source table(s)
2. FROM                                 2. JOIN + ON        ──► Stitch related tables together
3. JOIN + ON                            3. WHERE            ──► Filter individual ROWS (Pre-grouping)
4. WHERE                                4. GROUP BY         ──► Partition rows into BUCKETS
5. GROUP BY                             5. HAVING           ──► Filter BUCKETS/GROUPS
6. HAVING                               6. Window Functions ──► Compute ranks, lags & totals
7. Window Functions                     7. SELECT           ──► Project & compute final columns
8. DISTINCT                             8. DISTINCT         ──► Remove duplicate result rows
9. ORDER BY                             9. ORDER BY         ──► Sort final output rows
10. LIMIT                              10. LIMIT            ──► Restrict number of returned rows
```

---

# Reference Dataset for Examples

### 📥 Input Table: `employees`
| id | name | department | salary | manager_id |
|---|---|---|---|---|
| 1 | Amit | IT | 70000 | 3 |
| 2 | Priya | IT | 90000 | 3 |
| 3 | Rahul | HR | 50000 | NULL |
| 4 | Neha | HR | 60000 | 3 |
| 5 | Arjun | IT | 80000 | 3 |

---

# 1. Aggregations Without GROUP BY

⚡ **Memory Hook**: When used without `GROUP BY`, aggregate functions treat the **ENTIRE TABLE as one single bucket**.

### 💻 Query
```sql
SELECT 
    COUNT(*) AS total_employees,
    SUM(salary) AS total_payroll,
    AVG(salary) AS avg_salary,
    MIN(salary) AS lowest_salary,
    MAX(salary) AS highest_salary
FROM employees;
```

### 📤 Output Table
| total_employees | total_payroll | avg_salary | lowest_salary | highest_salary |
|---|---|---|---|---|
| 5 | 350000 | 70000 | 50000 | 90000 |

---

# 2. GROUP BY + COUNT(*)

⚡ **Memory Hook**: Counts the number of rows in each bucket.

> Keyword cue: **"For each department, find the number of employees."**

### 💻 Query
```sql
SELECT department, COUNT(*) AS employee_count
FROM employees
GROUP BY department;
```

### 📤 Output Table
| department | employee_count |
|---|---|
| IT | 3 |
| HR | 2 |

---

# 3. GROUP BY + AVG() / SUM() / MIN() / MAX()

⚡ **Memory Hook**: Calculates mathematical metrics inside each bucket.

### 💻 Query
```sql
SELECT 
    department,
    SUM(salary) AS total_salary,
    AVG(salary) AS avg_salary,
    MIN(salary) AS min_salary,
    MAX(salary) AS max_salary
FROM employees
GROUP BY department;
```

### 📤 Output Table
| department | total_salary | avg_salary | min_salary | max_salary |
|---|---|---|---|---|
| IT | 240000 | 80000 | 70000 | 90000 |
| HR | 110000 | 55000 | 50000 | 60000 |

---

# 4. COUNT(*) vs COUNT(column) vs COUNT(DISTINCT column)

> [!WARNING]
> - `COUNT(*)` counts **ALL rows** in the group, regardless of `NULL`s.
> - `COUNT(column)` counts **NON-NULL values** in that specific column.
> - `COUNT(DISTINCT column)` counts **UNIQUE non-NULL values**.

### 📥 Input Table: `employees`
| id | department | manager_id |
|---|---|---|
| 1 | IT | 3 |
| 2 | IT | 3 |
| 3 | HR | NULL |
| 4 | HR | 3 |
| 5 | IT | 3 |

### 💻 Query
```sql
SELECT 
    department,
    COUNT(*) AS total_rows,
    COUNT(manager_id) AS non_null_managers,
    COUNT(DISTINCT manager_id) AS unique_managers
FROM employees
GROUP BY department;
```

### 📤 Output Table
| department | total_rows | non_null_managers | unique_managers |
|---|---|---|---|
| IT | 3 | 3 | 1 |
| HR | 2 | 1 | 1 |

---

# 5. Multi-Column GROUP BY

⚡ **Memory Hook**: `GROUP BY A, B` creates buckets for every unique combination of `(A, B)`.

### 📥 Input Table: `sales`
| country | product | amount |
|---|---|---|
| India | Laptop | 50000 |
| India | Laptop | 30000 |
| India | Phone | 20000 |
| USA | Laptop | 70000 |
| USA | Phone | 40000 |

### 💻 Query
```sql
SELECT country, product, SUM(amount) AS total_sales
FROM sales
GROUP BY country, product;
```

### 📤 Output Table
| country | product | total_sales |
|---|---|---|
| India | Laptop | 80000 |
| India | Phone | 20000 |
| USA | Laptop | 70000 |
| USA | Phone | 40000 |

---

# 6. WHERE vs HAVING — Crucial Interview Distinction

```text
WHERE  ──► Filters individual ROWS BEFORE grouping (Cannot use aggregate functions)
HAVING ──► Filters BUCKETS/GROUPS AFTER aggregation (Uses aggregate functions)
```

### ❌ WRONG Query (Using Aggregates in WHERE)
```sql
-- FAILS! WHERE runs BEFORE AVG(salary) is calculated!
SELECT department, AVG(salary)
FROM employees
WHERE AVG(salary) > 60000
GROUP BY department;
```

### ✅ CORRECT Query (Using HAVING)
```sql
SELECT department, AVG(salary) AS avg_sal
FROM employees
GROUP BY department
HAVING AVG(salary) > 60000;
```

### 📤 Output Table
| department | avg_sal |
|---|---|
| IT | 80000 |

---

# 7. Combining WHERE + GROUP BY + HAVING

> Problem: **"Find departments whose average salary is > 60,000, considering ONLY employees earning at least 60,000."**

### 🧠 Pattern Step-by-Step Pipeline:
1. `WHERE salary >= 60000` ──► Filters individual employee rows first.
2. `GROUP BY department` ──► Buckets surviving employees by department.
3. `HAVING AVG(salary) > 60000` ──► Filters out department buckets with avg $\le 60000$.

### 💻 Query
```sql
SELECT department, COUNT(*) AS emp_count, AVG(salary) AS avg_sal
FROM employees
WHERE salary >= 60000
GROUP BY department
HAVING AVG(salary) > 60000;
```

### 📤 Output Table Execution Flow

**Step 1: Raw Table (`FROM employees`)** — 5 rows  
**Step 2: Filter Rows (`WHERE salary >= 60000`)**: Drops Rahul (50k). Remaining rows: Amit (70k), Priya (90k), Neha (60k), Arjun (80k).  
**Step 3: Buckets (`GROUP BY department`)**: 
- IT: [70k, 90k, 80k] $\rightarrow$ Avg = 80,000, Count = 3
- HR: [60k] $\rightarrow$ Avg = 60,000, Count = 1  
**Step 4: Filter Buckets (`HAVING AVG(salary) > 60000`)**: HR bucket (60,000) is filtered out because $60000 \ngtr 60000$.

### Final Output:
| department | emp_count | avg_sal |
|---|---|---|
| IT | 3 | 80000 |

---

# 8. GROUP BY + LEFT JOIN (Zero-Count Group Pattern)

⚡ **Memory Hook**: When joining tables to count records per group, use `LEFT JOIN` + `COUNT(right_table.primary_key)` so zero-match groups show a count of `0` instead of disappearing!

### 📥 Input Tables
`Departments`: `IT` (id: 10), `HR` (id: 20), `Sales` (id: 30)  
`Employees`: Amit (10), Priya (10), Rahul (20)

### 💻 Query
```sql
SELECT 
    d.department,
    COUNT(e.id) AS employee_count
FROM Departments AS d
LEFT JOIN Employees AS e
  ON d.id = e.dept_id
GROUP BY d.department;
```

### 📤 Output Table
| department | employee_count |
|---|---|
| IT | 2 |
| HR | 1 |
| Sales | 0 |

> [!CAUTION]
> If you used `COUNT(*)` here, `Sales` would incorrectly show `1` because the joined row `Sales | NULL` counts as 1 row! Using `COUNT(e.id)` correctly counts `0` because `e.id` is `NULL`.

---

# 9. Complete Master Pipeline Example

> Problem: **"Find the top 2 departments by average salary among employees with salary > 50,000, considering only departments with more than 1 such employee."**

### 💻 Query
```sql
SELECT 
    department,
    COUNT(*) AS total_staff,
    AVG(salary) AS avg_salary
FROM employees
WHERE salary > 50000
GROUP BY department
HAVING COUNT(*) > 1
ORDER BY avg_salary DESC
LIMIT 2;
```

### 📤 Output Table
| department | total_staff | avg_salary |
|---|---|---|
| IT | 3 | 80000 |

---

# 10. Aggregation & GROUP BY Pattern Matrix

| Problem Wording Keyword | SQL Clause / Function | Quick Mental Model |
|---|---|---|
| "For each X" / "Per X" | `GROUP BY X` | Bucket rows by X |
| "Total count of records" | `COUNT(*)` | Count rows |
| "Count of non-null values" | `COUNT(column)` | Skip NULLs |
| "Count unique values" | `COUNT(DISTINCT column)` | Deduplicated count |
| "Filter rows BEFORE grouping" | `WHERE condition` | Row filter |
| "Filter groups AFTER aggregation" | `HAVING aggregate_cond` | Bucket filter |
| "Show 0 count for missing categories" | `LEFT JOIN` + `COUNT(right.pk)` | Zero-count handling |
| "Top N groups by metric" | `GROUP BY ... ORDER BY metric DESC LIMIT N` | Aggregated Top-K |
