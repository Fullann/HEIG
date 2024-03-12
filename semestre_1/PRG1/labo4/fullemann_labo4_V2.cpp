/**
 * Laboratoire 4
 * Author : Nathan Füllemann
 * Date : 25.09.2023
 *
 * Name: Montre sans trotteuse
 * Desc : Programme qui permet de calculer les minutes et secondes à partir d'un angle.
 */
#include <iostream>
#include <cmath>  

using namespace std;

int main()
{
    const int angleRotation = 90; //Un quart du cadran en angle 
    const int secondesParAngle = 10; //Permet de changer pour passer en dixième
    const int angleCercle = 360; // Le nombre d'angle dans un cercle
    const int secondesParMinute = 60; //Nombre de seconde par minutes

    double angle;
    double time;
    double seconds;
    int minutes;

    cout <<"Entrez l'angle (en dixièmes de degrés) de l'aiguille des minutes : ";
    cin >> angle;

    // Calcul de l'angle par rapport a la vertical
    angle = fmod( angle / secondesParAngle, angleCercle);
    angle = angleCercle + angleRotation - angle;
    angle = fmod(angle, angleCercle);

    // Calcul des minutes et des secondes
    time = angle * secondesParAngle;
    minutes = static_cast<int>(time) / secondesParMinute;
    seconds = fmod(time, secondesParMinute);

    cout << minutes << " minutes et " << seconds << " secondes" << endl;
}
