# Systems and C Practice

A collection of C programming and systems-oriented practice projects focused on:

- File handling and persistence
- String processing
- Dynamic memory allocation
- Recursive algorithms
- Sorting and comparison logic
- State management and undo/redo systems

## Projects

### Expense Manager
A simple file-based expense tracker supporting:
- adding expenses
- viewing stored records
- computing totals
- resetting records

Concepts:
- file I/O
- formatted input/output
- persistent storage

---

### Chronicle Editor (undo/redo editor)
A lightweight text modification engine supporting:
- insert
- delete
- undo
- redo

Concepts:
- state management
- string manipulation
- file-backed updates

---

### String Similarity Engine
A string matching and ranking engine implementing:
- substring/subsequence generation
- custom similarity metrics
- lexicographic sorting
- dynamic candidate filtering

Concepts:
- recursion
- combinatorics
- qsort comparators
- dynamic memory allocation

---

## Running the tests

Each project has a `compile_run.sh` that compiles the program and checks it against the sample cases in `input/` and `output/`:

```bash
cd "Chronicle Editor"          && bash compile_run.sh Chronicle_Editor.c 1
cd "String Similarity Engine"  && bash compile_run.sh String_Similarity_Engine.c 2
cd "Expense Manager"           && bash compile_run.sh Expense_Manager.c
```

The second argument is the number of test cases.
