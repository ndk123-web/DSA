# SQL Subqueries, CASE Statements, ROUND & Advanced SUM Patterns

## 🎯 Core Mental Model

In SQL, queries can be nested and combined dynamically:
- **Subquery**: A query inside another query ($Query \subseteq Query$).
- **CASE**: The `if-else` branching logic of SQL.
- **ROUND**: Formats numeric output to exact decimal precision.
- **SUM (Global vs Grouped vs Conditional)**: Totals across the entire table vs within buckets vs filtered conditions.

---

# 1. Subqueries (Queries Inside Queries)

A **Subquery** (or Inner Query) is a `SELECT` query nested inside a `WHERE`, `FROM`, or `SELECT` clause of an Outer Query.

```text
┌─────────────────────────────────────────────────────────┐
│ Outer Query                                             │
│   SELECT ... FROM ... WHERE column OP                   │
│   ┌─────────────────────────────────────────────────┐   │
│   │ Inner Subquery (Executes first or per row)      │   │
│   │ SELECT ... FROM ...                             │   │
│   └─────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────┘
```

---

## Sample Dataset: `employees` & `departments`

### 📥 Input Table A: `employees`
| id | name | department_id | salary |
|---|---|---|---|
| 1 | Amit | 10 | 70000 |
| 2 | Priya | 10 | 90000 |
| 3 | Rahul | 20 | 50000 |
| 4 | Neha | 20 | 60000 |
| 5 | Vikram | 30 | 45000 |

### 📥 Input Table B: `departments`
| id | dept_name | location |
|---|---|---|
| 10 | IT | Mumbai |
| 20 | HR | Delhi |
| 30 | Sales | Bangalore |

---

## 1.1 Scalar Subquery (Single Value Return)

⚡ **Memory Hook**: A **Scalar Subquery** returns exactly ONE row and ONE column (a single value like a number or string). It can be used anywhere a constant value is expected (`=`, `>`, `<`, etc.).

> Problem: **"Find employees earning more than the company average salary."**

### 💻 Query
```sql
SELECT name, salary
FROM employees
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
);
```

### 📤 Step-by-Step Execution
1. Inner subquery runs: `SELECT AVG(salary) FROM employees` $\rightarrow$ `63000`.
2. Outer query runs: `WHERE salary > 63000`.

### 📤 Output Table
| name | salary |
|---|---|
| Amit | 70000 |
| Priya | 90000 |

---

## 1.2 Multi-Row Subquery with `IN` / `NOT IN`

⚡ **Memory Hook**: Returns a list/set of values. Used with `IN` ($x \in \{v_1, v_2, \dots\}$) or `NOT IN`.

> Problem: **"Find employees working in departments located in Mumbai or Delhi."**

### 💻 Query
```sql
SELECT name, salary
FROM employees
WHERE department_id IN (
    SELECT id
    FROM departments
    WHERE location IN ('Mumbai', 'Delhi')
);
```

### 📤 Output Table
| name | salary |
|---|---|
| Amit | 70000 |
| Priya | 90000 |
| Rahul | 50000 |
| Neha | 60000 |

> [!CAUTION]
> **CRITICAL GOTCHA WITH `NOT IN` & `NULL`s**:
> If the inner subquery returns even a SINGLE `NULL` value (e.g. `[10, 20, NULL]`), `val NOT IN (10, 20, NULL)` will evaluate to `UNKNOWN` for ALL rows and return **0 rows**!
> **Rule**: Always add `WHERE col IS NOT NULL` inside a `NOT IN` subquery or use `NOT EXISTS`!

---

## 1.3 Subqueries in `FROM` Clause (Derived Tables)

⚡ **Memory Hook**: Treats the result of an inner subquery as a temporary virtual table.

> [!IMPORTANT]
> In SQL, any subquery in the `FROM` clause **MUST be given a table alias** (e.g., `AS dept_summary`).

> Problem: **"Find departments whose total payroll is greater than 100,000."**

### 💻 Query
```sql
SELECT department_id, total_payroll
FROM (
    SELECT department_id, SUM(salary) AS total_payroll
    FROM employees
    GROUP BY department_id
) AS dept_summary
WHERE total_payroll > 100000;
```

### 📤 Output Table
| department_id | total_payroll |
|---|---|
| 10 | 160000 |
| 20 | 110000 |

---

## 1.4 Correlated Subquery & `EXISTS` / `NOT EXISTS`

⚡ **Memory Hook**:
- A **Correlated Subquery** references a column from the **Outer Query** (`e.department_id`). It re-executes **for every single row** evaluated by the outer query.
- `EXISTS` returns `TRUE` as soon as the inner query finds at least one matching record.

> Problem: **"Find employees earning more than the average salary of THEIR OWN department."**

### 💻 Query
```sql
SELECT e.name, e.salary, e.department_id
FROM employees AS e
WHERE e.salary > (
    SELECT AVG(salary)
    FROM employees
    WHERE department_id = e.department_id
);
```

### 📤 Output Table Execution
- For Amit (Dept 10, Sal 70k): Dept 10 Avg = 80k $\rightarrow$ $70k \ngtr 80k$ (No)
- For Priya (Dept 10, Sal 90k): Dept 10 Avg = 80k $\rightarrow$ $90k > 80k$ (Yes)
- For Rahul (Dept 20, Sal 50k): Dept 20 Avg = 55k $\rightarrow$ $50k \ngtr 55k$ (No)
- For Neha (Dept 20, Sal 60k): Dept 20 Avg = 55k $\rightarrow$ $60k > 55k$ (Yes)

### 📤 Output Table
| name | salary | department_id |
|---|---|---|
| Priya | 90000 | 10 |
| Neha | 60000 | 20 |

---

# 2. `CASE` Statements (Conditional Branching)

⚡ **Memory Hook**: `CASE` is SQL's `if-else` expression. It evaluates conditions in order and returns a value when the first condition is `TRUE`.

### 📐 Syntax Structure
```sql
CASE 
    WHEN condition1 THEN result1
    WHEN condition2 THEN result2
    ELSE fallback_result
END
```

> [!WARNING]
> Do NOT forget the `END` keyword! Omitting `END` is a common syntax error.

---

## 2.1 Categorizing Rows into Labels

> Problem: **"Categorize employees into 'High', 'Medium', or 'Low' salary tiers."**

### 💻 Query
```sql
SELECT 
    name,
    salary,
    CASE 
        WHEN salary >= 80000 THEN 'High Salary'
        WHEN salary >= 60000 THEN 'Medium Salary'
        ELSE 'Low Salary'
    END AS salary_tier
FROM employees;
```

### 📤 Output Table
| name | salary | salary_tier |
|---|---|---|
| Amit | 70000 | Medium Salary |
| Priya | 90000 | High Salary |
| Rahul | 50000 | Low Salary |
| Neha | 60000 | Medium Salary |
| Vikram | 45000 | Low Salary |

---

## 2.2 Conditional Aggregation (`SUM` or `COUNT` with `CASE`)

⚡ **Memory Hook**: Combining `SUM(CASE WHEN ... THEN 1 ELSE 0 END)` allows you to **pivot rows into columns** or count specific conditions in a single query!

### 📥 Input Table: `orders`
| order_id | customer_id | status | amount |
|---|---|---|---|
| 101 | 1 | COMPLETED | 500 |
| 102 | 1 | CANCELLED | 200 |
| 103 | 2 | COMPLETED | 1200 |
| 104 | 1 | COMPLETED | 300 |
| 105 | 2 | PENDING | 150 |

> Problem: **"For each customer, count total orders, completed orders, and cancelled orders."**

### 💻 Query
```sql
SELECT 
    customer_id,
    COUNT(*) AS total_orders,
    SUM(CASE WHEN status = 'COMPLETED' THEN 1 ELSE 0 END) AS completed_orders,
    SUM(CASE WHEN status = 'CANCELLED' THEN 1 ELSE 0 END) AS cancelled_orders
FROM orders
GROUP BY customer_id;
```

### 📤 Output Table
| customer_id | total_orders | completed_orders | cancelled_orders |
|---|---|---|---|
| 1 | 3 | 2 | 1 |
| 2 | 2 | 1 | 0 |

---

# 3. `ROUND()` Function

⚡ **Memory Hook**: `ROUND(numeric_value, decimal_places)` rounds numbers to specified decimal precision.

### 📐 Usage Syntax
- `ROUND(123.4567, 2)` $\rightarrow$ `123.46`
- `ROUND(123.4567, 0)` $\rightarrow$ `123`
- `ROUND(AVG(salary), 2)` $\rightarrow$ Formats calculated averages to 2 decimal places.

### 💻 Query
```sql
SELECT 
    department_id,
    AVG(salary) AS raw_average,
    ROUND(AVG(salary), 2) AS rounded_average,
    ROUND(AVG(salary), 0) AS rounded_integer
FROM employees
GROUP BY department_id;
```

### 📤 Output Table
| department_id | raw_average | rounded_average | rounded_integer |
|---|---|---|---|
| 10 | 80000.0000 | 80000.00 | 80000 |
| 20 | 55000.0000 | 55000.00 | 55000 |
| 30 | 45000.0000 | 45000.00 | 45000 |

---

# 4. `SUM()` — Normal vs `GROUP BY` vs Conditional SUM

⚡ **Memory Hook**:
1. **Normal `SUM()`**: 1 overall table-wide scalar sum.
2. **`SUM()` + `GROUP BY`**: Group-wise totals.
3. **`SUM()` + `CASE`**: Conditional sum (sums values ONLY if condition is met).

### 📥 Input Table: `sales`
| region | category | revenue |
|---|---|---|
| East | Electronics | 5000 |
| East | Clothing | 2000 |
| West | Electronics | 8000 |
| West | Clothing | 3000 |
| East | Electronics | 1500 |

---

## 4.1 Normal `SUM()` vs `GROUP BY SUM()`

### 💻 Query 1: Normal `SUM()` (Entire Table)
```sql
SELECT SUM(revenue) AS grand_total_revenue
FROM sales;
```
**Output**: `19500`

---

### 💻 Query 2: `SUM()` + `GROUP BY` (By Region)
```sql
SELECT region, SUM(revenue) AS regional_revenue
FROM sales
GROUP BY region;
```

### 📤 Output Table
| region | regional_revenue |
|---|---|
| East | 8500 |
| West | 11000 |

---

## 4.2 Conditional `SUM()` with `CASE` (Pivoting Data)

> Problem: **"Find total Electronics revenue and total Clothing revenue per region in columns."**

### 💻 Query
```sql
SELECT 
    region,
    SUM(CASE WHEN category = 'Electronics' THEN revenue ELSE 0 END) AS electronics_revenue,
    SUM(CASE WHEN category = 'Clothing' THEN revenue ELSE 0 END) AS clothing_revenue,
    SUM(revenue) AS total_revenue
FROM sales
GROUP BY region;
```

### 📤 Output Table
| region | electronics_revenue | clothing_revenue | total_revenue |
|---|---|---|---|
| East | 6500 | 2000 | 8500 |
| West | 8000 | 3000 | 11000 |

---

# 5. Master Pattern Recognition Cheat Sheet

| English Problem Keyword | SQL Technique | Core Pattern |
|---|---|---|
| *"Compared to average / max of table"* | Scalar Subquery | `WHERE col > (SELECT AVG(...) FROM table)` |
| *"In a specific list of matching IDs"* | `IN` Subquery | `WHERE id IN (SELECT id FROM ...)` |
| *"Excluding list of matching IDs"* | `NOT IN` / `NOT EXISTS` | `WHERE id NOT IN (SELECT id FROM ... WHERE id IS NOT NULL)` |
| *"Comparing each row against its group aggregate"* | Correlated Subquery | `WHERE col > (SELECT AVG(...) FROM table WHERE dept = e.dept)` |
| *"If X then A else B"* | `CASE WHEN` | `CASE WHEN cond THEN val ELSE fallback END` |
| *"Count/Sum specific status into separate columns"* | Conditional Aggregation | `SUM(CASE WHEN status = 'X' THEN 1 ELSE 0 END)` |
| *"Format average to 2 decimal places"* | `ROUND()` | `ROUND(AVG(col), 2)` |
| *"Sum values satisfying condition per group"* | `SUM(CASE WHEN ...)` | `SUM(CASE WHEN cond THEN val ELSE 0 END) + GROUP BY` |
