/**
 * Laboratoire sur l'exercice 6.4
 * Author : Nathan Füllemann
 * Date : 10.11.2023
 * Updated on :
 *
 * Name: Taille d'un fichier
 * Desc : Ce programme affiche la taille d'un fichier rentre par l'utilisateur
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Demander à l'utilisateur le nom du fichier
    cout << "Veuillez entrer le nom du fichier : ";
    string nomFichier;
    getline(cin, nomFichier);

    // Créer un objet ifstream pour le fichier
    ifstream fichier(nomFichier);

    // Vérifier si le fichier existe
    if (fichier) {
        // Le fichier existe, obtenir sa taille
        fichier.seekg(0, ios::end); // Se déplacer à la fin du fichier
        streampos taille = fichier.tellg(); // Obtenir la position actuelle, qui est la taille du fichier
        fichier.seekg(0, ios::beg); // Revenir au début du fichier

        // Afficher la taille du fichier
        cout << "La taille du fichier est : " << taille << " octets." << endl;
    } else {
        // Le fichier n'existe pas
        cout << "Le fichier n'existe pas." << endl;
    }

    // Fermer le fichier
    fichier.close();

    return 0;
}
