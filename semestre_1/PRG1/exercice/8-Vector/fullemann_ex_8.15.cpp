/**
 * Laboratoire sur l'exercice 8.15
 * Author : Nathan Füllemann
 * Date : 21.11.2023
 * Updated on :
 *
 * Name: ConvertirEnString
 * Desc : Ce programme permet de convertir un nombre en chaîne de caractères avec une base spécifiée.
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Fonction pour convertir un nombre en chaîne de caractères avec une base spécifiée
string convertirEnString(size_t nombre, int base = 10, int numeroTable = 0) {
    // Table de correspondance par défaut
    vector<string> tableCorrespondance = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    // Table de correspondance personnalisée (à ajouter si nécessaire)
    if (numeroTable == 1) {
        tableCorrespondance = {"zero", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf",
                               "A", "B", "C", "D", "E", "F"};
    }

    // Vérifier la validité de la base
    if (base < 2 || base > tableCorrespondance.size()) {
        return "Erreur: base invalide";
    }

    // Vérifier la validité du numéro de table
    if (numeroTable < 0 || numeroTable >= tableCorrespondance.size()) {
        return "Table de correspondance non disponible";
    }

    // Cas particulier : nombre égal à zéro
    if (nombre == 0) {
        return tableCorrespondance[0];
    }

    // Convertir le nombre en chaîne de caractères dans la base spécifiée
    string resultat = "";
    while (nombre > 0) {
        size_t reste = nombre % base;
        resultat = tableCorrespondance[reste] + " " + resultat;
        nombre /= base;
    }

    // Retirer l'espace à la fin
    resultat.pop_back();

    return resultat;
}

int main() {
    // Exemple d'utilisation
    size_t nombre;
    int base, numeroTable;

    cout << "Entrez un nombre : ";
    cin >> nombre;

    cout << "Entrez une base (par défaut 10) : ";
    cin >> base;

    cout << "Entrez le numéro de la table de correspondance (par défaut 0) : ";
    cin >> numeroTable;

    string resultat = convertirEnString(nombre, base, numeroTable);
    cout << "Résultat : " << resultat << endl;

    return 0;
}
