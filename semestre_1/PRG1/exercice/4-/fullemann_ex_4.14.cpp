/**
 * Laboratoire sur l'exercice 3.14
 * Author : Nathan Füllemann
 * Date : 17.10.2023
 * Updated on :
 *
 * Name:   Verification si un nombre est premier
 * Desc :  Ce programme verifie si un nombre entier fourni en paramètre est premier ou non
 */
#include <iostream>

using namespace std;

bool estPremier(int n)
{
    // Cas particuliers
    if (n <= 1)
    {
        return false;
    }

    if (n <= 3)
    {
        return true;
    }
    // Cas généraux
    if (n % 2 == 0 || n % 3 == 0)
    {
        return false;
    }
    // Boucle pour tester si le nombre est premier
    for (int i = 5; i * i <= n; i += 6)
    {
        // Si n est divisible par i ou i+2, alors n n'est pas premier
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int nombre;
    cout << "Entrez un nombre entier : ";
    cin >> nombre;

    if (estPremier(nombre))
    {
        cout << nombre << " est un nombre premier." << endl;
    }
    else
    {
        cout << nombre << " n'est pas un nombre premier." << endl;
    }

    return 0;
}
