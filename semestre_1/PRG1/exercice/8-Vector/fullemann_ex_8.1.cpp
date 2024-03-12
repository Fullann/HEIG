#include <iostream>
#include <vector>
using namespace std;

bool tousLesElementsPairs(const vector<int>& vecteur) {
    // Parcourir le vecteur
    for (int element : vecteur) {
        // Vérifier si l'élément est impair
        if (element % 2 != 0) {
            return false; // Si au moins un élément est impair, retourner false
        }
    }
    return true; // Si tous les éléments sont pairs, retourner true
}

int main() {
    // Exemple d'utilisation
    vector<int> vecteur1 = {2, 4, 6, 8, 10};
    vector<int> vecteur2 = {1, 2, 3, 4, 5};

    if (tousLesElementsPairs(vecteur1)) {
        cout << "Tous les éléments de vecteur1 sont pairs." << endl;
    } else {
        cout << "Il y a au moins un élément impair dans vecteur1." << endl;
    }

    if (tousLesElementsPairs(vecteur2)) {
        cout << "Tous les éléments de vecteur2 sont pairs." << endl;
    } else {
        cout << "Il y a au moins un élément impair dans vecteur2." << endl;
    }

    return 0;
}
