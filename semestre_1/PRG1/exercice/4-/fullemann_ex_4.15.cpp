/**
 * Laboratoire sur l'exercice 4.15
 * Author : Nathan Füllemann
 * Date : 30.10.2023
 * Updated on :
 *
 * Name:   Cryptographie RSA
 * Desc :  Ce programme permet de générer une clé publique et privée pour crypter et décrypter des messages.
 */
#include <iostream>
#include <cmath>

using namespace std;
// Fonction pour vérifier si un nombre est premier
bool estPremier(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Fonction pour calculer l'inverse de e modulo phi
int inverseModulo(int e, int phi)
{
    int m0 = phi, t, q;
    int x0 = 0, x1 = 1;

    while (e > 1)
    {
        q = e / phi;
        t = phi;
        phi = e % phi, e = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int main()
{
    int p, q, e;

    cout << "Entrez deux nombres premiers distincts p et q : ";
    cin >> p >> q;

    if (!estPremier(p) || !estPremier(q) || p == q)
    {
        cout << "p et q doivent être des nombres premiers distincts." << endl;
        return 1;
    }

    int n = p * q;
    int phi = (p - 1) * (q - 1);

    cout << "Entrez un nombre premier e tel que 1 < e < " << phi << " : ";
    cin >> e;

    if (!estPremier(e) || e >= phi)
    {
        cout << "e doit être un nombre premier avec (p-1)*(q-1)." << endl;
        return 1;
    }

    int d = inverseModulo(e, phi);

    cout << "Clé publique (n, e) : (" << n << ", " << e << ")" << endl;
    cout << "Clé privée d : " << d << endl;

    // Vérification
    for (int m = 1; m < n; m++)
    {
        int c = 1;
        for (int i = 0; i < e; i++)
        {
            c = (c * m) % n;
        }

        int decrypted = 1;
        for (int i = 0; i < d; i++)
        {
            decrypted = (decrypted * c) % n;
        }

        if (m != decrypted)
        {
            cout << "La vérification a échoué pour m = " << m << endl;
            return 1;
        }
    }

    cout << "Vérification réussie. Vous pouvez crypter et décrypter des messages." << endl;

    return 0;
}
