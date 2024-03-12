/**
 * Laboratoire 9.1
 * Author : Nathan Füllemann
 * Date : 09.10.2023
 *
 * Name:    Calcul de pi
 * Desc :   Ce programme estime la valeur de pi en utilisant la méthode de Monte Carlo
 */
#include <iostream>
#include <random>
using namespace std;
int main()
{
    // Initialisation du générateur de nombres aléatoires
    random_device rd;                                 // Utilisé pour initialiser le générateur
    mt19937 gen(rd());                                // Générateur Mersenne Twister
    uniform_real_distribution<double> dist(0.0, 1.0); // Distribution uniforme entre 0 et 1

    int numPoints = 1000000;    // Nombre de points à générer
    int pointsInsideCircle = 0; // Compteur de points à l'intérieur du cercle unité

    for (int i = 0; i < numPoints; ++i)
    {
        double x = dist(gen); // Générer une coordonnée x aléatoire entre 0 et 1
        double y = dist(gen); // Générer une coordonnée y aléatoire entre 0 et 1

        // Vérifier si le point est à l'intérieur du cercle unité
        if (x * x + y * y <= 1.0)
        {
            pointsInsideCircle++;
        }
    }

    // Estimer la valeur de π en utilisant la formule (points à l'intérieur du cercle / nombre total de points) * 4
    double estimatedPi = static_cast<double>(pointsInsideCircle) / static_cast<double>(numPoints) * 4.0;

    cout << "Estimation de pi: " << estimatedPi << endl;

    return 0;
}
