#include "evaluator.h"
#include <sstream>  // std::istringstream
#include <stack>    // std::stack
#include <cmath>    // std::pow
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool isOperator(const char& c){
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '<':
        case '>':
            return true;
        default:
            return false;
    }
}

double calcul(const char& op,const double& val1, const double& val2){
    switch (op) {
        case '+':
            return val1 + val2;
        case '-':
            return val1 - val2;
        case '*':
            return val1 * val2;
        case '/':
            if (val2 == 0)
                throw bad_exception();
            return val1 / val2;
        case '^':
            return std::pow(val1, val2);
        default:
            return 0.0;
    }
}

bool is_number(const std::string& s){
    try{
        std::stod(s);
    }
    catch(...){
        return false;
    }
    return true;
}

double evalue(string const& expr ){
    stack<char> pileOp {};
    stack<double> pileVal {};
    string temp{};
    string expression = expr;

    //Enlève les espaces
    expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());

    //Parcours l'expression
    for(size_t i = 0; i < expression.size(); ++i){
        temp += expression[i];

        //Ajoute dans une variable temp la valeur en entier exemple 23 on va mettre 2 puis 3 dans temp
        if (isdigit(expression[i]) && (i + 1) < expression.size()
        && isdigit(expression[i + 1])){
            continue;
        }

        //Ajoute si il y a un point dans la valeur
        if (isdigit(expression[i]) && (i + 1) < expression.size()
            && expression[i+1] == '.'){
            continue;
        }

        //Ajoute si il y a une valeur après la virgule
        if (expression[i] == '.' && (i + 1) < expression.size()
            && isdigit(expression[i + 1])){
            continue;
        }

        //Verifie si il y a 2 opérateur à la suite
        if ((i + 1) < expression.size() && isOperator(expression[i])
        && isOperator(expression[i+1]) && expression[i] == expression[i+1]){
            throw bad_expression();
        }

        string c = temp;
        temp = "";

        if (c == "("){
            //continue;
        } else if (isOperator(c[0])){
            //On change si c'est des opérateurs unaire pour pouvoir les différencier
            if ((i - 1 < 0 || expression[i-1] == '(' || isOperator(expression[i-1]) || i == 0) && c == "-"){
                c = "<"; //opérateur unaire -
            } else if ((i - 1 < 0 || expression[i-1] == '(' || isOperator(expression[i-1]) || i == 0) && c == "+"){
                c = ">"; //opérateur unaire +
            }

            pileOp.push(c[0]);
        } else if (is_number(c)){
            pileVal.push(stod(c));
        } else if (c == ")"){
            if (pileVal.size() < 2){
                throw bad_expression();
            }

            //Tant qu'il y a des opérateurs unaire dans la stack on les traites
            while (pileOp.top() == '<' || pileOp.top() == '>'){
                if (pileOp.top() == '<'){
                    pileVal.top() *= -1;
                }
                pileOp.pop();
            }

            double v2 = pileVal.top();
            pileVal.pop();

            double v1 = pileVal.top();
            pileVal.pop();

            char op = pileOp.top();
            pileOp.pop();

            double r = calcul(op, v1, v2);
            pileVal.push(r);
        }
    }

    if (!pileOp.empty()){
        if (pileOp.top() == '<'){
            pileVal.top() *= -1;
        }else{
            throw bad_expression();
        }
    }

    return pileVal.top();
}


/**
 * (-2+3) n'est pas bien traité, car je mon code fait (3+2)*(-1) comme après le 2 il y un opérateur uniaire
 * Je ne vois pas comment faire pour différencier un opérateur unaire entre -(2+3) et (-2+3)
 * ceci est un exemple parmi tous les cas où le '-' est entre '(' et une valeur
 */



