#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Rat.hpp"

using namespace std;

/**
 * @brief Affiche une ligne de la matrice
 * @param ligne La ligne à afficher
*/
void imprime_ligne(const vector<Rat>& ligne)
{
    for (const auto& coeff : ligne)
        cout << std::setw(6) << coeff << " ";
    cout << endl;
}

/**
 * @brief Affiche la matrice
 * @param matrice La matrice
 */
void imprime_matrice(const vector<vector<Rat>>& matrice)
{
    cout << "----------------------" << endl;
    for (const auto& ligne : matrice)
        imprime_ligne(ligne);
    cout << endl;
}

/**
 * @brief Effectue un pivotage sur la matrice
 * @param matrice La matrice
 * @param ligne La ligne du pivot
 * @param colonne La colonne du pivot
 */
void pivote(vector<vector<Rat>>& matrice, size_t ligne, size_t colonne)
{
    const size_t nb_lignes = matrice.size();
    const size_t nb_colonnes = matrice[0].size();

    for (size_t i = 0; i < nb_lignes; i++)
        if (i != ligne)
            for (size_t j = 0; j < nb_colonnes; j++)
                if (j != colonne)
                    matrice[i][j] = matrice[i][j] - matrice[i][colonne] * matrice[ligne][j] / matrice[ligne][colonne];

    for (size_t i = 0; i < nb_lignes; i++)
        if (i != ligne)
            matrice[i][colonne] = -matrice[i][colonne] / matrice[ligne][colonne];

    for (size_t j = 0; j < nb_colonnes; j++)
        if (j != colonne)
            matrice[ligne][j] = matrice[ligne][j] / matrice[ligne][colonne];

    matrice[ligne][colonne] = Rat(1) / matrice[ligne][colonne];
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <nom_du_fichier>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile.is_open())
    {
        cerr << "Erreur: Impossible d'ouvrir le fichier." << endl;
        return 1;
    }

    size_t m, n; // Variables pour le nombre de lignes et de colonnes
    infile >> m >> n; // Lecture des valeurs de m et n

    // Utilisation de vecteurs pour stocker la matrice
    vector<vector<Rat>> matrice(m, vector<Rat>(n));

    // Boucle de lecture des éléments de la matrice à partir du fichier
    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
            infile >> matrice[i][j];

    // Pivotages; arrêter le programme avec CTRL-C
    while (true)
    {
        imprime_matrice(matrice);
        cout << "Ligne et colonne du pivot : ";
        size_t i, j;
        cin >> i >> j;
        if (i < m and j < n && matrice[i][j] != Rat(0))
            pivote(matrice, i, j);
        else
            cout << "Pivot non valide !" << endl;
    }
}
