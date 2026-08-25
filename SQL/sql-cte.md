# SQL Common Table Expressions (CTEs) & Advanced Pipeline Chaining

## 🎯 Core Mental Model

A **Common Table Expression (CTE)** is a temporary named result set defined using a `WITH` clause that exists only for the duration of a single query execution.

Think of a CTE in programming as declaring a temporary variable or modular helper function:
```cpp
// Programming analogy:
auto step1_clean_data = filterRawData();
auto step2_ranked_data = addRankings(step1_clean_data);
auto final_output = selectTop3(step2_ranked_data);
```

In SQL:
```sql
WITH Step1 AS (...),
     Step2 AS (...)
SELECT * FROM Step2;
```

---

# 1. Basic CTE Syntax vs Subquery

### 💻 Standard CTE Syntax
```sql
WITH CTEName AS (
    SELECT column1, column2
    FROM TableName
    WHERE condition
)
SELECT * 
FROM CTEName;
```

### 💡 Why CTEs Are Preferred Over Subqueries:
1. **Readability**: Code flows top-to-bottom instead of deeply nested inside-out subqueries.
2. **Reusability**: A CTE can be referenced multiple times within the main query (e.g. joined with itself).
3. **Debugging**: You can test individual CTE steps independently.

---

# 2. Creating Your Own Custom CTEs (Injecting Custom Rows)

Sometimes in interviews or production, you need to create a **custom temporary table with hardcoded rows** (e.g. injecting 3 test rows, creating a status lookup table, or generating missing category lists).

---

## 2.1 Method A: Using `UNION ALL` (Works in All SQL Databases)

⚡ **Memory Hook**: Stitch individual `SELECT` queries with constant values together using `UNION ALL`.

### 💻 Query (Creating 3 Custom Rows)
```sql
WITH CustomTierCTE AS (
    SELECT 1 AS tier_id, 'Entry Level' AS tier_name, 30000 AS min_salary, 50000 AS max_salary
    UNION ALL
    SELECT 2 AS tier_id, 'Mid Level'   AS tier_name, 50001 AS min_salary, 80000 AS max_salary
    UNION ALL
    SELECT 3 AS tier_id, 'Senior Level' AS tier_name, 80001 AS min_salary, 150000 AS max_salary
)
SELECT * 
FROM CustomTierCTE;
```

### 📤 Output Table
| tier_id | tier_name | min_salary | max_salary |
|---|---|---|---|
| 1 | Entry Level | 30000 | 50000 |
| 2 | Mid Level | 50001 | 80000 |
| 3 | Senior Level | 80001 | 150000 |

---

## 2.2 Method B: Using `VALUES` Constructor (MySQL 8.0+, PostgreSQL)

⚡ **Memory Hook**: Compact syntax using `VALUES (row1), (row2), (row3)`.

### 💻 Query
```sql
WITH CustomCategories (cat_id, cat_name) AS (
    VALUES 
        (1, 'Electronics'),
        (2, 'Clothing'),
        (3, 'Groceries')
)
SELECT cat_id, cat_name 
FROM CustomCategories;
```

### 📤 Output Table
| cat_id | cat_name |
|---|---|
| 1 | Electronics |
| 2 | Clothing |
| 3 | Groceries |

---

# 3. Multiple CTE Connections (Chaining CTEs)

⚡ **Memory Hook**: Separate multiple CTE definitions with a comma `,` under a single `WITH` keyword. Subsequent CTEs can reference previously defined CTEs!

```sql
WITH CTE_A AS ( ... ),
     CTE_B AS ( SELECT ... FROM CTE_A ... ),   -- References CTE_A!
     CTE_C AS ( SELECT ... FROM CTE_B ... )    -- References CTE_B!
SELECT * FROM CTE_C;
```

---

## 3.1 Real-World Chained Pipeline Example

> Problem: **"Find the department name and employee name of the highest-earning employee in departments located in 'Mumbai' or 'Delhi'."**

### 📥 Input Tables
`employees`: [Amit (70k, Dept 10), Priya (90k, Dept 10), Rahul (50k, Dept 20), Neha (60k, Dept 20)]  
`departments`: [Dept 10 (IT, Mumbai), Dept 20 (HR, Delhi)]

### 💻 Chained CTE Query
```sql
-- Step 1: Filter active departments in targeted cities
WITH TargetDepts AS (
    SELECT id, dept_name, location
    FROM departments
    WHERE location IN ('Mumbai', 'Delhi')
),

-- Step 2: Join employees with TargetDepts and compute DENSE_RANK()
RankedSalaries AS (
    SELECT 
        e.name AS emp_name,
        e.salary,
        d.dept_name,
        d.location,
        DENSE_RANK() OVER(PARTITION BY e.department_id ORDER BY e.salary DESC) AS rnk
    FROM employees AS e
    JOIN TargetDepts AS d 
      ON e.department_id = d.id
),

-- Step 3: Filter Top 1 earners per department
TopEarners AS (
    SELECT emp_name, dept_name, location, salary
    FROM RankedSalaries
    WHERE rnk = 1
)

-- Step 4: Final Output Selection
SELECT * FROM TopEarners;
```

### 📤 Output Table
| emp_name | dept_name | location | salary |
|---|---|---|---|
| Priya | IT | Mumbai | 90000 |
| Neha | HR | Delhi | 60000 |

---

# 4. Recursive CTEs (Sequence & Hierarchy Generation)

⚡ **Memory Hook**: A **Recursive CTE** references ITSELF to generate sequences (numbers 1 to N, dates, or organizational tree hierarchies).

### 📐 Recursive CTE Structure
```sql
WITH RECURSIVE NumberSeries AS (
    -- 1. Anchor Member (Initial base case row)
    SELECT 1 AS n
    
    UNION ALL
    
    -- 2. Recursive Member (Generates next row, referencing itself)
    SELECT n + 1 
    FROM NumberSeries
    WHERE n < 5 -- 3. Termination Condition
)
SELECT n FROM NumberSeries;
```

### 📤 Output Table
| n |
|---|
| 1 |
| 2 |
| 3 |
| 4 |
| 5 |

---

## 4.1 Real-World Recursive CTE: Generating Missing Date Ranges

> Problem: **"Generate all dates between August 1 and August 5, 2026."**

### 💻 Query
```sql
WITH RECURSIVE DateRange AS (
    SELECT CAST('2026-08-01' AS DATE) AS date_val
    UNION ALL
    SELECT DATE_ADD(date_val, INTERVAL 1 DAY)
    FROM DateRange
    WHERE date_val < '2026-08-05'
)
SELECT date_val FROM DateRange;
```

### 📤 Output Table
| date_val |
|---|
| 2026-08-01 |
| 2026-08-02 |
| 2026-08-03 |
| 2026-08-04 |
| 2026-08-05 |

---

# 5. Master CTE Pattern Recognition Cheat Sheet

| Use Case | CTE Pattern | Key Syntax |
|---|---|---|
| **Filter output of Window Functions** | Standard CTE | `WITH Ranked AS (SELECT ..., DENSE_RANK()...) SELECT * FROM Ranked WHERE rnk = 1` |
| **Inject custom test rows** | `UNION ALL` or `VALUES` | `WITH Custom AS (SELECT 1 AS id, 'A' AS val UNION ALL SELECT 2, 'B')` |
| **Multi-step data transformation pipeline** | Chained CTEs | `WITH Step1 AS (...), Step2 AS (SELECT ... FROM Step1)` |
| **Generate number or date series** | Recursive CTE | `WITH RECURSIVE Series AS (Base UNION ALL Recursive WHERE cond)` |
