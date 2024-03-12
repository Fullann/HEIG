/**
 * Laboratoire 8.3
 * Author : Nathan Füllemann
 * Date : 09.10.2023
 *
 * Name:   Affichage d'un carré avec des lettres partant de A
 * Desc :   Ce programme affiche un carré de lettres partant de A et allant jusqu'à la lettre la plus éloignée du centre demandé par l'utilisateur
 */
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cout << "Entrez la taille du carré : ";
    cin >> n;

    if (n < 1)
    {
        cout << "La taille doit être supérieure ou égale à 1." << endl;
        return 1;
    }

    for (int i = -n + 1; i < n; i++)
    {
        for (int j = -n + 1; j < n; j++)
        {
            char current_char = 'A' + max(abs(i), abs(j));
            cout << current_char;
        }
        cout << endl;
    }

    return 0;
}
