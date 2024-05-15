//IN (1+((2+3)*(4*5)))
//IN ( 1 + ( (2 + 3) * ( 4 * 5 ) ) )
//IN ( 100 + ( (21 + 32) * ( 42 * 5 ) ) )
//IN ( 1 - ( (2 + 0) * ( 4 * 52 ) ) )
//IN ( 2. ^ 10 )
//IN ( ( ( 30 / 12 ) * ( 12.5 * 4 ) ) - ( ( 42.2 * 5 ) + ( 5 + ( 3 ^ 2 ) ) ) )
//IN (1+((2+3)*(4*5))
//IN (+3)
//IN (2//3)

#include "evaluator.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

    cout << "Quelle expression voulez-vous évaluer ? \n";
    string expression;
    getline(cin, expression);

    try {
        cout << expression << " = " << evalue(expression) << "\n";
    } catch( bad_expression ) {
        cout << "Bad expression \n";
    }
}
