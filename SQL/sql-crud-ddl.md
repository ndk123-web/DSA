# SQL Data Definition (DDL) & Data Manipulation (DML) — Complete CRUD Guide

## 🎯 Core Mental Model: The 4 Categories of SQL Commands

SQL commands are divided into 4 functional language categories:

```text
                                     SQL COMMAND CATEGORIES
                                                │
         ┌──────────────────┬───────────────────┼───────────────────┐
         ▼                  ▼                   ▼                   ▼
      DQL (Query)       DML (Data)          DDL (Schema)       TCL (Transactions)
    ───────────────   ───────────────     ─────────────────  ─────────────────────
    • SELECT          • INSERT INTO       • CREATE TABLE     • COMMIT
                      • UPDATE            • ALTER TABLE      • ROLLBACK
                      • DELETE            • DROP TABLE       • SAVEPOINT
                                          • TRUNCATE TABLE
```

- **DQL**: Queries data (reading rows).
- **DML**: Manipulates data rows (Create, Update, Delete data).
- **DDL**: Defines table schemas and database structures.
- **TCL**: Controls transaction boundaries and database state changes.

---

# 1. DDL — Data Definition Language (Schema Management)

---

## 1.1 `CREATE TABLE` — Creating Table Schemas with Constraints

⚡ **Memory Hook**: Defines table columns, data types, and integrity constraints (`PRIMARY KEY`, `FOREIGN KEY`, `NOT NULL`, `UNIQUE`, `DEFAULT`, `CHECK`).

### 💻 SQL Query
```sql
CREATE TABLE employees (
    emp_id      INT AUTO_INCREMENT PRIMARY KEY,
    first_name  VARCHAR(50) NOT NULL,
    last_name   VARCHAR(50) NOT NULL,
    email       VARCHAR(100) UNIQUE NOT NULL,
    salary      DECIMAL(10, 2) CHECK (salary > 0),
    dept_id     INT,
    status      VARCHAR(20) DEFAULT 'ACTIVE',
    created_at  TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (dept_id) REFERENCES departments(id)
);
```

### 📤 Resulting Schema Constraints
| Column Name | Constraint | Purpose |
|---|---|---|
| `emp_id` | `PRIMARY KEY` + `AUTO_INCREMENT` | Unique identifier, auto-incrementing integer |
| `email` | `UNIQUE` + `NOT NULL` | No duplicates allowed, cannot be missing/NULL |
| `salary` | `CHECK (salary > 0)` | Enforces salary must be strictly positive |
| `status` | `DEFAULT 'ACTIVE'` | Defaults to `'ACTIVE'` if no value supplied |
| `dept_id` | `FOREIGN KEY` | Links `dept_id` to `id` column in `departments` table |

---

## 1.2 `ALTER TABLE` — Modifying Existing Schemas

⚡ **Memory Hook**: Modifies an existing table without dropping it.

```sql
-- 1. Add a new column
ALTER TABLE employees
ADD COLUMN phone_number VARCHAR(15);

-- 2. Drop an existing column
ALTER TABLE employees
DROP COLUMN phone_number;

-- 3. Modify column data type/constraint
ALTER TABLE employees
MODIFY COLUMN salary DECIMAL(12, 2);

-- 4. Rename a column
ALTER TABLE employees
RENAME COLUMN first_name TO given_name;
```

---

## 1.3 `DROP TABLE` vs `TRUNCATE TABLE` vs `DELETE FROM`

> [!CAUTION]
> This is one of the most famous interview comparison questions!

| Feature | `DELETE FROM` | `TRUNCATE TABLE` | `DROP TABLE` |
|---|---|---|---|
| **Category** | DML (Data Manipulation) | DDL (Data Definition) | DDL (Data Definition) |
| **What happens?** | Deletes rows specified by `WHERE` | Removes **ALL rows** instantly | Deletes **ALL rows AND table schema** |
| **Can use `WHERE`?** | ✅ YES (`WHERE salary < 30000`) | ❌ NO | ❌ NO |
| **Resets `AUTO_INCREMENT`?** | ❌ NO | ✅ YES (Resets counter to 1) | N/A (Table is destroyed) |
| **Speed / Performance** | Slower (Row-by-row logging) | Very Fast (Metadata reset) | Fast (Drops entire object) |
| **Can `ROLLBACK`?** | ✅ YES (Inside transaction) | ❌ NO (Auto-commits in most DBs) | ❌ NO |

---

# 2. DML — Data Manipulation Language (Row Management)

---

## 2.1 `INSERT INTO` — Inserting Rows

⚡ **Memory Hook**: Adds new records to a table.

### 💻 Single & Multi-Row Insertion
```sql
-- Insert Single Row
INSERT INTO employees (first_name, last_name, email, salary, dept_id)
VALUES ('Amit', 'Sharma', 'amit@company.com', 70000.00, 10);

-- Insert Multiple Rows in a Single Query
INSERT INTO employees (first_name, last_name, email, salary, dept_id)
VALUES 
    ('Priya', 'Patel', 'priya@company.com', 90000.00, 10),
    ('Rahul', 'Verma', 'rahul@company.com', 50000.00, 20),
    ('Neha',  'Gupta', 'neha@company.com',  60000.00, 20);
```

---

### 💻 Insert From Another Table (`INSERT INTO ... SELECT`)
> Problem: **"Copy high-earning employees (>80k) into a dedicated `high_earners` archive table."**

```sql
INSERT INTO high_earners (emp_id, full_name, salary)
SELECT 
    emp_id, 
    CONCAT(first_name, ' ', last_name), 
    salary
FROM employees
WHERE salary > 80000;
```

---

## 2.2 `UPDATE` — Modifying Existing Rows

⚡ **Memory Hook**: Changes column values in existing rows matching a `WHERE` condition.

> [!WARNING]
> Running `UPDATE employees SET salary = 100000;` **WITHOUT a `WHERE` clause** will overwrite EVERY SINGLE ROW in the table!

### 💻 Query 1: Basic Update with WHERE
```sql
-- Give a 10% raise to employees in IT department (dept_id = 10)
UPDATE employees
SET salary = salary * 1.10
WHERE dept_id = 10;
```

---

### 💻 Query 2: `UPDATE` with `JOIN`
> Problem: **"Give a 15% raise to employees working in departments located in 'Mumbai'."**

```sql
UPDATE employees AS e
JOIN departments AS d ON e.dept_id = d.id
SET e.salary = e.salary * 1.15
WHERE d.location = 'Mumbai';
```

---

## 2.3 `DELETE` — Removing Rows

⚡ **Memory Hook**: Deletes rows from a table matching a `WHERE` clause.

### 💻 Query 1: Basic Delete with WHERE
```sql
DELETE FROM employees
WHERE status = 'INACTIVE';
```

---

### 💻 Query 2: `DELETE` with `JOIN` (LeetCode 196 Pattern — Delete Duplicate Emails)

> Problem: **"Delete all duplicate emails, keeping only one unique email with the smallest ID."**

### 📥 Input Table: `Person`
| id | email |
|---|---|
| 1 | john@example.com |
| 2 | bob@example.com |
| 3 | john@example.com |

### 💻 SQL Query
```sql
DELETE p1
FROM Person AS p1
JOIN Person AS p2
  ON p1.email = p2.email
WHERE p1.id > p2.id;
```

### 📤 Output Table
| id | email |
|---|---|
| 1 | john@example.com |
| 2 | bob@example.com |

### 💡 Pattern Explanation:
- `JOIN ON p1.email = p2.email` matches rows with identical emails.
- `WHERE p1.id > p2.id` targets the row with the larger ID (`id = 3`), keeping `id = 1` intact!

---

# 3. UPSERT — `INSERT ... ON DUPLICATE KEY UPDATE`

⚡ **Memory Hook**: *"If record exists, update it. If record is new, insert it."*

### 💻 MySQL Syntax (`ON DUPLICATE KEY UPDATE`)
```sql
INSERT INTO page_views (page_url, view_count)
VALUES ('/home', 1)
ON DUPLICATE KEY UPDATE view_count = view_count + 1;
```

### 💻 PostgreSQL Syntax (`ON CONFLICT DO UPDATE`)
```sql
INSERT INTO page_views (page_url, view_count)
VALUES ('/home', 1)
ON CONFLICT (page_url) 
DO UPDATE SET view_count = page_views.view_count + 1;
```

---

# 4. TCL — Transaction Control (`COMMIT` & `ROLLBACK`)

⚡ **Memory Hook**: Guarantees **Atomicity** ($A$ in ACID). Either all operations succeed (`COMMIT`), or all changes are undone (`ROLLBACK`).

### 💻 Query Example (Bank Funds Transfer)
```sql
START TRANSACTION;

-- Step 1: Deduct 500 from Account 101
UPDATE accounts 
SET balance = balance - 500 
WHERE account_id = 101;

-- Step 2: Add 500 to Account 102
UPDATE accounts 
SET balance = balance + 500 
WHERE account_id = 102;

-- If both steps succeed:
COMMIT;

-- If an error occurs:
-- ROLLBACK;
```

---

# 5. Master DDL/DML Pattern Matrix

| Operation Goal | SQL Command | Pattern Syntax |
|---|---|---|
| **Create new table structure** | `CREATE TABLE` | `CREATE TABLE t (id INT PRIMARY KEY, name VARCHAR(50))` |
| **Add column to existing table** | `ALTER TABLE` | `ALTER TABLE t ADD COLUMN age INT` |
| **Fastest way to wipe table rows** | `TRUNCATE TABLE` | `TRUNCATE TABLE t` (DDL, resets auto-increment) |
| **Destroy table data and schema** | `DROP TABLE` | `DROP TABLE t` |
| **Add new records** | `INSERT INTO` | `INSERT INTO t (col1, col2) VALUES (v1, v2), (v3, v4)` |
| **Copy records from query** | `INSERT INTO ... SELECT` | `INSERT INTO t2 SELECT * FROM t1 WHERE cond` |
| **Modify existing values** | `UPDATE` | `UPDATE t SET col = val WHERE cond` |
| **Delete specific duplicate rows** | `DELETE ... JOIN` | `DELETE p1 FROM Person p1 JOIN Person p2 ON p1.email=p2.email WHERE p1.id > p2.id` |
| **Insert or Update (UPSERT)** | `ON DUPLICATE KEY UPDATE` | `INSERT INTO t ... ON DUPLICATE KEY UPDATE col = col + 1` |
| **Save/undo transaction block** | `COMMIT` / `ROLLBACK` | `START TRANSACTION; ... COMMIT;` |
