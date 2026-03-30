## Lemonade Change — Full Readme (Interview Standard)

---

## 1. Problem Statement

You are given a queue of customers represented by an array `bills`.

Each customer:

* Buys exactly one lemonade costing **$5**
* Pays with either **$5, $10, or $20**

You must:

* Provide correct change **immediately**
* Start with **no money**

Return:

* `true` → if all customers are served correctly
* `false` → if at any point you cannot give correct change

---

## 2. Why this problem exists (Interviewer Intent)

This is not a math problem.

It tests:

* Real-time decision making
* State tracking
* Greedy strategy
* Understanding of **denominations vs total value**

---

## 3. Core Intuition

You are simulating a **cashier**.

At every step:

* You only have access to past transactions
* You must decide instantly whether change is possible

---

## 4. Key Insight

You do NOT care about total money.

You ONLY care about:

* how many `$5` bills you have
* how many `$10` bills you have

Why?

Because:

* Change must be given using **exact denominations**
* You cannot break a `$10` into two `$5`

---

## 5. State Representation

Maintain two variables:

* `five` → count of $5 bills
* `ten` → count of $10 bills

You ignore $20 bills because:

* They are never used to give change

---

## 6. Decision Logic

Process customers one by one.

---

### Case 1: bill = 5

* No change required
* Simply collect it

State update:

```
five++
```

---

### Case 2: bill = 10

* You must give **$5 change**

Check:

* If `five == 0` → cannot give change → return false

Else:

* give one $5 → `five--`
* collect $10 → `ten++`

---

### Case 3: bill = 20

* You must give **$15 change**

Two ways:

#### Option 1 (Preferred):

* Give one $10 + one $5

Condition:

```
ten > 0 AND five > 0
```

---

#### Option 2:

* Give three $5

Condition:

```
five >= 3
```

---

#### Failure:

* If neither option is possible → return false

---

## 7. Why Greedy Works

When handling $20:

You prefer:

```
10 + 5
```

over:

```
5 + 5 + 5
```

Reason:

* $5 bills are more flexible
* You need $5 for future $10 customers
* Preserving $5 prevents future failure

---

## 8. Algorithm

1. Initialize:

   * `five = 0`
   * `ten = 0`

2. Iterate through each bill:

   * If 5 → increment `five`
   * If 10 → check and give one 5
   * If 20 → try (10 + 5), else (5 + 5 + 5), else fail

3. If all customers are processed → return true

---

## 9. Dry Run

### Example 1

Input:

```
[5, 10, 5, 5, 20]
```

Step-by-step:

| Step | Bill | five | ten | Action        |
| ---- | ---- | ---- | --- | ------------- |
| 1    | 5    | 1    | 0   | collect       |
| 2    | 10   | 0    | 1   | give 5        |
| 3    | 5    | 1    | 1   | collect       |
| 4    | 5    | 2    | 1   | collect       |
| 5    | 20   | 1    | 0   | give (10 + 5) |

Result: true

---

### Example 2

Input:

```
[5, 5, 10, 10, 20]
```

| Step | Bill | five | ten | Action         |
| ---- | ---- | ---- | --- | -------------- |
| 1    | 5    | 1    | 0   | collect        |
| 2    | 5    | 2    | 0   | collect        |
| 3    | 10   | 1    | 1   | give 5         |
| 4    | 10   | 0    | 2   | give 5         |
| 5    | 20   | 0    | 2   | cannot give 15 |

Result: false

---

### Example 3 (Edge Case)

Input:

```
[10]
```

* No $5 available
* Cannot give change

Result: false

---

## 10. Complexity Analysis

### Time Complexity

```
O(n)
```

* Single pass through array

---

### Space Complexity

```
O(1)
```

* Only two variables used

---

## 11. Common Mistakes

### Mistake 1: Tracking total money

Wrong because:

* Denominations matter, not sum

---

### Mistake 2: Using future information

Invalid because:

* You must decide in real time

---

### Mistake 3: Accepting bill before giving change

Wrong order:

* First validate change
* Then update state

---

### Mistake 4: Wrong logic for $10

* Only one $5 is required
* Not two

---

### Mistake 5: Missing failure conditions

Every case must explicitly handle:

* success
* failure

---

## 12. Final Code

```cpp
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;

        for (int& bill : bills) {

            if (bill == 5) {
                five++;
            }
            else if (bill == 10) {
                if (five >= 1) {
                    five--;
                    ten++;
                } else {
                    return false;
                }
            }
            else { // bill == 20
                if (ten >= 1 && five >= 1) {
                    ten--;
                    five--;
                } else if (five >= 3) {
                    five -= 3;
                } else {
                    return false;
                }
            }
        }

        return true;
    }
};
```

---

## 13. Final Takeaway

This problem is not about money.

It is about:

* managing limited resources
* making optimal local decisions
* preserving critical resources for future steps