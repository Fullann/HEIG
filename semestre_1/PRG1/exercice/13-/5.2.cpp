#include <iostream>
#include <stdexcept>
using namespace std;
ptrdiff_t somme_premiers_entiers(ptrdiff_t n) {
    if (n < 0) {
        throw invalid_argument("La valeur de n ne peut pas être négative.");
    }

    try {
        // Utilisation de la formule de la somme des n premiers entiers
        return (n * (n + 1)) / 2;
    } catch (const overflow_error& e) {
        throw runtime_error("Exception lors du calcul de la somme des entiers.");
    }
}

int main() {
    try {
        ptrdiff_t result = somme_premiers_entiers(10);
        cout << "La somme des 10 premiers entiers est : " << result << endl;
    } catch (const exception& e) {
        cerr << "Erreur : " << e.what() << endl;
    }

    return 0;
}
