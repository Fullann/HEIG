/**
 * Laboratoire 8.1
 * Author : Nathan Füllemann
 * Date : 09.10.2023
 *
 * Name:    Calcul de la representation de nombre en binaire
 * Desc :   Ce programme calcule la représentation binaire d'un nombre entier non négatif
 */
#include <iostream>
using namespace std;

int main()
{
    unsigned int nombre;

    // Demander à l'utilisateur de saisir un nombre entier non négatif
    cout << "Entrez un nombre entier non négatif : ";
    cin >> nombre;

    if (nombre == 0)
    {
        cout << "La représentation binaire est : 0" << endl;
    }
    else
    {
        // Initialiser une chaîne de caractères pour stocker la représentation binaire
        string binaire = "";

        // Calculer la représentation binaire en inversant l'ordre des bits
        while (nombre > 0)
        {
            int bit = nombre % 2;
            binaire += to_string(bit);
            nombre /= 2;
        }

        // Afficher la représentation binaire en inversant l'ordre des bits
        cout << "La représentation binaire est : ";
        for (int i = binaire.length() - 1; i >= 0; i--)
        {
            cout << binaire[i];
        }
        cout << endl;
    }

    return 0;
}
