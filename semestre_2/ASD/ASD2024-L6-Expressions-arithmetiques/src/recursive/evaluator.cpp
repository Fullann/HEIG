#include "evaluator.h"
#include <cmath>
#include <algorithm>

using namespace std;

double applyOperation(char operation, double operand1, double operand2) {
    switch (operation) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 == 0)
                throw bad_expression();
            return operand1 / operand2;
        case '^':
            return std::pow(operand1, operand2);
        default:
            throw bad_expression();
    }
}

double evalue(string const& expression) {
    if (expression.empty()) {
        throw bad_expression();
    }

    string sanitizedExpression = expression;
    sanitizedExpression.erase(
            remove_if(sanitizedExpression.begin(), sanitizedExpression.end(), ::isspace),
            sanitizedExpression.end()
    );

    if (count(sanitizedExpression.begin(), sanitizedExpression.end(), '.') <= 1 &&
        all_of(sanitizedExpression.begin(), sanitizedExpression.end(), [](char c) { return (isdigit(c) || c == '.'); })) {
        return stod(sanitizedExpression);
    }

    size_t operatorIndex = 0;
    size_t parenthesisCount = 0;
    for (auto it = sanitizedExpression.begin(); it != sanitizedExpression.end(); ++it) {
        if (*it == '(') {
            ++parenthesisCount;
            continue;
        }

        if (*it == ')') {
            --parenthesisCount;
            continue;
        }

        static const string VALID_OPERATORS = "+-*/^";
        if (VALID_OPERATORS.find(*it) != string::npos && parenthesisCount == 1) {
            operatorIndex = static_cast<size_t>(distance(sanitizedExpression.begin(), it));
            break;
        }
    }

    string leftOperand = sanitizedExpression.substr(1, operatorIndex - 1);
    string rightOperand = sanitizedExpression.substr(operatorIndex + 1, sanitizedExpression.size() - operatorIndex - 2);

    double leftValue = evalue(leftOperand);
    double rightValue = evalue(rightOperand);

    return applyOperation(sanitizedExpression[operatorIndex], leftValue, rightValue);
}
