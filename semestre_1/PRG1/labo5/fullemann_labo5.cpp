/**
 * Laboratoire 5
 * Author : Nathan Füllemann
 * Date : 25.09.2023
 *
 * Name: Convert Seconde V2
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
    // Si nombre de seconde negatif
    if (input < 0)
    {
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
    // Check des semaines
    if (semaines > 0)
    {
        cout << semaines;
        if (semaines == 1)
        {
            cout << " semaine, ";
        }
        else
        {
            cout << " semaines, ";
        }
    }
    // Check des joures
    if (jours > 0)
    {
        cout << jours;
        if (jours == 1)
        {
            cout << " jour, ";
        }
        else
        {
            cout << " jours, ";
        }
    }
    // Check des heures
    if (heures > 0)
    {
        cout << heures;
        if (heures == 1)
        {
            cout << " heure, ";
        }
        else
        {
            cout << " heures, ";
        }
    }
    // Check des minutes
    if (minutes > 0)
    {
        cout << minutes;
        if (minutes == 1)
        {
            cout << " minute, ";
        }
        else
        {
            cout << " minutes, ";
        }
    }
    // Check des secondes
    if (secondes > 0)
    {
        if (minutes == 0 && heures == 0 && jours == 0 && semaines == 0)
        {
            cout << "Vous avez introduit " << secondes;
        }
        else
        {
            cout << secondes;
        }
        if (secondes == 1)
        {
            cout << " seconde";
        }
        else
        {
            cout << " secondes";
        }
    }

    cout << endl;
}
