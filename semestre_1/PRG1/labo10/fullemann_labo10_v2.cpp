/**
 * Laboratoire 10
 * Author : Nathan Füllemann
 * Date : 09.10.2023
 * Updated on : 17.10.2023
 *
 * Name:   Calcul de la racine carrée d'un nombre entier positif
 * Desc :  Ce programme calcule la racine carrée d'un nombre entier positif en utilisant la méthode de Héron
 */
#include <iostream>
#include <iomanip>
using namespace std;

// Structure pour stocker la racine carrée et le nombre d'itérations
struct racine
{
    int iterations;
    double value;
};

double calculate_epsilon(int);
racine heron_sqrt(double, int);

int main()
{
    const int decimale = 10; // Nombre de decimales à afficher
    double x;
    int precision;

    // Demander à l'utilisateur d'entrer un nombre positif et la précision souhaitée
    cout << "Entrez le nombre x : ";
    cin >> x;
    cout << "Entrez la précision (nombre de bits significatifs) : ";
    cin >> precision;

    racine result = heron_sqrt(x, precision); // Calculer la racine carrée
    cout << "Racine carrée de " << x << " avec " << precision << " bits significatifs : " << fixed << setprecision(decimale) << result.value << endl;
    cout << "Nombre d'itérations : " << result.iterations << endl;

    return 0;
}
// Fonction pour calculer epsilon par rapport à la précision souhaitée
double calculate_epsilon(int precision)
{
    double result = 1.0;
    for (int i = 0; i < precision; i++)
    {
        result *= 2;
    }
    return 1 / result;
}

// Fonction pour calculer la racine carrée en utilisant l'algorithme de Héron
racine heron_sqrt(double x, int precision)
{
    int precision_min = 1;       // Précision minimale
    int precision_max = 50;      // Précision maximale
    int first_approximation = 2; // Première approximation de la racine carrée
    int iterations = 0;          // Compteur d'itérations

    // Vérification que le nombre est positif
    if (x <= 0)
    {
        cout << "Erreur : La racine carrée d'un nombre négatif n'est pas définie." << endl;
        racine error = {-1, 0.0 / 0.0};
        return error;
    }

    // Assurer que la précision est entre 1 et 50 bits
    precision = min(max(precision, precision_min), precision_max);

    double r = x / first_approximation;            // Première approximation de la racine carrée
    double epsilon = calculate_epsilon(precision); // Précision souhaitée convertie en epsilon
    while (abs(r - x / r) > epsilon * r)           // Continuer tant que la précision n'est pas atteinte
    {
        r = 0.5 * (r + x / r); // Améliorer l'approximation en utilisant l'algorithme de Héron
        iterations++;          // Incrémenter le compteur d'itérations
    }
    racine result = {iterations, r};
    return result; // Retourner la racine carrée et le nombre d'itérations
}