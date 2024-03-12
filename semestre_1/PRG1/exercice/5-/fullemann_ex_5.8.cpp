/**
 * Laboratoire sur l'exercice 5.8
 * Author : Nathan Füllemann
 * Date : 30.10.2023
 * Updated on :
 *
 * Name:   Produit de deux nombres binaires
 * Desc :  Ce programme calcule le produit de deux nombres binaires
 */
#include <iostream>
#include <string>
using namespace std;
string operator*(const string &lhs, const string &rhs)
{
    int len1 = lhs.length();
    int len2 = rhs.length();

    if (len1 == 0 || len2 == 0)
    {
        return "0"; // Produit de zéro avec n'importe quel nombre est zéro
    }

    string result(len1 + len2, '0'); // Initialise la chaîne résultat avec des zéros.

    for (int i = len1 - 1; i >= 0; i--)
    {
        int carry = 0;
        int num1 = lhs[i] - '0';

        for (int j = len2 - 1; j >= 0; j--)
        {
            int num2 = rhs[j] - '0';
            int product = (num1 * num2) + (result[i + j + 1] - '0') + carry;
            carry = product / 2;
            result[i + j + 1] = '0' + (product % 2);
        }

        result[i] = '0' + carry;
    }

    // Supprime les zéros non significatifs à gauche du résultat.
    int first_non_zero = result.find_first_not_of('0');
    if (first_non_zero != string::npos)
    {
        return result.substr(first_non_zero);
    }

    return "0"; // Si le résultat est zéro, retourne simplement "0".
}

int main()
{
    string binary1 = "110"; // Exemple : représentation binaire de 6
    string binary2 = "101"; // Exemple : représentation binaire de 5

    string product = binary1 * binary2;

    cout << "Produit en binaire inversé : " << product << endl;

    return 0;
}
