#include <iostream>
#include <vector>

using namespace std;

// Fonction pour afficher la matrice
void afficherMatrice(const vector<vector<bool>>& matrice) {
    for (const auto& ligne : matrice) {
        for (bool valeur : ligne) {
            cout << (valeur ? 'X' : '.');
        }
        cout << endl;
    }
}

// Fonction pour effectuer une itération du jeu de la vie
vector<vector<bool>> iterationJeuDeLaVie(const vector<vector<bool>>& matrice) {
    int lignes = matrice.size();
    int colonnes = matrice[0].size();

    vector<vector<bool>> nouvelleMatrice(lignes, vector<bool>(colonnes, false));

    // Parcourir chaque cellule dans la matrice
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            // Compter le nombre de voisins vivants
            int voisinsVivants = 0;

            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    if (x == 0 && y == 0) {
                        // Ignorer la cellule elle-même
                        continue;
                    }

                    int nouvelleLigne = i + x;
                    int nouvelleColonne = j + y;

                    // Vérifier si les indices sont valides
                    if (nouvelleLigne >= 0 && nouvelleLigne < lignes && nouvelleColonne >= 0 && nouvelleColonne < colonnes) {
                        voisinsVivants += matrice[nouvelleLigne][nouvelleColonne] ? 1 : 0;
                    }
                }
            }

            // Appliquer les règles du jeu de la vie
            if (matrice[i][j]) {
                // Cellule vivante
                nouvelleMatrice[i][j] = (voisinsVivants == 2 || voisinsVivants == 3);
            } else {
                // Cellule morte
                nouvelleMatrice[i][j] = (voisinsVivants == 3);
            }
        }
    }

    return nouvelleMatrice;
}

int main() {
    // Exemple d'utilisation
    vector<vector<bool>> matrice = {
        {false, true, false, false},
        {false, false, true, false},
        {true, true, true, false},
        {false, false, false, false}
    };

    cout << "Matrice initiale:" << endl;
    afficherMatrice(matrice);

    // Effectuer une itération du jeu de la vie
    matrice = iterationJeuDeLaVie(matrice);

    cout << "\nMatrice après une itération du jeu de la vie:" << endl;
    afficherMatrice(matrice);

    return 0;
}
