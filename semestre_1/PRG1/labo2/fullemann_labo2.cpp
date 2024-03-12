/**
 * Laboratoire 2
 * Author : Nathan Füllemann
 * Date : 19.09.2023
 *
 * Name: Convert Seconde
 * Desc : Petit programme de conversion de seconde en temps avec le nombre de semaine / jours / heures / secondes
 */
#include <iostream>
using namespace std;

int main()
{
    const int secInSemaine = 604800; // 1 semaine = 7 jours * 24 heures * 60 minutes * 60 secondes
    const int secInDay = 86400;      // 1 jour = 24 heures * 60 minutes * 60 secondes
    const int secInHeures = 3600;    // 1 heure = 60 minutes * 60 secondes
    const int secInMin = 60;         // 1 minute = 60 secondes

    int secondes;

    // Demande à l'utilisateur d'entrer le nombre de secondes
    cout << "Entrez le nombre de secondes : ";
    cin >> secondes;
    const int input = secondes;
    //Si nombre de seconde negatif
    if (input < 0){
        cout << "Le nombre de seconde ne peut pas etre negatif";
        return 0;
    }
    // Calcul des semaines, jours, heures, minutes et secondes
    int semaines = secondes / secInSemaine;
    secondes %= secInSemaine;
    int jours = secondes / secInDay;
    secondes %= secInDay;
    int heures = secondes / secInHeures;
    secondes %= secInHeures;
    int minutes = secondes / secInMin;
    secondes %= secInMin;

    // Affichage du résultat
    cout << input << " s = ";
    if (semaines > 0)
    {
        cout << semaines << " semaines, ";
    }
    if (jours > 0)
    {
        cout << jours << " jours, ";
    }
    if (heures > 0)
    {
        cout << heures << " heures, ";
    }
    if (minutes > 0)
    {
        cout << minutes << " minutes, ";
    }
    cout << secondes << " secondes" << endl;
}
