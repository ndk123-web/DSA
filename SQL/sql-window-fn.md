# SQL Window Functions — Advanced Analytics Pattern Mastery

## 🎯 Core Mental Model: `GROUP BY` vs `WINDOW FUNCTIONS`

- **`GROUP BY`**: Collapses multiple rows into a single summary row per bucket. **Individual row identity is lost.**
- **`WINDOW FUNCTION`**: Performs calculations across a window (set) of related rows **WHILE RETAINING EVERY INDIVIDUAL ROW**.

```text
Input Rows                         GROUP BY department                 WINDOW FUNCTION: OVER(PARTITION BY department)
┌────────────────────────┐         ┌────────────────────────┐          ┌──────────────────────────────────────────────┐
│ Amit  | IT | 70000     │         │ IT | Avg Sal: 80000    │          │ Amit  | IT | 70000 | IT_Avg: 80000         │
│ Priya | IT | 90000     │ ──────► ├────────────────────────┤ ───────► │ Priya | IT | 90000 | IT_Avg: 80000         │
│ Rahul | HR | 50000     │         │ HR | Avg Sal: 55000    │          │ Rahul | HR | 50000 | HR_Avg: 55000         │
│ Neha  | HR | 60000     │         └────────────────────────┘          │ Neha  | HR | 60000 | HR_Avg: 55000         │
└────────────────────────┘                                             └──────────────────────────────────────────────┘
                                    (Rows Collapsed: 4 ──► 2)           (Rows Retained: 4 ──► 4, Extra Column Added)
```

---

## ⚡ Basic Syntax of `OVER()` Clause

```sql
FUNCTION() OVER (
    PARTITION BY partition_column   -- Optional: Defines window boundaries (like GROUP BY)
    ORDER BY sort_column             -- Optional: Sorts rows within each window
    ROWS/RANGE frame_specification   -- Optional: Defines dynamic sub-window frames
)
```

---

# Reference Dataset for Examples

### 📥 Input Table: `employees`
| id | name | department | salary | join_date |
|---|---|---|---|---|
| 101 | Amit | IT | 70000 | 2024-01-10 |
| 102 | Priya | IT | 90000 | 2024-02-15 |
| 103 | Arjun | IT | 90000 | 2024-03-01 |
| 104 | Rahul | HR | 50000 | 2024-01-20 |
| 105 | Neha | HR | 60000 | 2024-04-10 |

---

# 1. Ranking Window Functions

⚡ **Memory Hook**: Assigns ranks to rows within each partition based on sorting order.

| Function | Behavior on Ties (e.g. salaries 90k, 90k, 70k) | Sequence Output |
|---|---|---|
| **`ROW_NUMBER()`** | Ignores ties, assigns strictly unique sequential integers | `1, 2, 3, 4` |
| **`RANK()`** | Same rank for ties, **LEAVES GAPS** in next rank | `1, 1, 3, 4` |
| **`DENSE_RANK()`** | Same rank for ties, **NO GAPS** in next rank | `1, 1, 2, 3` |
| **`NTILE(N)`** | Distributes rows into $N$ equal buckets/quartiles | Bucket `1, 1, 2, 2` |

---

## 1.1 `ROW_NUMBER()` vs `RANK()` vs `DENSE_RANK()`

> Problem: **"Rank employees by salary within each department."**

### 💻 Query
```sql
SELECT 
    name,
    department,
    salary,
    ROW_NUMBER() OVER(PARTITION BY department ORDER BY salary DESC) AS row_num,
    RANK()       OVER(PARTITION BY department ORDER BY salary DESC) AS rnk,
    DENSE_RANK() OVER(PARTITION BY department ORDER BY salary DESC) AS dense_rnk
FROM employees;
```

### 📤 Output Table
| name | department | salary | row_num | rnk | dense_rnk |
|---|---|---|---|---|---|
| Priya | IT | 90000 | 1 | 1 | 1 |
| Arjun | IT | 90000 | 2 | 1 | 1 |
| Amit | IT | 70000 | 3 | 3 | 2 |
| Neha | HR | 60000 | 1 | 1 | 1 |
| Rahul | HR | 50000 | 2 | 2 | 2 |

> [!KEY TAKEAWAY]
> - Notice for **IT Department**: Priya & Arjun both have salary 90,000.
> - `RANK()` gives them both `1`, then skips to `3` for Amit.
> - `DENSE_RANK()` gives them both `1`, then goes to `2` for Amit.
> - **Interview Rule**: Use `DENSE_RANK()` when asked for *"Top N unique highest salaries"* (LeetCode 185)!

---

# 2. Navigation Window Functions (`LAG`, `LEAD`, `FIRST_VALUE`, `LAST_VALUE`)

⚡ **Memory Hook**: Allows querying values from previous or next rows **without self-joins**!

- **`LAG(col, offset, default)`**: Looks **BACKWARDS** $offset$ rows (default offset = 1).
- **`LEAD(col, offset, default)`**: Looks **FORWARDS** $offset$ rows (default offset = 1).
- **`FIRST_VALUE(col)`**: Returns first value in sorted window.
- **`LAST_VALUE(col)`**: Returns last value in sorted window.

---

## 2.1 `LAG()` & `LEAD()` — Day-over-Day or Row Differences

### 📥 Input Table: `daily_sales`
| sale_date | revenue |
|---|---|
| 2026-08-01 | 500 |
| 2026-08-02 | 700 |
| 2026-08-03 | 650 |
| 2026-08-04 | 900 |

> Problem: **"Calculate previous day revenue and daily revenue growth."**

### 💻 Query
```sql
SELECT 
    sale_date,
    revenue AS today_revenue,
    LAG(revenue, 1, 0) OVER(ORDER BY sale_date ASC) AS prev_day_revenue,
    revenue - LAG(revenue, 1, 0) OVER(ORDER BY sale_date ASC) AS revenue_growth,
    LEAD(revenue, 1, 0) OVER(ORDER BY sale_date ASC) AS next_day_revenue
FROM daily_sales;
```

### 📤 Output Table
| sale_date | today_revenue | prev_day_revenue | revenue_growth | next_day_revenue |
|---|---|---|---|---|
| 2026-08-01 | 500 | 0 | 500 | 700 |
| 2026-08-02 | 700 | 500 | +200 | 650 |
| 2026-08-03 | 650 | 700 | -50 | 900 |
| 2026-08-04 | 900 | 650 | +250 | 0 |

---

## 2.2 Consecutive Numbers Pattern (LeetCode 180 Pattern)

> Problem: **"Find all numbers that appear at least 3 times consecutively."**

### 📥 Input Table: `logs`
| id | num |
|---|---|
| 1 | 1 |
| 2 | 1 |
| 3 | 1 |
| 4 | 2 |
| 5 | 1 |

### 💻 Query (Using `LAG` & `LEAD`)
```sql
WITH ConsecutiveCTE AS (
    SELECT 
        num,
        LAG(num, 1) OVER(ORDER BY id) AS prev_num,
        LEAD(num, 1) OVER(ORDER BY id) AS next_num
    FROM logs
)
SELECT DISTINCT num AS ConsecutiveNums
FROM ConsecutiveCTE
WHERE num = prev_num AND num = next_num;
```

### 📤 Output Table
| ConsecutiveNums |
|---|
| 1 |

---

# 3. Aggregate Window Functions & Running Totals

⚡ **Memory Hook**: Performs `SUM()`, `AVG()`, `COUNT()` cumulatively or across partitions without collapsing rows.

---

## 3.1 Cumulative Sum / Running Total

> Problem: **"Calculate cumulative total sales per customer over time."**

### 📥 Input Table: `orders`
| order_id | customer_id | order_date | amount |
|---|---|---|---|
| 1 | 10 | 2026-01-01 | 100 |
| 2 | 10 | 2026-01-05 | 250 |
| 3 | 10 | 2026-01-10 | 150 |
| 4 | 20 | 2026-01-02 | 300 |
| 5 | 20 | 2026-01-08 | 400 |

### 💻 Query
```sql
SELECT 
    order_id,
    customer_id,
    order_date,
    amount,
    SUM(amount) OVER(
        PARTITION BY customer_id 
        ORDER BY order_date ASC
        ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
    ) AS running_total
FROM orders;
```

### 📤 Output Table
| order_id | customer_id | order_date | amount | running_total |
|---|---|---|---|---|
| 1 | 10 | 2026-01-01 | 100 | 100 |
| 2 | 10 | 2026-01-05 | 250 | 350 |
| 3 | 10 | 2026-01-10 | 150 | 500 |
| 4 | 20 | 2026-01-02 | 300 | 300 |
| 5 | 20 | 2026-01-08 | 400 | 700 |

---

## 3.2 Moving Average (3-Row Sliding Frame)

⚡ **Memory Hook**: `ROWS BETWEEN 2 PRECEDING AND CURRENT ROW` calculates average over current row + previous 2 rows.

### 💻 Query
```sql
SELECT 
    sale_date,
    revenue,
    ROUND(AVG(revenue) OVER(
        ORDER BY sale_date ASC
        ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
    ), 2) AS moving_3day_avg
FROM daily_sales;
```

---

# 4. Deep Dive: Window Frames & `OVER()` Variations

Understanding how `OVER()` behaves depending on which clauses are present is crucial for SQL interviews.

```text
OVER Clause Configuration                  Window Scope & Frame Behavior
─────────────────────────                  ─────────────────────────────────────────────────────
OVER ()                                ──► Entire table is 1 window. Fixed grand total for all rows.
OVER (PARTITION BY dept)               ──► Department window. Fixed department total for all rows.
OVER (ORDER BY date)                   ──► Entire table window + DEFAULT CUMULATIVE FRAME:
                                           RANGE BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW.
OVER (PARTITION BY dept ORDER BY date) ──► Department window + CUMULATIVE FRAME per department.
```

---

## 4.1 What Happens When You Omit `PARTITION BY`?

⚡ **Memory Hook**: If you omit `PARTITION BY`, SQL treats the **ENTIRE TABLE as one single window partition**.

### 💻 Case A: `OVER ()` (No `PARTITION BY`, No `ORDER BY`)
Computes the grand total / average across all rows and repeats it on every single row.

```sql
SELECT 
    name, 
    salary,
    SUM(salary) OVER () AS grand_total_salary,
    ROUND(salary * 100.0 / SUM(salary) OVER (), 2) AS pct_of_company_total
FROM employees;
```

### 📤 Output Table
| name | salary | grand_total_salary | pct_of_company_total |
|---|---|---|---|
| Amit | 70000 | 360000 | 19.44% |
| Priya | 90000 | 360000 | 25.00% |
| Arjun | 90000 | 360000 | 25.00% |
| Rahul | 50000 | 360000 | 13.89% |
| Neha | 60000 | 360000 | 16.67% |

---

## 4.2 What Happens When You Use ONLY `ORDER BY`? (The Default Cumulative Frame)

> [!IMPORTANT]
> When you add `ORDER BY` inside `OVER()` without specifying a window frame, SQL **automatically applies the default frame**:
> ```sql
> RANGE BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
> ```
> This causes aggregate functions like `SUM()`, `AVG()`, `COUNT()` to compute a **CUMULATIVE RUNNING TOTAL** row-by-row instead of a single total!

### 💻 Query
```sql
SELECT 
    id,
    join_date,
    salary,
    -- Simple OVER() = Total salary of entire table
    SUM(salary) OVER () AS total_salary_fixed,
    -- OVER(ORDER BY join_date) = CUMULATIVE running total over time
    SUM(salary) OVER (ORDER BY join_date ASC) AS running_total_salary
FROM employees;
```

### 📤 Output Table
| id | join_date | salary | total_salary_fixed | running_total_salary |
|---|---|---|---|---|
| 101 | 2024-01-10 | 70000 | 360000 | 70000 |
| 104 | 2024-01-20 | 50000 | 360000 | 120000 |
| 102 | 2024-02-15 | 90000 | 360000 | 210000 |
| 103 | 2024-03-01 | 90000 | 360000 | 300000 |
| 105 | 2024-04-10 | 60000 | 360000 | 360000 |

---

## 4.3 Window Frame Specification (`ROWS` vs `RANGE`)

⚡ **Memory Hook**: A **Window Frame** defines the exact subset of rows inside the partition used for calculation relative to the `CURRENT ROW`.

### 📐 Frame Boundary Keywords
- `UNBOUNDED PRECEDING` $\rightarrow$ First row of the partition.
- `N PRECEDING` $\rightarrow$ $N$ rows before the current row.
- `CURRENT ROW` $\rightarrow$ The current row.
- `N FOLLOWING` $\rightarrow$ $N$ rows after the current row.
- `UNBOUNDED FOLLOWING` $\rightarrow$ Last row of the partition.

```text
Visual Frame Architecture relative to CURRENT ROW:

┌─────────────────────────────────────────────────────────┐
│ UNBOUNDED PRECEDING  (First row of partition)          │
│ ...                                                     │
│ 2 PRECEDING          (2 rows back)                      │
│ 1 PRECEDING          (1 row back)                       │
│ ═══════════════════════════════════════════════════════ │
│ CURRENT ROW          (Active processing row)            │
│ ═══════════════════════════════════════════════════════ │
│ 1 FOLLOWING          (1 row ahead)                      │
│ 2 FOLLOWING          (2 rows ahead)                     │
│ ...                                                     │
│ UNBOUNDED FOLLOWING  (Last row of partition)           │
└─────────────────────────────────────────────────────────┘
```

---

## 4.4 `ROWS` vs `RANGE` — The Crucial Difference on Duplicate Values

- **`ROWS`**: Operates on **exact physical row numbers**.
- **`RANGE`**: Operates on **value ranges**. If two rows have identical `ORDER BY` values (ties), `RANGE` treats them as a single logical unit!

### 📥 Example Table: `sales` (Duplicate dates on 2026-08-01)
| sale_date | amount |
|---|---|
| 2026-08-01 | 100 |
| 2026-08-01 | 100 |
| 2026-08-02 | 200 |

### 💻 Query
```sql
SELECT 
    sale_date,
    amount,
    -- ROWS: Adds exact row-by-row
    SUM(amount) OVER(ORDER BY sale_date ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS rows_running_total,
    -- RANGE: Includes ALL duplicate order dates in the current calculation step!
    SUM(amount) OVER(ORDER BY sale_date RANGE BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS range_running_total
FROM sales;
```

### 📤 Output Table
| sale_date | amount | rows_running_total | range_running_total |
|---|---|---|---|
| 2026-08-01 | 100 | 100 | **200** |
| 2026-08-01 | 100 | **200** | **200** |
| 2026-08-02 | 200 | 400 | 400 |

> [!CAUTION]
> Because `RANGE` includes all ties on the same date at once, the running total for both rows on `2026-08-01` jumps straight to `200`! If you want strict row-by-row incremental addition, **ALWAYS explicitly specify `ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW`**!

---

# 5. CRITICAL GOTCHA: Window Functions in `WHERE` Clause

> [!CAUTION]
> Window functions are executed **AFTER `WHERE`, `GROUP BY`, and `HAVING`** in the logical processing pipeline.
> **You CANNOT write**: `WHERE ROW_NUMBER() OVER(...) = 1` directly!

### ❌ WRONG Query
```sql
-- FAILS WITH SYNTAX ERROR!
SELECT name, department, salary
FROM employees
WHERE DENSE_RANK() OVER(PARTITION BY department ORDER BY salary DESC) <= 2;
```

### ✅ CORRECT Query (Wrapped in a CTE / Subquery)
```sql
WITH RankedEmployees AS (
    SELECT 
        name, 
        department, 
        salary,
        DENSE_RANK() OVER(PARTITION BY department ORDER BY salary DESC) AS rnk
    FROM employees
)
SELECT name, department, salary
FROM RankedEmployees
WHERE rnk <= 2;
```

---

# 6. Master Window Function Pattern Matrix

| Problem Wording Keyword | Window Function Technique | Core Pattern / Formula |
|---|---|---|
| *"Grand total on every row / Percentage of total"* | `OVER ()` | `val * 100.0 / SUM(val) OVER()` |
| *"Cumulative total / Running sum over time"* | `OVER (ORDER BY date)` | `SUM(val) OVER (ORDER BY date)` (Default `RANGE` frame) |
| *"Strict incremental running total with ties"* | `OVER (... ROWS BETWEEN ...)` | `SUM(val) OVER (ORDER BY date ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW)` |
| *"Highest paid employee per department"* | `DENSE_RANK()` / `ROW_NUMBER()` | `DENSE_RANK() OVER(PARTITION BY dept ORDER BY sal DESC)` |
| *"Top 3 unique salaries"* | `DENSE_RANK()` + `CTE` | `WHERE rnk <= 3` (No skipped rank numbers) |
| *"Difference compared to previous row / yesterday"* | `LAG()` | `val - LAG(val, 1) OVER(ORDER BY date)` |
| *"Value of next row"* | `LEAD()` | `LEAD(val, 1) OVER(ORDER BY date)` |
| *"3 consecutive identical records"* | `LAG()` & `LEAD()` | `WHERE val = LAG(val) AND val = LEAD(val)` |
| *"Moving 7-day average"* | `AVG() OVER(ROWS BETWEEN)` | `AVG(amt) OVER(ORDER BY date ROWS BETWEEN 6 PRECEDING AND CURRENT ROW)` |
