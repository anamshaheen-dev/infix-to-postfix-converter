/*
    Tokenizer and Input Validator
    Compiler Construction Project
    Branch: member2-tokenizer
    Developer: Raffia Pervaiz (085)

    This program reads an infix expression and breaks it into
    individual tokens (operands, operators, parentheses). It also
    checks that the expression is valid before it gets converted
    to postfix - balanced parentheses, no missing operands, etc.
*/

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

bool isOperand(char c) {
    return isalnum(c);
}

// Splits the expression into a list of tokens.
// Each operand, operator, and parenthesis becomes its own entry.
vector<string> tokenize(const string& expr) {
    vector<string> tokens;

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (c == ' ') {
            continue; // skip spaces
        }
        else if (isOperand(c)) {
            tokens.push_back(string(1, c));
        }
        else if (c == '(' || c == ')') {
            tokens.push_back(string(1, c));
        }
        else if (isOperator(c)) {
            tokens.push_back(string(1, c));
        }
        else {
            cout << "Warning: Unknown character '" << c << "' skipped.\n";
        }
    }

    return tokens;
}

// Checks that every '(' has a matching ')' and vice versa.
bool isBalanced(const vector<string>& tokens) {
    int count = 0;
    for (const string& t : tokens) {
        if (t == "(") count++;
        if (t == ")") count--;
        if (count < 0) return false; // ')' came before its '('
    }
    return count == 0;
}

// Checks that operators are not placed back-to-back,
// and that the expression doesn't start or end with an operator.
bool hasValidOperatorPlacement(const vector<string>& tokens) {
    if (tokens.empty()) return false;

    // first token cannot be an operator (unless it's '(')
    if (tokens.front().length() == 1 && isOperator(tokens.front()[0])) {
        return false;
    }
    // last token cannot be an operator
    if (tokens.back().length() == 1 && isOperator(tokens.back()[0])) {
        return false;
    }

    for (size_t i = 0; i < tokens.size() - 1; i++) {
        bool currentIsOp = tokens[i].length() == 1 && isOperator(tokens[i][0]);
        bool nextIsOp    = tokens[i + 1].length() == 1 && isOperator(tokens[i + 1][0]);

        if (currentIsOp && nextIsOp) {
            return false; // two operators in a row, e.g. "A + * B"
        }
    }

    return true;
}

// Runs all validation checks together.
// Returns true if the expression is valid, prints a message if not.
bool validateExpression(const vector<string>& tokens) {
    if (tokens.empty()) {
        cout << "Error: Expression is empty.\n";
        return false;
    }
    if (!isBalanced(tokens)) {
        cout << "Error: Parentheses are not balanced.\n";
        return false;
    }
    if (!hasValidOperatorPlacement(tokens)) {
        cout << "Error: Operators are placed incorrectly.\n";
        return false;
    }
    return true;
}

// Prints the token list, useful for checking the output during testing.
void printTokens(const vector<string>& tokens) {
    cout << "Tokens: ";
    for (const string& t : tokens) {
        cout << "[" << t << "] ";
    }
    cout << "\n";
}

int main() {
    string infix;

    cout << "=========================================\n";
    cout << " Tokenizer and Validator\n";
    cout << " Compiler Construction Project\n";
    cout << "=========================================\n\n";

    cout << "Enter an infix expression:\n";
    cout << "Example: A + B * C - D / E\n";
    cout << "> ";
    getline(cin, infix);

    vector<string> tokens = tokenize(infix);

    cout << "\n";
    printTokens(tokens);

    if (validateExpression(tokens)) {
        cout << "Expression is valid and ready for conversion.\n";
    } else {
        cout << "Expression is invalid. Please fix it and try again.\n";
    }

    return 0;
}
