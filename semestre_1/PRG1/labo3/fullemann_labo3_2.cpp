/**
 * Laboratoire 3
 * Author : Nathan Füllemann
 * Date : 25.09.2023
 *
 * Name: Calcul durée trajet
 * Desc : Programme qui permet de calculer la durée d’un trajet
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main()
{
    const int minInHour = 60;
    const int minInDay = minInHour *24; //24 => Nombre d'heure dans un jours
    int heure_depart, minute_depart, heure_arrivee, minute_arrivee;

    cout << "Entrez l'heure de départ (hh mm) : ";
    cin >> heure_depart >> minute_depart;

    cout << "Entrez l'heure d'arrivée (hh mm) : ";
    cin >> heure_arrivee >> minute_arrivee;

    // Convertit les heures de départ et d'arrivée en minutes
    int depart_en_minutes = heure_depart * minInHour + minute_depart;
    int arrivee_en_minutes = heure_arrivee * minInHour + minute_arrivee + minInDay;

    // Calcule la durée du trajet en minutes
    int duree_en_minutes = arrivee_en_minutes - depart_en_minutes;
    duree_en_minutes = duree_en_minutes % (minInDay);

    // Calcule les heures et les minutes à partir de la durée en minutes
    int duree_heures = duree_en_minutes / minInHour;
    int duree_minutes = duree_en_minutes % minInHour;

    cout << "La durée du trajet est : " << duree_heures << "h " << duree_minutes << "min" << endl;
}
