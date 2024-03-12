/**
 * Laboratoire 3
 * Author : Nathan Füllemann
 * Date : 25.09.2023
 *
 * Name: Addition longueur
 * Desc : Programme qui permet d’introduire deux longueurs (sous la forme de nombre entiers exprimés en kilomètres, mètres, centimètres et milimètres), de les additionner et d’afficher le résultat
 */
#include <iostream>
using namespace std;

int main()
{
    const int tailleTableauLongueur = 4;
    const int changeToMM[3] = {1000000, 1000, 10};

    int result;
    int longueur1[tailleTableauLongueur]; // Tableau pour la première longueur (km, m, cm, mm)
    int longueur2[tailleTableauLongueur]; // Tableau pour la deuxième longueur (km, m, cm, mm)

    // Demande à l'utilisateur d'entrer les deux longueurs
    cout << "Entrez la première longueur (km m cm mm) : ";
    cin >> longueur1[0] >> longueur1[1] >> longueur1[2] >> longueur1[3];

    cout << "Entrez la deuxième longueur (km m cm mm) : ";
    cin >> longueur2[0] >> longueur2[1] >> longueur2[2] >> longueur2[3];

    // Normalise les valeurs entrées en mm puis on les additionne
    result = longueur1[0] * changeToMM[0] + longueur1[1] * changeToMM[1] + longueur1[2] * changeToMM[2] + longueur1[3];
    result += longueur2[0] * changeToMM[0] + longueur2[1] * changeToMM[1] + longueur2[2] * changeToMM[2] + longueur2[3];

    // Calcul des unités
    long long kilometres = result / changeToMM[0];
    result %= changeToMM[0];

    long long metres = result / changeToMM[1];
    result %= changeToMM[1];

    long long centimetres = result / changeToMM[2];
    result %= changeToMM[2];

    // Affichage du résultat
    std::cout << longueur1[0] << " km, " << longueur1[1] << " m, " << longueur1[2] << " cm, " << longueur1[3] << " mm + ";
    std::cout << longueur2[0] << " km, " << longueur2[1] << " m, " << longueur2[2] << " cm, " << longueur2[3] << " mm font: \n";
    std::cout << kilometres << " km, " << metres << " m, " << centimetres << " cm, " << result << " mm";
}
