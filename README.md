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
- Hashset.c # Core logic (insert, erase, resize, etc.)
- Hashset.h # Public API definition
- Node.c # Internal key-value structure implementation
- Node.h # Node struct and related functions
- Hash.h # Simple hash functions for ints, strings, etc
- Utils.h # Utility macros and conversion helpers

## Testing Framework
├── tests.c # Contains test cases
├── test_runner.c # Lightweight test execution engine
├── test_runner.h # Header for the test runner


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

The user supplies:
- A hash function (e.g. from Hash.h)
- An equality comparator
- A value destructor function (Optional)


## Running the Tests 🧪
Compile and run all tests using:

### to complete






