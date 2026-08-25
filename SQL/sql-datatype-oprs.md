# SQL Data Types & Type-Specific Operations

## 🎯 Core Mental Model

Every column in a database table has a **Data Type**. The data type dictates:
1. **What kind of data** is stored (Text, Number, Date, Boolean).
2. **Which operations and SQL functions** can be applied.

```text
Problem Wording ──► Identify Data Type ──► Select Allowed Operations ──► Apply SQL Function
```

---

# 1. Character & String Operations

Common types: `VARCHAR(n)` (variable text), `CHAR(n)` (fixed-width text), `TEXT` (large text).

### 📥 Input Table: `users`
| id | full_name | email | status |
|---|---|---|---|
| 1 |  Amit Sharma  | amit@oldcompany.com | ACTIVE |
| 2 | Priya Patel | priya@gmail.com | inactive |
| 3 | Rahul Verma | rahul@yahoo.com | ACTIVE |

---

## 1.1 LENGTH() — Character Count
⚡ **Memory Hook**: `LENGTH(str)` counts the number of characters in a string.

```sql
SELECT full_name, LENGTH(full_name) AS name_len
FROM users;
```

### 📤 Output Table
| full_name | name_len |
|---|---|
|  Amit Sharma  | 15 |
| Priya Patel | 11 |
| Rahul Verma | 11 |

---

## 1.2 LOWER() & UPPER() — Case Conversion
⚡ **Memory Hook**: Standardize case for consistent comparisons and formatting.

```sql
SELECT 
    LOWER(status) AS status_lowercase,
    UPPER(full_name) AS name_uppercase
FROM users;
```

### 📤 Output Table
| status_lowercase | name_uppercase |
|---|---|
| active | AMIT SHARMA |
| inactive | PRIYA PATEL |
| active | RAHUL VERMA |

---

## 1.3 TRIM() — Remove Surrounding Spaces
⚡ **Memory Hook**: Strips leading and trailing whitespace.

```sql
SELECT TRIM(full_name) AS clean_name, LENGTH(TRIM(full_name)) AS clean_len
FROM users
WHERE id = 1;
```

### 📤 Output Table
| clean_name | clean_len |
|---|---|
| Amit Sharma | 11 |

---

## 1.4 SUBSTRING() — Extract Substring
⚡ **Memory Hook**: `SUBSTRING(str, start_pos, length)` extracts characters starting from index `1` (1-indexed).

```sql
-- Extract first 5 characters of full_name
SELECT full_name, SUBSTRING(TRIM(full_name), 1, 5) AS short_name
FROM users;
```

### 📤 Output Table
| full_name | short_name |
|---|---|
|  Amit Sharma  | Amit |
| Priya Patel | Priya |
| Rahul Verma | Rahul |

---

## 1.5 REPLACE() — String Replacement
⚡ **Memory Hook**: `REPLACE(str, search, replace_with)` swaps substrings.

```sql
SELECT email, REPLACE(email, '@oldcompany.com', '@newcompany.com') AS updated_email
FROM users
WHERE id = 1;
```

### 📤 Output Table
| email | updated_email |
|---|---|
| amit@oldcompany.com | amit@newcompany.com |

---

## 1.6 CONCAT() — Combining Strings
⚡ **Memory Hook**: Glues multiple string values together into one string.

```sql
SELECT CONCAT(TRIM(full_name), ' <', email, '>') AS formatted_contact
FROM users;
```

### 📤 Output Table
| formatted_contact |
|---|
| Amit Sharma <amit@oldcompany.com> |
| Priya Patel <priya@gmail.com> |
| Rahul Verma <rahul@yahoo.com> |

---

## 1.7 Capitalize Single Character / First Letter Only (LeetCode 1667 Pattern)

⚡ **Memory Hook**: To capitalize only the **1st character** of a string and keep the remaining characters **lowercase**:
1. `UPPER(SUBSTRING(name, 1, 1))` $\rightarrow$ Extracts & upper-cases 1st character.
2. `LOWER(SUBSTRING(name, 2))` $\rightarrow$ Extracts & lower-cases characters from 2nd position to the end.
3. `CONCAT(...)` $\rightarrow$ Glues them together.

### 📥 Input Table: `Users`
| user_id | name |
|---|---|
| 1 | aMiT |
| 2 | pRIYA |
| 3 | rAHUL |

> Problem: **"Fix names in a table so that only the first character is uppercase and the rest are lowercase (LeetCode 1667)."**

### 💻 SQL Query (LeetCode 1667 Solution)
```sql
SELECT 
    user_id,
    CONCAT(
        UPPER(SUBSTRING(name, 1, 1)),
        LOWER(SUBSTRING(name, 2))
    ) AS name
FROM Users
ORDER BY user_id;
```

### 📤 Output Table
| user_id | name |
|---|---|
| 1 | Amit |
| 2 | Priya |
| 3 | Rahul |

---

### 💡 General Formula: Convert Character at Any Specific Index $i$
To convert only the $i$-th character of a string to uppercase/lowercase:

```sql
CONCAT(
    SUBSTRING(name, 1, i - 1),       -- Characters before index i
    UPPER(SUBSTRING(name, i, 1)),   -- Convert character at index i
    SUBSTRING(name, i + 1)          -- Characters after index i
)
```

> [!NOTE]
> PostgreSQL provides a built-in `INITCAP(name)` function that automatically capitalizes the first letter of each word. In MySQL (used by LeetCode), use the `CONCAT` + `SUBSTRING` combination shown above!

---

# 2. Numeric Data Types & Operations

Common types: `INT`/`INTEGER` (whole numbers), `DECIMAL(precision, scale)` (exact decimal/currency), `FLOAT`/`DOUBLE` (approximate floating point).

### 📥 Input Table: `products`
| id | product_name | price | quantity | discount |
|---|---|---|---|---|
| 101 | Laptop | 75000.50 | 4 | 500.00 |
| 102 | Mouse | 450.25 | 10 | 0.00 |
| 103 | Keyboard | 1200.80 | 0 | 50.00 |
| 104 | Monitor | 15000.75 | 3 | 250.50 |

---

## 2.1 Basic Arithmetic (`+`, `-`, `*`, `/`, `%`)

```sql
SELECT 
    product_name,
    price * quantity AS gross_revenue,
    (price * quantity) - discount AS net_revenue
FROM products;
```

### 📤 Output Table
| product_name | gross_revenue | net_revenue |
|---|---|---|
| Laptop | 300002.00 | 299502.00 |
| Mouse | 4502.50 | 4502.50 |
| Keyboard | 0.00 | -50.00 |
| Monitor | 45002.25 | 44751.75 |

---

## 2.2 Numeric Aggregations: SUM(), AVG(), MIN(), MAX()
⚡ **Memory Hook**: Mathematical summary functions over columns.

```sql
SELECT 
    SUM(price * quantity) AS total_inventory_value,
    AVG(price) AS average_price,
    MIN(price) AS cheapest_price,
    MAX(price) AS most_expensive_price
FROM products;
```

### 📤 Output Table
| total_inventory_value | average_price | cheapest_price | most_expensive_price |
|---|---|---|---|
| 349506.75 | 22913.075 | 450.25 | 75000.50 |

---

## 2.3 ROUND(), FLOOR(), CEIL() — Numeric Rounding Functions

| Function | Description | Example Input | Output |
|---|---|---|---|
| `ROUND(x, d)` | Rounds to $d$ decimal places | `ROUND(450.256, 2)` | `450.26` |
| `FLOOR(x)` | Rounds DOWN to integer | `FLOOR(450.85)` | `450` |
| `CEIL(x)` / `CEILING(x)` | Rounds UP to integer | `CEIL(450.15)` | `451` |
| `ABS(x)` | Absolute value | `ABS(-50.00)` | `50.00` |

---

# 3. Date & Time Data Types

Common types: `DATE` (`YYYY-MM-DD`), `TIME` (`HH:MM:SS`), `TIMESTAMP` (`YYYY-MM-DD HH:MM:SS`).

### 📥 Input Table: `orders`
| order_id | customer_id | order_timestamp |
|---|---|---|
| 501 | 1 | 2026-01-15 10:30:00 |
| 502 | 2 | 2026-08-12 14:45:10 |
| 503 | 1 | 2026-12-31 23:59:59 |
| 504 | 3 | 2027-01-01 00:00:00 |

---

## 3.1 Date Comparisons & Range Filters

> [!IMPORTANT]
> **Half-Open Date Range Pattern**: When querying timestamps for a calendar year/month, ALWAYS use `>= start AND < next_period` instead of `BETWEEN` to prevent missing records occurring late on the last day!

### 💻 Query (Orders created during year 2026)
```sql
SELECT order_id, order_timestamp
FROM orders
WHERE order_timestamp >= '2026-01-01'
  AND order_timestamp < '2027-01-01';
```

### 📤 Output Table
| order_id | order_timestamp |
|---|---|
| 501 | 2026-01-15 10:30:00 |
| 502 | 2026-08-12 14:45:10 |
| 503 | 2026-12-31 23:59:59 |

---

## 3.2 Extracting Date Parts (Year, Month, Day)

```sql
SELECT 
    order_id,
    EXTRACT(YEAR FROM order_timestamp) AS order_year,
    EXTRACT(MONTH FROM order_timestamp) AS order_month
FROM orders;
```

### 📤 Output Table
| order_id | order_year | order_month |
|---|---|---|
| 501 | 2026 | 1 |
| 502 | 2026 | 8 |
| 503 | 2026 | 12 |
| 504 | 2027 | 1 |

---

# 4. NULL Handling Functions

### 📥 Input Table: `contacts`
| id | name | primary_phone | secondary_phone |
|---|---|---|---|
| 1 | Amit | 9876543210 | 9123456789 |
| 2 | Priya | NULL | 9988776655 |
| 3 | Rahul | NULL | NULL |

---

## 4.1 COALESCE() — Fallback Value Replacement
⚡ **Memory Hook**: Returns the **FIRST NON-NULL** value from a list of parameters.

```sql
SELECT 
    name,
    COALESCE(primary_phone, secondary_phone, 'No Phone Available') AS contact_number
FROM contacts;
```

### 📤 Output Table
| name | contact_number |
|---|---|
| Amit | 9876543210 |
| Priya | 9988776655 |
| Rahul | No Phone Available |

---

## 4.2 NULLIF() — Prevent Division by Zero
⚡ **Memory Hook**: `NULLIF(a, b)` returns `NULL` if $a = b$, otherwise returns $a$.

```sql
-- Safe division: If quantity is 0, NULLIF(quantity, 0) turns 0 into NULL, avoiding crash!
SELECT 
    product_name,
    price / NULLIF(quantity, 0) AS unit_price_per_item
FROM products;
```

### 📥 Input Table: `products`
| product_name | price | quantity |
|---|---|---|
| Mouse | 100.00 | 2 |
| Keyboard | 500.00 | 0 |

### 📤 Output Table
| product_name | unit_price_per_item |
|---|---|
| Mouse | 50.00 |
| Keyboard | NULL |

---

# 5. Type Casting (Conversion)

⚡ **Memory Hook**: `CAST(expression AS target_type)` converts a value from one data type to another.

### 💻 Query
```sql
SELECT 
    CAST('123' AS INTEGER) AS num_val,
    CAST(123.456 AS VARCHAR) AS str_val,
    '2026-08-12'::DATE AS postgres_date_cast;
```

### 📤 Output Table
| num_val | str_val | postgres_date_cast |
|---|---|---|
| 123 | 123.456 | 2026-08-12 |

---

# 6. Type-Specific Pattern Cheat Sheet Matrix

| English Problem Keyword | Data Type Category | SQL Function / Operator |
|---|---|---|
| "Length / count of characters" | String | `LENGTH(column)` |
| "Case-insensitive match" | String | `LOWER(column)` / `UPPER(column)` |
| "Trim leading/trailing spaces" | String | `TRIM(column)` |
| "Extract substring from position" | String | `SUBSTRING(column, start, len)` |
| "Replace substring" | String | `REPLACE(col, old, new)` |
| "Combine strings / concatenate" | String | `CONCAT(a, b, c)` |
| "Total sum of numeric column" | Numeric | `SUM(column)` |
| "Average value" | Numeric | `AVG(column)` |
| "Min / Max value" | Numeric | `MIN()` / `MAX()` |
| "Round to N decimal places" | Numeric | `ROUND(column, N)` |
| "Prevent division by zero" | Numeric / NULL | `val / NULLIF(qty, 0)` |
| "Filter timestamps by year/month" | Date / Time | `>= '2026-01-01' AND < '2027-01-01'` |
| "Extract year or month number" | Date / Time | `EXTRACT(YEAR FROM date_col)` |
| "Replace NULL with fallback string" | NULL | `COALESCE(col, 'Fallback')` |
| "Convert string to integer" | Any | `CAST(col AS INTEGER)` |
