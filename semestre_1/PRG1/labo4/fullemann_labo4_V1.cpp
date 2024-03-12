/**
 * Laboratoire 4
 * Author : Nathan Füllemann
 * Date : 25.09.2023
 *
 * Name: Montre sans trotteuse
 * Desc : Programme qui permet de calculer les minutes et secondes à partir d'un angle.
 */

#include <iostream>
using namespace std;

int main()
{
    int angle;

    const int minToHorizontal = 15; // Nombre de minutes depuis la vertical pour etre a l'horizontal
    const int minInSec = 60; // Nombre de secondes dans une minutes
    const int verticalInMin = minToHorizontal * minInSec; // 15 * 60 => 900 angle de la vertical par rapport à la vertical

    cout << "Entrez l'angle (en dixièmes de degrés) de l'aiguille des minutes : ";
    cin >> angle;

    // Calcul des minutes et des secondes
    int minutes = (verticalInMin - angle) / minInSec; // Chaque minute correspond à 6 degrés (360 degrés / 60 minutes)
    int secondes = minInSec - (angle % minInSec);     // Chaque seconde correspond à 0,1 degré (6 degrés / 60 secondes)

    cout << "Il est : " << minutes << " min. et " << secondes << " s." << endl;

    return 0;
}
