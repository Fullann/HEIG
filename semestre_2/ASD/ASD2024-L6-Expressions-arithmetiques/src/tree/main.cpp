//IN (1+((2+3)*(4*5)))
//IN ( 1 + ( (2 + 3) * ( 4 * 5 ) ) )
//IN ( 100 + ( (21 + 32) * ( 42 * 5 ) ) )
//IN ( 1 - ( (2 + 0) * ( 4 * 52 ) ) )
//IN ( ( ( 33 / 12 ) * ( 12 * 4 ) ) - ( ( 42 * 5 ) + ( 5 ^ 3) ) )
//IN ( ( (2 + 3) * ( 6 / 4 ) ) ^ 2)
//IN (1+((2+3)*(4*5))
//IN (+3)
//IN (2//3)

#include "Expression.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

    cout << "Quelle expression voulez-vous évaluer ? \n";

    try {
        Expression e(cin);
        cout << "Polish : " << e.to_pn() << endl;
        cout << "RPN    : " << e.to_rpn() << endl;
        cout << "Infix  : " << e.to_infix() << endl;
        cout << "Value  : " << double(e) << endl;
    } catch( bad_expression ) {
        cout << "Bad expression \n";
    }
}
