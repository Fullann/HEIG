#include "Expression.h"
#include <stack>
#include <cctype>
#include <cmath>
#include <sstream>

using namespace std;

Expression::Expression(istream& in) {
    char next_char;
    in >> next_char;
    if (isdigit(next_char) || next_char == '-') { // Ajout de la vérification pour les nombres négatifs
        in.putback(next_char);
        in >> value;
        is_leaf = true;
    } else if (next_char == '(') {
        lhs = new Expression(in);
        in >> op;
        rhs = new Expression(in);
        if (!(in >> next_char) || next_char != ')') { // Modification de la condition pour vérifier la fermeture de la parenthèse
            throw bad_expression();
        }
        is_leaf = false;
    } else {
        throw bad_expression();
    }
}

Expression::~Expression() {
    if (!is_leaf) {
        delete lhs;
        delete rhs;
    }
}

Expression::operator double() const noexcept {
    if (is_leaf) {
        return value;
    } else {
        double left_val = static_cast<double>(*lhs);
        double right_val = static_cast<double>(*rhs);
        switch (op) {
            case '+':
                return left_val + right_val;
            case '-':
                return left_val - right_val;
            case '*':
                return left_val * right_val;
            case '/':
                if (right_val == 0) {
                    throw bad_expression();
                }
                return left_val / right_val;
            case '^':
                return pow(left_val, right_val);
            default:
                throw bad_expression();
        }
    }
}

string op_to_string(char op) {
    string result;
    result.push_back(op);
    return result;
}

string Expression::to_pn() const {
    if (is_leaf) {
        return to_string(value);
    } else {
        return op_to_string(op) + " " + lhs->to_pn() + " " + rhs->to_pn();
    }
}

string Expression::to_rpn() const {
    if (is_leaf) {
        return to_string(value);
    } else {
        return lhs->to_rpn() + " " + rhs->to_rpn() + " " + op_to_string(op);
    }
}

string Expression::to_infix() const {
    if (is_leaf) {
        return to_string(value);
    } else {
        return "(" + lhs->to_infix() + " " + op_to_string(op) + " " + rhs->to_infix() + ")";
    }
}
