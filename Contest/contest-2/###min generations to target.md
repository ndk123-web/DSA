# 3923. Minimum Generations to Target Point

## Problem Link

3923. Minimum Generations to Target Point 

## Problem Description

You are given a set of initial 3D points (Generation 0). In each new generation $k$, you can take any two distinct points from all previous generations and calculate their midpoint using the floor function:

$$c = \left\lfloor \frac{x_1 + x_2}{2} \right\rfloor, \left\lfloor \frac{y_1 + y_2}{2} \right\rfloor, \left\lfloor \frac{z_1 + z_2}{2} \right\rfloor$$



Return the smallest generation $k$ in which the target point appears. If it is impossible to reach the target, return -1.

---

## My Playbook Entry (The "Tell")

* 
**Pattern Used:** Geometric Reachability / Simulation (Batch Updates).


* 
**The "Trick":** The rule of **Simultaneous Production** requires that all points in a single generation are formed at once. This means you must store new points in a temporary set (`tempsett`) and only update the main set (`sett`) after the generation is complete.


* 
**Warning (The Simulation Trap):** This approach works by physically generating points, but it is prone to **Exponential Growth**. In a real contest, you should also consider the **Bounding Box** property—if a target is outside the min/max coordinates of the initial points, it can never be reached.



---

## Logic Breakdown

1. 
**Generation 0 Initialization:** We store all starting points in a `std::set`. Using a set automatically handles duplicate points and makes searching for the target efficient.


2. 
**Batch Processing:** To produce a new generation, we iterate through every distinct pair in the current set and calculate their midpoint.


3. 
**Simultaneous Update:** We use `tempsett` to ensure we aren't using points created *during* the current generation to make other points in the *same* generation.


4. 
**Stagnation Check (`temp == s`):** If a generation produces no new unique points, we have reached a "stagnation point" due to integer limits or geometric boundaries. If the target hasn't been found by then, it never will be, so we return -1.



---

## Implementation

```cpp
class Solution {
public:
    vector<int> calculate(const vector<int>& v1, const vector<int>& v2) {
        return {(v1[0] + v2[0]) / 2, (v1[1] + v2[1]) / 2, (v1[2] + v2[2]) / 2};
    }

    int evaluate(set<vector<int>>& sett, vector<int> target) {
        int gen = 0;

        while (!sett.contains(target)) {
            auto tempsett = sett; // Capture the state for simultaneous production

            for (auto it1 = sett.begin(); it1 != sett.end(); it1++) {
                for (auto it2 = next(it1); it2 != sett.end(); it2++) {
                    tempsett.insert(calculate(*it1, *it2));
                }
            }

            // If no new points were added, target is unreachable
            if (tempsett == sett) return -1;

            sett = tempsett; // Move to the next generation
            gen++;
        }
        return gen;
    }

    int minGenerations(vector<vector<int>>& points, vector<int>& target) {
        set<vector<int>> sett;
        for (auto& point : points) {
            sett.insert(point);
        }
        return evaluate(sett, target);
    }
};

```

---

## Complexity Analysis

* 
**Time Complexity:** Exponential. In the worst case, the number of points grows from $M$ to nearly $M^2$ every generation. This is a "Simulation Trap" that may TLE on very large test cases.


* 
**Space Complexity:** Exponential. Every unique point generated is stored in the `std::set`, which can lead to memory exhaustion (MLE) if the target is far away.