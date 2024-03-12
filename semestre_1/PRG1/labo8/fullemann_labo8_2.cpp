/**
 * Laboratoire 8.2
 * Author : Nathan Füllemann
 * Date : 09.10.2023
 *
 * Name:    Calcul du plus petit commun multiple
 * Desc :   Ce programme calcule le plus petit commun multiple de deux nombres entiers positifs
 */
#include <iostream>

using namespace std;
// Fonction pour calculer le plus grand commun diviseur
int pgcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main()
{
    int nombre1, nombre2;

    // Demander à l'utilisateur de saisir deux nombres positifs
    cout << "Entrez le premier nombre positif : ";
    cin >> nombre1;

    cout << "Entrez le deuxième nombre positif : ";
    cin >> nombre2;

    // Vérifier que les nombres sont positifs
    if (nombre1 <= 0 || nombre2 <= 0)
    {
        cerr << "Les nombres doivent être positifs." << endl;
        return 1; // Quitter le programme avec un code d'erreur
    }

    // Calculer le PGCD
    int pgcd_result = pgcd(nombre1, nombre2);

    // Calculer le ppmc en utilisant la formule LCM = (a * b) / PGCD(a, b)
    int ppmc = (nombre1 * nombre2) / pgcd_result;

    // Afficher le résultat
    cout << "Le plus petit commun multiple de " << nombre1 << " et " << nombre2 << " est : " << ppmc << endl;

    return 0;
}
