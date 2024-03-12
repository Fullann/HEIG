/**
 * Laboratoire 7
 * Author : Nathan Füllemann
 * Date : 02.10.2023
 *
 * Name:    Calcul de la moyenne et de la variance
 * Desc :   Programme qui calcule la moyenne et la variance d'une série de nombres positifs
 */
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    vector<double> valeurs;
    double valeur;

    // Lire les valeurs non négatives
    do
    {
        cout << "Entrez une valeur (nombre négatif pour terminer) : ";
        cin >> valeur;

        if (valeur >= 0)
        {
            valeurs.push_back(valeur);
        }
    } while (valeur >= 0);

    // Calculer la moyenne
    double variance = 0.0;
    double somme = 0.0;
    int count = 0;
    int i = 0;

    while (i < valeurs.size())
    {
        somme += valeurs[i];
        count++;
        i++;
    }

    double moyenne = (count > 0) ? somme / count : 0.0;

    i = 0;
    while (i < valeurs.size())
    {
        variance += pow(valeurs[i] - moyenne, 2);
        i++;
    }

    variance /= valeurs.size();

    // Afficher la moyenne et la variance
    cout << "Moyenne : " << moyenne << endl;
    cout << "Variance : " << variance << endl;

    return 0;
}
