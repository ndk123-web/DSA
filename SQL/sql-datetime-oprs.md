# SQL Date & DateTime Operations — Pattern Mastery

## 🎯 Core Mental Model

Date and DateTime data types (`YYYY-MM-DD` and `YYYY-MM-DD HH:MM:SS`) require specialized SQL functions for:
1. **Comparisons**: Filtering ranges using `=`, `>`, `<`, `>=`, `<=`, `BETWEEN`.
2. **Extraction**: Pulling out specific components (`YEAR`, `MONTH`, `DAY`).
3. **Formatting**: Converting dates into readable text patterns (`DATE_FORMAT(date, '%Y-%m')`).
4. **Arithmetic**: Adding/subtracting time intervals (`DATE_ADD`, `DATE_SUB`, `DATEDIFF`).
5. **Grouping**: Aggregating metrics by month, year, or custom date ranges.

```text
Raw DateTime                      Extraction / Formatting                  Aggregated Output
┌───────────────────────┐         ┌───────────────────────────────┐        ┌───────────────────────────────┐
│ 2026-08-21 14:30:00   │ ──────► │ YEAR  ──► 2026                │ ─────► │ Month   | Total Sales | Count │
│ 2026-08-25 09:15:00   │         │ MONTH ──► 08                  │        │ 2026-08 | 15000       | 2     │
│ 2026-09-01 11:00:00   │         │ DATE_FORMAT ──► '2026-08'     │        │ 2026-09 | 8000        | 1     │
└───────────────────────┘         └───────────────────────────────┘        └───────────────────────────────┘
```

---

# Sample Dataset for Examples

### 📥 Input Table: `Transactions` (`t`)
| id | country | state | amount | trans_date |
|---|---|---|---|---|
| 121 | US | approved | 1000 | 2024-01-18 |
| 122 | US | declined | 2000 | 2024-01-19 |
| 123 | US | approved | 2000 | 2024-01-20 |
| 124 | DE | approved | 2000 | 2024-01-07 |
| 125 | DE | approved | 3000 | 2024-02-15 |

---

# 1. Basic Date Comparisons (`=`, `!=`, `>`, `<`, `>=`, `<=`, `BETWEEN`)

⚡ **Memory Hook**: SQL compares `DATE` values (`YYYY-MM-DD`) chronologically.
- `'2024-01-20' > '2024-01-18'` evaluates to `TRUE` (Later date).
- `'2024-01-18' < '2024-01-20'` evaluates to `TRUE` (Earlier date).

### 📐 Comparison Operators Summary Table

| Operator | Meaning | Example |
|---|---|---|
| `=` | Exact date match | `trans_date = '2024-01-18'` |
| `!=` or `<>` | Not equal to date | `trans_date != '2024-01-18'` |
| `>` | After / Later than date | `trans_date > '2024-01-18'` |
| `<` | Before / Earlier than date | `trans_date < '2024-01-18'` |
| `>=` | On or after date | `trans_date >= '2024-01-18'` |
| `<=` | On or before date | `trans_date <= '2024-01-18'` |
| `BETWEEN a AND b` | Inclusive date range ($a \le date \le b$) | `trans_date BETWEEN '2024-01-01' AND '2024-01-31'` |

---

## 1.1 Simple Date Range Query (`BETWEEN`)

> Problem: **"Find all transactions created between January 18, 2024 and January 20, 2024 (inclusive)."**

### 💻 Query
```sql
SELECT id, amount, trans_date
FROM Transactions
WHERE trans_date BETWEEN '2024-01-18' AND '2024-01-20';
```

### 📤 Output Table
| id | amount | trans_date |
|---|---|---|
| 121 | 1000 | 2024-01-18 |
| 122 | 2000 | 2024-01-19 |
| 123 | 2000 | 2024-01-20 |

---

## 1.2 `BETWEEN` vs Half-Open Timestamp Range (`>=` and `<`)

> [!WARNING]
> **TIMESTAMP / DATETIME GOTCHA**:
> If `trans_date` is a `DATETIME` or `TIMESTAMP` type (e.g. `2024-01-31 15:30:00`), then:
> ```sql
> WHERE trans_date BETWEEN '2024-01-01' AND '2024-01-31'
> ```
> will **MISS** transactions created late on January 31st! This happens because `'2024-01-31'` is interpreted as `'2024-01-31 00:00:00'`, and `15:30:00` is greater than `00:00:00`.
>
> **Best Practice Pattern**: Use a **half-open range**:
> ```sql
> WHERE trans_date >= '2024-01-01'
>   AND trans_date <  '2024-02-01'
> ```

---

# 2. Date Component Extraction (`YEAR`, `MONTH`, `DAY`, `EXTRACT`)

⚡ **Memory Hook**: Extracts integer numeric parts directly from a date column.

| Function | Output Description | Example Input | Output |
|---|---|---|---|
| `YEAR(date)` | Returns 4-digit year | `YEAR('2026-08-21')` | `2026` |
| `MONTH(date)` | Returns month number (1–12) | `MONTH('2026-08-21')` | `8` |
| `DAY(date)` / `DAYOFMONTH(date)` | Returns day of the month (1–31) | `DAY('2026-08-21')` | `21` |
| `DAYOFWEEK(date)` | Returns day of week (1=Sun, 2=Mon...) | `DAYOFWEEK('2026-08-21')` | `6` |
| `EXTRACT(part FROM date)` | Standard ANSI extraction | `EXTRACT(MONTH FROM '2026-08-21')` | `8` |

### 💻 Query
```sql
SELECT 
    id,
    trans_date,
    YEAR(trans_date)  AS trans_year,
    MONTH(trans_date) AS trans_month,
    DAY(trans_date)   AS trans_day
FROM Transactions;
```

### 📤 Output Table
| id | trans_date | trans_year | trans_month | trans_day |
|---|---|---|---|---|
| 121 | 2024-01-18 | 2024 | 1 | 18 |
| 122 | 2024-01-19 | 2024 | 1 | 19 |
| 125 | 2024-02-15 | 2024 | 2 | 15 |

---

# 3. Date Formatting (`DATE_FORMAT`)

⚡ **Memory Hook**: Converts a date into a custom-formatted string (e.g. `'YYYY-MM'` for monthly reporting).

### 📐 Common MySQL `DATE_FORMAT` Specifiers
- `%Y` = 4-digit year (`2026`)
- `%y` = 2-digit year (`26`)
- `%m` = 2-digit month (`01` to `12`)
- `%d` = 2-digit day of month (`01` to `31`)
- `%M` = Full month name (`January`, `August`)
- `%b` = Abbreviated month name (`Jan`, `Aug`)
- `%W` = Full weekday name (`Monday`, `Friday`)

### 💻 Query
```sql
SELECT 
    trans_date,
    DATE_FORMAT(trans_date, '%Y-%m')    AS year_month,
    DATE_FORMAT(trans_date, '%M %d, %Y') AS formatted_text
FROM Transactions
WHERE id = 121;
```

### 📤 Output Table
| trans_date | year_month | formatted_text |
|---|---|---|
| 2024-01-18 | 2024-01 | January 18, 2024 |

---

# 4. Monthly Transactions Master Example (LeetCode 1193 Pattern)

> Problem: **"Find for each month and country: the number of transactions, approved transactions, total amount, and approved total amount."**

⚡ **Key Insight**: Group by monthly formatted date (`DATE_FORMAT(trans_date, '%Y-%m')`) and country, using conditional `SUM(CASE WHEN ... END)` for approved metrics.

### 💻 SQL Query
```sql
SELECT 
    DATE_FORMAT(t.trans_date, '%Y-%m') AS month,
    t.country,
    COUNT(*) AS trans_count,
    SUM(
        CASE 
            WHEN t.state = 'approved' THEN 1 
            ELSE 0 
        END
    ) AS approved_count,
    SUM(t.amount) AS trans_total_amount,
    SUM(
        CASE 
            WHEN t.state = 'approved' THEN t.amount 
            ELSE 0 
        END
    ) AS approved_total_amount
FROM Transactions AS t
GROUP BY DATE_FORMAT(t.trans_date, '%Y-%m'), t.country;
```

### 📤 Output Table
| month | country | trans_count | approved_count | trans_total_amount | approved_total_amount |
|---|---|---|---|---|---|
| 2024-01 | US | 3 | 2 | 5000 | 3000 |
| 2024-01 | DE | 1 | 1 | 2000 | 2000 |
| 2024-02 | DE | 1 | 1 | 3000 | 3000 |

---

# 5. Date Arithmetic (`DATE_ADD`, `DATE_SUB`, `DATEDIFF`)

⚡ **Memory Hook**: Modifies dates or computes the number of days between two dates.

---

## 5.1 `DATE_ADD()` & `DATE_SUB()` — Adding/Subtracting Time

```sql
-- Add 1 day
DATE_ADD(trans_date, INTERVAL 1 DAY)

-- Subtract 1 month
DATE_SUB(trans_date, INTERVAL 1 MONTH)

-- Add 7 days
trans_date + INTERVAL 7 DAY
```

### 💻 Query
```sql
SELECT 
    trans_date,
    DATE_ADD(trans_date, INTERVAL 1 DAY)   AS next_day,
    DATE_SUB(trans_date, INTERVAL 1 MONTH) AS prev_month
FROM Transactions
WHERE id = 121;
```

### 📤 Output Table
| trans_date | next_day | prev_month |
|---|---|---|
| 2024-01-18 | 2024-01-19 | 2023-12-18 |

---

## 5.2 `DATEDIFF()` — Difference Between Two Dates

⚡ **Memory Hook**: `DATEDIFF(date1, date2)` returns $\text{date1} - \text{date2}$ in **days**.

> Problem: **"Find weather record IDs where temperature was higher than the previous day (LeetCode 197 Pattern)."**

### 📥 Input Table: `Weather` (`w`)
| id | recordDate | temperature |
|---|---|---|
| 1 | 2026-08-01 | 10 |
| 2 | 2026-08-02 | 25 |
| 3 | 2026-08-03 | 20 |
| 4 | 2026-08-04 | 30 |

### 💻 Query (Self-JOIN ON `DATEDIFF = 1`)
```sql
SELECT w1.id
FROM Weather AS w1
JOIN Weather AS w2
  ON DATEDIFF(w1.recordDate, w2.recordDate) = 1
WHERE w1.temperature > w2.temperature;
```

### 📤 Output Table
| id |
|---|
| 2 |
| 4 |

> [!CAUTION]
> Do NOT assume consecutive IDs mean consecutive days! Row 1 could be `2026-08-01` and Row 2 could be `2026-08-05`. Always use `DATEDIFF(w1.recordDate, w2.recordDate) = 1` or `w1.recordDate = DATE_ADD(w2.recordDate, INTERVAL 1 DAY)`.

---

# 6. Current Date & Rolling Windows (`CURDATE`, `NOW`)

⚡ **Memory Hook**:
- `NOW()` / `CURRENT_TIMESTAMP()` $\rightarrow$ Current date and time (`YYYY-MM-DD HH:MM:SS`).
- `CURDATE()` / `CURRENT_DATE()` $\rightarrow$ Current calendar date (`YYYY-MM-DD`).

### 💻 Query (Orders in the last 30 days)
```sql
SELECT order_id, order_date
FROM Orders
WHERE order_date >= DATE_SUB(CURDATE(), INTERVAL 30 DAY);
```

---

# 7. MySQL vs PostgreSQL Date Dialect Cheat Table

| Operation | MySQL Syntax | PostgreSQL Syntax | Standard ANSI SQL |
|---|---|---|---|
| **Format Year-Month** | `DATE_FORMAT(d, '%Y-%m')` | `TO_CHAR(d, 'YYYY-MM')` | N/A |
| **Extract Month** | `MONTH(d)` | `EXTRACT(MONTH FROM d)` | `EXTRACT(MONTH FROM d)` |
| **Add 1 Day** | `DATE_ADD(d, INTERVAL 1 DAY)` | `d + INTERVAL '1 day'` | `d + INTERVAL '1' DAY` |
| **Days Difference** | `DATEDIFF(d1, d2)` | `d1 - d2` | `DATEDIFF(d1, d2)` |
| **Current Date** | `CURDATE()` | `CURRENT_DATE` | `CURRENT_DATE` |

---

# 8. Master Date Pattern Recognition Matrix

| English Problem Keyword | SQL Date Technique | Core Pattern |
|---|---|---|
| *"Date within inclusive range"* | `BETWEEN date1 AND date2` | `WHERE date BETWEEN '2024-01-01' AND '2024-01-31'` |
| *"Timestamp within month safely"* | `>= start AND < next_period` | `WHERE ts >= '2024-01-01' AND ts < '2024-02-01'` |
| *"Group transactions by year and month"* | `DATE_FORMAT(date, '%Y-%m')` | `GROUP BY DATE_FORMAT(trans_date, '%Y-%m')` |
| *"Find consecutive days"* | `DATEDIFF(d1, d2) = 1` | `ON DATEDIFF(w1.date, w2.date) = 1` |
| *"Yesterday's date"* | `DATE_SUB(date, INTERVAL 1 DAY)` | `DATE_SUB(CURDATE(), INTERVAL 1 DAY)` |
| *"Transactions in current year"* | `YEAR(date) = YEAR(CURDATE())` | Filter by matching current year |
| *"Active users in last 30 days"* | `date >= DATE_SUB(CURDATE(), INTERVAL 30 DAY)` | Rolling 30-day window |
| *"Month name and day"* | `DATE_FORMAT(date, '%M %d')` | String formatting output |
