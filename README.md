# Infix to Postfix Converter
### Compiler Construction Project

A program that converts infix expressions (like `A + B * C`) into postfix
notation (like `A B C * +`) using the Shunting Yard algorithm, written in C++.

---

## What This Project Does

When we write math expressions like `A + B * C`, computers struggle to evaluate
them directly because they need to track operator precedence and parentheses.

This program converts such expressions into **postfix notation**, which:
- Needs no parentheses
- Needs no precedence rules during evaluation
- Can be evaluated with a simple stack (left to right)

**Example:**
```
Input  (Infix):   A + B * C
Output (Postfix): A B C * +
```

---

## Team Members

| Member | Branch | Task |
|--------|--------|------|
| Anam Shaheen (Team Lead) | `lead-converter` | Core conversion algorithm (`converter.cpp`) using the Shunting Yard method |
| Raffia Pervaiz | `member2-tokenizer` | Tokenizer and input validator (`tokenizer.cpp`) |
| Amna Mehmood | `member3-docs-testing` | Test cases, test report, and documentation polish |

---

## Project Structure

```
infix-to-postfix-converter/
│
├── README.md            # This file
├── documentation.pdf     # Full project documentation with diagrams
├── converter.cpp         # Converts infix to postfix using Shunting Yard
├── tokenizer.cpp         # Splits expression into tokens and validates input
└── test_report.md        # Test cases and verified results
```

---

## How to Run

### Compile

```bash
g++ -o converter converter.cpp
g++ -o tokenizer tokenizer.cpp
```

### Run the tokenizer (checks if your expression is valid)

```bash
./tokenizer
```

### Run the converter (converts a valid expression to postfix)

```bash
./converter
```

---

## How It Works

1. The user enters an infix expression
2. `tokenizer.cpp` splits it into individual tokens and checks for errors
   (unbalanced parentheses, misplaced operators, empty input)
3. `converter.cpp` processes the valid tokens using a stack, applying
   operator precedence and associativity rules
4. The postfix expression is printed as output

---

## Operator Precedence Used

| Operator | Symbol | Precedence | Associativity |
|----------|--------|------------|----------------|
| Exponentiation | `^` | 3 (Highest) | Right |
| Multiplication / Division / Modulo | `* / %` | 2 | Left |
| Addition / Subtraction | `+ -` | 1 (Lowest) | Left |

---

## Test Results

15 test cases were run against the program — 11 valid expressions
and 4 invalid expressions — all producing the correct expected result.
Full details are in [test_report.md](test_report.md).

**Sample results:**

| Infix | Postfix |
|-------|---------|
| `A + B` | `A B +` |
| `A + B * C` | `A B C * +` |
| `( A + B ) * C` | `A B + C *` |
| `A ^ B ^ C` | `A B C ^ ^` |

---

## Diagrams

Full diagrams (Workflow Diagram, Data Flow Diagram, Algorithm
Flowchart) are included in [documentation.pdf](documentation.pdf).

---

## Subject
**Compiler Construction**
Submitted as a group project — 3 members
