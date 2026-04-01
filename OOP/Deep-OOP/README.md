# Deep-OOP: Next-Gen Banking Engine (C++)

This project is a small OOP-based banking simulation written in C++.
It demonstrates inheritance, virtual functions (runtime polymorphism), separation of declaration/definition, namespaces, and multi-file build flow.

## 1. What This Project Is

This project has one base class and two derived account types:

- Base class: `Account`
- Derived class: `Saving`
- Derived class: `Crypto`

Main file creates objects through base pointers and calls `withdraw()`.
Because `withdraw()` is virtual in base class, the correct derived implementation runs at runtime.

## 2. Why This Project Structure Is Useful

1. Reusability
- Common fields (`accountHolderName`, `amount`) are in `Account`.
- Common behavior can stay in one place.

2. Extensibility
- New account types can be added by inheriting from `Account` and overriding `withdraw()`.

3. Maintainability
- `.h` files keep declarations.
- `.cpp` files keep logic.
- Changes become easier to track and debug.

4. Real OOP Understanding
- Inheritance: child classes reuse base members.
- Polymorphism: same interface, different behavior.
- Encapsulation: controlled access using `protected` and class methods.

## 3. Project File Map

- `Next-Gen-Banking-Engine.cpp`: entry point (`main`)
- `utils/account.h`: base class declaration
- `utils/account.cpp`: base class implementation
- `utils/savings.h`: saving class declaration
- `utils/savings.cpp`: saving class implementation
- `utils/crypto.h`: crypto class declaration
- `utils/crypto.cpp`: crypto class implementation

## 4. How The Flow Works (Step-by-Step)

### Step 1: Create Saving account via base pointer

Code idea:

```cpp
Account *acc = new Saving(interestRate, holderName, initialAmount);
acc->withdraw(1000);
```

What happens:
- Pointer type is `Account*`.
- Actual object type is `Saving`.
- Because `withdraw()` is virtual, `Saving::withdraw()` executes.

Result:
- Minimum balance rule in `Saving` is checked.

### Step 2: Create Crypto account via base pointer

Code idea:

```cpp
Account *acc2 = new Crypto(initialGas, initialAmount, holderName);
acc2->withdraw(5000);
```

What happens:
- Pointer type is `Account*`.
- Actual object type is `Crypto`.
- Runtime dispatch calls `Crypto::withdraw()`.

Result:
- Gas is checked.
- If gas > 0, withdrawal runs and gas decreases.

## 5. Example Input and Output

This program currently does not read from stdin.
Inputs are hardcoded inside `main`:

- `interestRate = 8`
- `initialAmount = 20000`
- `holderName = "NDK"`
- saving withdraw amount = `1000`
- crypto withdraw amount = `5000`

Observed output from build run:

```text
Withdrawl Success
Saving Amount: 19000
Yo All Set Crypt
Crypto Amount: 15000
```

## 6. What Is `.h` and Why It Is Used

`.h` files are header files.
They usually contain:

- class declarations
- function declarations
- type declarations
- constants/macros

Why:
- Multiple `.cpp` files can include the same declarations.
- Compiler knows function/class signatures before seeing implementation.
- Code organization is cleaner for medium/large projects.

## 7. What Is `#pragma once`

`#pragma once` is an include guard directive.
It tells compiler:

- Include this header only one time per translation unit.

Why needed:
- Prevents duplicate class/function declarations from repeated includes.
- Avoids redefinition errors.

Equivalent old style is macro guards:

```cpp
#ifndef ACCOUNT_H
#define ACCOUNT_H
// content
#endif
```

`#pragma once` is shorter and readable.

## 8. Build Pipeline: Source -> Object -> Linker -> Executable

When building this project with g++:

```bash
g++ Next-Gen-Banking-Engine.cpp utils/account.cpp utils/savings.cpp utils/crypto.cpp -o bank.exe
```

Internal stages:

1. Preprocessing
- Handles `#include`, `#pragma once`, macros.

2. Compilation
- Each `.cpp` compiles separately to assembly/object form.

3. Object Generation
- Produces `.o` object files (logical step, even if done in one command).

4. Linking
- Linker combines all object files.
- Resolves function/class symbols across files.
- Produces final executable (`bank.exe`).

## 9. Errors You Can Face In This Project and Fixes

### Error A: Header not found
Typical message:

```text
fatal error: utils/account.h: No such file or directory
```

Why:
- Wrong include path or wrong current working directory.

Fix:
- Compile from project root (`Deep-OOP`) or provide correct `-I` include path.
- Keep includes consistent with folder structure.

### Error B: Undefined reference at link time
Typical message:

```text
undefined reference to `Saving::withdraw(double)`
```

Why:
- Declaration exists in `.h`, but `.cpp` not linked.

Fix:
- Add all implementation files in compile command:
- `utils/account.cpp`, `utils/savings.cpp`, `utils/crypto.cpp`

### Error C: Multiple definition / redefinition
Typical message:

```text
redefinition of class Account
```

Why:
- Same header included multiple times without guard.

Fix:
- Keep `#pragma once` at top of headers.

### Error D: Namespace/type mismatch
Typical message:

```text
error: expected class-name before '{' token
```

Why:
- `Account` is inside `AccountNamespace` and referenced without proper scope.

Fix:
- Use full scope `AccountNamespace::Account` where needed.
- Or carefully use `using namespace AccountNamespace;`.

### Error E: Runtime logic issue (no balance check in Crypto)
Current behavior:
- `Crypto::withdraw` subtracts amount if gas > 0.
- It does not verify if balance is sufficient.

Impact:
- Amount can become negative.

Fix idea:
- Add balance check before subtraction.

### Error F: Memory management issue (allocated with `new`, never deleted)
Current behavior:
- `acc` and `acc2` are created with `new` and not deleted.

Impact:
- Memory leak for long-running process.

Fix options:
1. Use `delete acc; delete acc2;`
2. Better: use `std::unique_ptr<Account>`.

## 10. What Was Verified In This Workspace

Build verification done with:

```bash
g++ d:/DSA/OOP/Deep-OOP/Next-Gen-Banking-Engine.cpp d:/DSA/OOP/Deep-OOP/utils/account.cpp d:/DSA/OOP/Deep-OOP/utils/savings.cpp d:/DSA/OOP/Deep-OOP/utils/crypto.cpp -o d:/DSA/OOP/Deep-OOP/bank.exe
```

Result:
- Build succeeded.
- Program executed successfully and produced expected output.

## 11. How To Extend This Project

Add a new account type (example: `Business`):

1. Create `utils/business.h` and inherit from `Account`.
2. Override `withdraw(double)` with business-specific rules.
3. Implement in `utils/business.cpp`.
4. Include and test in `main`.
5. Add new `.cpp` to compile command.

This keeps the same OOP contract while adding custom behavior cleanly.

## 12. Quick Revision Summary

- `.h` = declarations, `.cpp` = implementations.
- `#pragma once` prevents duplicate header inclusion.
- Virtual methods enable runtime polymorphism.
- Build has compile + link stages.
- Most common failures are include path, linker missing files, namespace mismatch.
- Current code runs, but can be improved for balance checks and memory management.
