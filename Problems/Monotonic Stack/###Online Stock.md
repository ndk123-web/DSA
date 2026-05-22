# Intuition

For every new stock price, we need to find:

> how many consecutive previous days had price <= current price.

A brute force approach would scan backward every time, which becomes `O(n²)`.

Instead, we observe:

* Smaller/equal previous prices are useless once a bigger price appears.
* We only care about the **previous greater price**.
* This naturally leads to a **monotonic decreasing stack**.

---

# Key Observation

If a previous price is smaller than or equal to the current price:

```txt id="20y8f0"
previous_price <= current_price
```

then that previous price can never act as a stopping point again.

So we can safely remove it.

---

# Optimization Idea

Instead of storing only prices, store:

```txt id="z7e6qq"
(price, span)
```

Why?

Suppose:

```txt id="m8llr4"
75 has span = 4
```

and current price is `85`.

Then all 4 days automatically belong to `85` too.

So instead of counting one-by-one:

```cpp id="vsk2u5"
span++;
```

we directly reuse:

```cpp id="fkllxy"
span += previous_span;
```

This avoids repeated work.

---

# Algorithm

For every incoming `price`:

1. Start with:

```cpp id="1mjlwm"
span = 1
```

(today itself counts)

2. While stack top price is `<= current price`:

   * add its stored span
   * pop it

3. Push:

```cpp id="78fem4"
{price, span}
```

4. Return span.

---

# Dry Run

Prices:

```txt id="0x4xew"
100, 80, 60, 70, 60, 75, 85
```

Stack stores:

```txt id="guxm6z"
(price, span)
```

---

## price = 100

Push:

```txt id="hjlwm5"
(100,1)
```

Answer = 1

---

## price = 80

100 > 80 → stop

Push:

```txt id="gt0zn4"
(80,1)
```

Answer = 1

---

## price = 60

80 > 60

Push:

```txt id="h89vrv"
(60,1)
```

Answer = 1

---

## price = 70

Pop `(60,1)`

```txt id="9i0wh4"
span = 1 + 1 = 2
```

Push:

```txt id="l7jz2v"
(70,2)
```

Answer = 2

---

## price = 75

Pop `(60,1)`

```txt id="1dqarf"
span = 2
```

Pop `(70,2)`

```txt id="b9jlwm"
span = 4
```

Push:

```txt id="v3r1pc"
(75,4)
```

Answer = 4

---

# Complexity Analysis

## Time Complexity

Each element:

* pushed once
* popped once

So total:

```txt id="gl54c8"
O(n)
```

Amortized per call:

```txt id="f72kl6"
O(1)
```

---

## Space Complexity

```txt id="i5s9lm"
O(n)
```

for the stack.

---

# C++ Solution

```cpp id="cshxbm"
class StockSpanner {
public:
    
    stack<pair<int, int>> preComputation;

    StockSpanner() {
        
    }

    int next(int price) {

        int span = 1;

        while (!preComputation.empty() &&
               preComputation.top().first <= price) {

            span += preComputation.top().second;
            preComputation.pop();
        }

        preComputation.push({price, span});

        return span;
    }
};
```
