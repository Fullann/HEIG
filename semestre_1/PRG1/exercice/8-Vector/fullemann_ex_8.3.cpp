#include <iostream>
#include <vector>
using namespace std;

vector<int> concatenerVecteurs(const vector<int>& vecteur1, const vector<int>& vecteur2) {
    // Créer un nouveau vecteur pour contenir la concaténation
    vector<int> resultat;

    // Insérer tous les éléments du premier vecteur
    resultat.insert(resultat.end(), vecteur1.begin(), vecteur1.end());

    // Insérer tous les éléments du deuxième vecteur
    resultat.insert(resultat.end(), vecteur2.begin(), vecteur2.end());

    // Retourner le vecteur résultant
    return resultat;
}

int main() {
    // Exemple d'utilisation de la fonction
    vector<int> vecteur1 = {1, 2, 3};
    vector<int> vecteur2 = {4, 5, 6};

    vector<int> resultat = concatenerVecteurs(vecteur1, vecteur2);

    // Afficher le résultat
    cout << "Vecteur concaténé : ";
    for (int element : resultat) {
        cout << element << " ";
    }
    cout << endl;

    return 0;
}
