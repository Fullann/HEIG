/**
 * Laboratoire sur l'exercice 8.12
 * Author : Nathan Füllemann
 * Date : 20.11.2023
 * Updated on :
 *
 * Name: Matrice
 * Desc : Ce programme permet de manipuler une matrice.
 */
#include <iostream>
#include <iomanip>

using namespace std;

void imprime_ligne(double* ligne, size_t nb_colonnes)
{
    for (size_t j = 0; j < nb_colonnes; j++)
        cout << scientific << ligne[j] << " ";
    cout << endl;
}

void imprime_matrice(double** t, size_t nb_lignes, size_t nb_colonnes)
{
    cout << "----------------------" << endl;
    for (size_t i = 0; i < nb_lignes; i++)
        imprime_ligne(t[i], nb_colonnes);
    cout << endl;
}

void pivote(double** t, size_t nb_lignes, size_t nb_colonnes, size_t ligne, size_t colonne)
{
    for (size_t i = 0; i < nb_lignes; i++)
        if (i != ligne)
            for (size_t j = 0; j < nb_colonnes; j++)
                if (j != colonne)
                    t[i][j] = t[i][j] - t[i][colonne] * t[ligne][j] / t[ligne][colonne];

    for (size_t i = 0; i < nb_lignes; i++)
        if (i != ligne)
            t[i][colonne] = -t[i][colonne] / t[ligne][colonne];

    for (size_t j = 0; j < nb_colonnes; j++)
        if (j != colonne)
            t[ligne][j] = t[ligne][j] / t[ligne][colonne];

    t[ligne][colonne] = 1.0 / t[ligne][colonne];
}

int main()
{
    size_t nb_lignes, nb_colonnes;

    cout << "Entrez le nombre de lignes du système : ";
    cin >> nb_lignes;

    cout << "Entrez le nombre de colonnes du système : ";
    cin >> nb_colonnes;

    double** t = new double*[nb_lignes];
    for (size_t i = 0; i < nb_lignes; i++)
    {
        t[i] = new double[nb_colonnes];
        for (size_t j = 0; j < nb_colonnes; j++)
        {
            cout << "Introduire l'element de la ligne " << i
                 << " et de la colonne " << j << endl;
            cin >> t[i][j];
        }
    }

    while (1)
    {
        imprime_matrice(t, nb_lignes, nb_colonnes);
        cout << "ligne et colonne du pivot\n";
        size_t i, j;
        cin >> i >> j;
        if (i < nb_lignes and j < nb_colonnes and t[i][j] != 0.0)
            pivote(t, nb_lignes, nb_colonnes, i, j);
        else
            cout << "pivot non valide!\n";
    }

    // Libérer la mémoire allouée dynamiquement
    for (size_t i = 0; i < nb_lignes; i++)
        delete[] t[i];
    delete[] t;

    return 0;
}
