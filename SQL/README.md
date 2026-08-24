# SQL Pattern Mastery & Execution Engine Architecture

> **Master Guide**: Complete SQL Query Execution Pipeline & SQL Study Roadmap.

---

## ⚡ The Master SQL Logical Execution Pipeline

When writing SQL, you write in **Syntax Order**. But the SQL Database Engine processes your query in **Logical Execution Order**:

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

### 🧠 Flowchart Visualization

```text
       ┌───────────┐
       │   FROM    │ ──► Pick base source table(s)
       └─────┬─────┘
             │
             ▼
       ┌───────────┐
       │ JOIN + ON │ ──► Connect matching keys across tables
       └─────┬─────┘
             │
             ▼
       ┌───────────┐
       │   WHERE   │ ──► Row-by-row filtering BEFORE grouping
       └─────┬─────┘
             │
             ▼
       ┌───────────┐
       │ GROUP BY  │ ──► Partition rows into group buckets
       └─────┬─────┘
             │
             ▼
       ┌───────────┐
       │  HAVING   │ ──► Group-level filtering AFTER aggregation
       └─────┬─────┘
             │
             ▼
┌───────────────────────┐
│   Window Functions    │ ──► Compute RANK(), DENSE_RANK(), LAG(), LEAD(), SUM() OVER()
└────────────┬──────────┘
             │
             ▼
       ┌───────────┐
       │  SELECT   │ ──► Compute final expressions & aliases
       └─────┬─────┘
             │
             ▼
       ┌───────────┐
       │ DISTINCT  │ ──► Deduplicate final output rows
       └─────┬─────┘
             │
             ▼
       ┌───────────┐
       │ ORDER BY  │ ──► Sort final result set
       └─────┬─────┘
             │
             ▼
       ┌───────────┐
       │   LIMIT   │ ──► Restrict maximum output row count
       └───────────┘
```

---

## 💡 Why This Execution Order Matters (Crucial Interview Rules)

1. **Why `WHERE` cannot use Column Aliases or Aggregate Functions**:
   - `WHERE` executes **BEFORE** `SELECT` (so aliases don't exist yet) and **BEFORE** `GROUP BY` (so aggregates haven't been computed).
2. **Why `HAVING` filters Groups while `WHERE` filters Rows**:
   - `WHERE` runs at step 3 (row level). `HAVING` runs at step 5 (group level after `GROUP BY`).
3. **Why Window Functions CANNOT be placed in `WHERE` or `HAVING`**:
   - Window functions execute at step 6, **AFTER** `HAVING`. To filter by a window function output (e.g. `WHERE rnk <= 3`), you **MUST** wrap the query in a **CTE** or Subquery!
4. **Why `SELECT` Column Aliases can be used in `ORDER BY`**:
   - `ORDER BY` executes at step 9, **AFTER** `SELECT` (step 7) has evaluated all column aliases.

---

## 📚 SQL Topic Cheat Sheets Roadmap

| Topic File | Core Concepts Covered |
|---|---|
| 📘 **[sql-learning.md](file:///d:/DSA/SQL/sql-learning.md)** | `SELECT`, `WHERE`, `IN`, `BETWEEN`, `LIKE`, `NULL` logic, `ORDER BY`, `LIMIT/OFFSET` |
| 🔗 **[sql-joins.md](file:///d:/DSA/SQL/sql-joins.md)** | `INNER`, `LEFT`, `RIGHT`, `FULL OUTER`, `SELF`, `CROSS` JOINs, `ON` vs `WHERE` |
| 📊 **[sql-group-by.md](file:///d:/DSA/SQL/sql-group-by.md)** | `COUNT`, `SUM`, `AVG`, `MIN`, `MAX`, `GROUP BY`, `HAVING`, Zero-count handling |
| ⚡ **[sql-subquries.md](file:///d:/DSA/SQL/sql-subquries.md)** | Subqueries (Scalar, `IN`, Derived `FROM`, Correlated), `CASE WHEN`, `ROUND`, `SUM` |
| 🪟 **[sql-window-fn.md](file:///d:/DSA/SQL/sql-window-fn.md)** | `OVER()`, `PARTITION BY`, `ROW_NUMBER`, `RANK`, `DENSE_RANK`, `LAG`, `LEAD`, Cumulative `SUM` |
| 📅 **[sql-datetime-oprs.md](file:///d:/DSA/SQL/sql-datetime-oprs.md)** | `YEAR`, `MONTH`, `DATE_FORMAT`, `DATE_ADD`, `DATE_SUB`, `DATEDIFF`, Date Range filtering |
| 🔢 **[sql-datatype-oprs.md](file:///d:/DSA/SQL/sql-datatype-oprs.md)** | String ops (`LENGTH`, `SUBSTRING`, `CONCAT`), Numeric ops, `COALESCE`, `NULLIF`, `CAST` |
