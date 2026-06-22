# Test Report
## Infix to Postfix Converter — Compiler Construction Project
### Branch: member3-docs-testing

This report documents the testing performed on the `converter.cpp`
and `tokenizer.cpp` modules. All test cases below were run directly
against the compiled programs and the actual output is recorded here.

---

## 1. How Testing Was Done

Each program was compiled using a standard C++ compiler:

```
g++ -o converter converter.cpp
g++ -o tokenizer tokenizer.cpp
```

Test expressions were then fed into each program, and the printed
output was compared against the expected result calculated by hand
using standard operator precedence and associativity rules.

---

## 2. Valid Expression Test Cases (Converter)

These test cases confirm that `converter.cpp` produces the correct
postfix expression for a range of operator combinations.

| # | Infix Expression | Postfix Output | Concept Tested | Result |
|---|---|---|---|---|
| 1 | A + B | A B + | Basic addition | Pass |
| 2 | A + B * C | A B C * + | * has higher precedence than + | Pass |
| 3 | ( A + B ) * C | A B + C * | Parentheses override precedence | Pass |
| 4 | A * B + C * D | A B * C D * + | Same-level operators, left to right | Pass |
| 5 | A + B * C - D / E | A B C * + D E / - | Mixed precedence levels | Pass |
| 6 | A ^ B ^ C | A B C ^ ^ | Right-associativity of ^ | Pass |
| 7 | ( ( A + B ) * C ) - D | A B + C * D - | Nested parentheses | Pass |
| 8 | A - B - C | A B - C - | Left-associativity of - | Pass |
| 9 | A / B / C | A B / C / | Left-associativity of / | Pass |
| 10 | ( A + B ) * ( C - D ) | A B + C D - * | Two separate parenthesis groups | Pass |
| 11 | A + ( B * C ) - D | A B C * + D - | Parentheses around a sub-expression | Pass |

**Result: 11 / 11 test cases passed.**

---

## 3. Invalid Expression Test Cases (Tokenizer)

These test cases confirm that `tokenizer.cpp` correctly detects and
rejects invalid input before it ever reaches the converter.

| # | Input | Expected Behavior | Actual Output | Result |
|---|---|---|---|---|
| 1 | `( A + B * C` | Reject — unbalanced parentheses | "Error: Parentheses are not balanced." | Pass |
| 2 | `A + * B` | Reject — two operators in a row | "Error: Operators are placed incorrectly." | Pass |
| 3 | `+ A B` | Reject — expression starts with an operator | "Error: Operators are placed incorrectly." | Pass |
| 4 | (empty input) | Reject — nothing entered | "Error: Expression is empty." | Pass |

**Result: 4 / 4 test cases passed.**

---

## 4. Observations

- The converter correctly applies operator precedence: `^` is treated
  as highest priority, followed by `*`, `/`, `%`, then `+`, `-`.
- Right-associativity is handled correctly for `^` — confirmed by
  test case 6, where `A ^ B ^ C` correctly becomes `A B C ^ ^`
  (meaning B and C are combined first, matching `A ^ (B ^ C)`).
- The tokenizer successfully catches the most common input mistakes:
  unbalanced brackets, double operators, and missing operands.

---

## 5. Known Limitations

- The current version only supports single-character operands
  (e.g. `A`, `B`, `5`). Multi-character variable names or multi-digit
  numbers are not yet supported.
- The tokenizer and converter currently run as two separate programs.
  In a future version, they could be combined so the tokenizer's
  output feeds directly into the converter automatically.

---

## 6. Conclusion

All 15 test cases (11 valid expressions + 4 invalid expressions)
produced the correct expected output. The converter and tokenizer
modules work as intended and are ready for final submission.
