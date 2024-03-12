#include <iostream>
#include <vector>
using namespace std;

template <typename T>
ostream& operator<<(ostream& sortie, const vector<T>& vecteur) {
    sortie << "[ ";
    for (const T& element : vecteur) {
        sortie << element << " ";
    }
    sortie << "]";
    return sortie;
}

int main() {
    vector<int> vecteurEntiers = {1, 2, 3, 4, 5};

    // Utilisation de l'opérateur << surchargé pour afficher le vecteur
    cout << "Vecteur d'entiers : " << vecteurEntiers << endl;

    return 0;
}
