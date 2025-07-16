# Generic HashSet in C 🧠📦

This project is a full implementation of a generic `HashSet` in C, using closed hashing with **quadratic probing** for collision resolution.  
Developed as part of an academic exercise, it demonstrates key data structure concepts, low-level memory handling, and API design in pure C.

---

## 🔧 Features

- ✅ Generic `HashSet` with support for custom types via user-defined hash & equality functions
- 🚀 Closed hashing with **quadratic probing** to resolve collisions
- 📈 Dynamic resizing based on **upper/lower load factors**
- ⚡ Optimized hash function using `x & (capacity - 1)` (for power-of-2 table sizes)
- 🧪 Includes **unit tests** with a simple test runner

---

## 📁 File Structure
- **Hashset.c** - Core logic (insert, erase, resize, etc.)
- **Hashset.h** - Public API definition
- **Node.c** - Internal key-value structure implementation
- **Node.h** - Node struct and related functions
- **Hash.h** - Simple hash functions for ints, strings, etc
- **Utils.h** - Utility macros and conversion helpers

## Testing Framework
- **tests.c** (Contains test cases)
- **test_runner.c** (Lightweight test execution engine)
- **test_runner.h** (Header for the test runner)


---

## ⚙️ API Overview

You can use the `HashSet` like so (simplified pseudocode):

```c
HashSet* hs = hashSetAlloc(
    capacity,
    upperLoadFactor,
    lowerLoadFactor,
    hashFunction,
    equalityFunction,
    destroyValueFunction
);

hashSetInsert(hs, someValue);
bool exists = hashSetContains(hs, someValue);
hashSetErase(hs, someValue);
hashSetFree(hs);
```

The user supplies:
- A hash function (e.g. from Hash.h)
- An equality comparator
- A value destructor function (Optional)

---

## Running the Tests 🧪
Compile and run all tests using:

```bash
gcc -std=c99 -Wall -Wextra -o tests tests.c test_runner.c HashSet.c Node.c
./tests
```
**All tests will run automatically and report pass/fail status.**

---

## 🧠 Concepts Demonstrated
- Generic programming in C (using void*)
- Hashing & collision resolution strategies
- Memory management and error handling
- Closed hashing (open addressing) vs. separate chaining
- API design for reusable C modules
- Simple unit testing without external frameworks

---

## 📜 Hash Function Example
The default hash function for integers uses:

```bash
hash(x) = x & (capacity - 1)
```
Which is fast and valid for table sizes that are powers of 2 (capacity = 2^n).

More functions available in Hash.h, including support for:
- Integers
- Strings
- Floats (Via Casting)

---

## 📝 Notes
- Only Node.c and HashSet.c were required for submission, but the rest are provided for completeness.
- Code adheres to C99 and was tested in a Linux environment.
- Foolproofing was emphasized: the system gracefully handles invalid input (e.g. NULL).













