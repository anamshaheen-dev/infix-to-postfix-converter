/*
    Infix to Postfix Converter
    Compiler Construction Project

    This file implements the CONVERTER part of the project —
    the Shunting Yard algorithm that takes a list of valid tokens
    and converts them into postfix notation using a stack.

    Branch: lead-converter
    Author: Team Lead (Anam Shaheen)
*/

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// ---------------------------------------------------------
// Returns the precedence level of an operator.
// Higher number = higher precedence.
// ---------------------------------------------------------
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0; // not an operator
}

// ---------------------------------------------------------
// Returns true if the operator is right-associative.
// Only '^' (exponentiation) is right-associative here.
// Example: A ^ B ^ C  =  A ^ (B ^ C)
// ---------------------------------------------------------
bool isRightAssociative(char op) {
    return op == '^';
}

// ---------------------------------------------------------
// Returns true if the character is a valid operator.
// ---------------------------------------------------------
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

// ---------------------------------------------------------
// Returns true if the character is a valid operand.
// Supports single letters (A-Z, a-z) and digits (0-9).
// ---------------------------------------------------------
bool isOperand(char c) {
    return isalnum(c);
}

// ---------------------------------------------------------
// MAIN FUNCTION: Converts an infix expression to postfix
// using the Shunting Yard algorithm.
//
// Steps:
//   1. Scan the expression left to right.
//   2. If operand -> add directly to output.
//   3. If '(' -> push onto stack.
//   4. If ')' -> pop to output until matching '(' is found.
//   5. If operator -> pop operators with higher/equal
//      precedence to output, then push current operator.
//   6. After scanning, pop all remaining operators to output.
// ---------------------------------------------------------
string infixToPostfix(const string& infix) {
    stack<char> operatorStack;
    string postfix = "";

    for (size_t i = 0; i < infix.length(); i++) {
        char token = infix[i];

        // Skip spaces
        if (token == ' ') {
            continue;
        }

        // Rule 1: Operand -> append directly to output
        if (isOperand(token)) {
            postfix += token;
            postfix += ' ';
        }
        // Rule 2: Left parenthesis -> push onto stack
        else if (token == '(') {
            operatorStack.push(token);
        }
        // Rule 3: Right parenthesis -> pop until matching '('
        else if (token == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix += operatorStack.top();
                postfix += ' ';
                operatorStack.pop();
            }
            if (!operatorStack.empty()) {
                operatorStack.pop(); // discard the '('
            }
        }
        // Rule 4: Operator -> pop higher/equal precedence operators first
        else if (isOperator(token)) {
            while (!operatorStack.empty() &&
                   operatorStack.top() != '(' &&
                   isOperator(operatorStack.top())) {

                char topOp = operatorStack.top();
                bool shouldPop;

                if (isRightAssociative(token)) {
                    shouldPop = precedence(topOp) > precedence(token);
                } else {
                    shouldPop = precedence(topOp) >= precedence(token);
                }

                if (!shouldPop) break;

                postfix += topOp;
                postfix += ' ';
                operatorStack.pop();
            }
            operatorStack.push(token);
        }
        // Anything else is invalid
        else {
            cout << "Warning: Invalid character '" << token << "' ignored.\n";
        }
    }

    // Pop all remaining operators from the stack
    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        postfix += ' ';
        operatorStack.pop();
    }

    return postfix;
}

// ---------------------------------------------------------
// Checks whether parentheses are balanced in the expression.
// (basic validation before conversion)
// ---------------------------------------------------------
bool isBalanced(const string& expr) {
    int count = 0;
    for (char c : expr) {
        if (c == '(') count++;
        if (c == ')') count--;
        if (count < 0) return false; // closed before opened
    }
    return count == 0;
}

// ---------------------------------------------------------
// MAIN PROGRAM
// ---------------------------------------------------------
int main() {
    string infix;

    cout << "=========================================\n";
    cout << " Infix to Postfix Converter\n";
    cout << " Compiler Construction Project\n";
    cout << "=========================================\n\n";

    cout << "Enter an infix expression (use spaces between tokens):\n";
    cout << "Example: A + B * C - D / E\n";
    cout << "> ";
    getline(cin, infix);

    // Step 1: Validate parentheses
    if (!isBalanced(infix)) {
        cout << "\nError: Unbalanced parentheses in expression.\n";
        return 1;
    }

    // Step 2: Convert
    string postfix = infixToPostfix(infix);

    // Step 3: Display result
    cout << "\nInfix Expression  : " << infix << "\n";
    cout << "Postfix Expression: " << postfix << "\n";

    return 0;
}
