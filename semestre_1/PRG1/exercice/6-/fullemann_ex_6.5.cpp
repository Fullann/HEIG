/**
 * Laboratoire sur l'exercice 6.5
 * Author : Nathan Füllemann
 * Date : 14.11.2023
 * Updated on :
 *
 * Name: Update header WAV
 * Desc : Ce programme met à jour les valeurs de l'en-tête d'un fichier WAV
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;

void updateWavHeader(const char* fileName) {
    // Ouvrir le fichier en mode lecture et écriture binaire
    fstream file(fileName, ios::in | ios::out | ios::binary);

    if (!file.is_open()) {
        cerr << "Impossible d'ouvrir le fichier." << endl;
        return;
    }

    // Déplacer le curseur à la position de l'octet 4 pour lire la taille du fichier
    file.seekg(4, ios::beg);

    // Lire la taille du fichier actuelle
    uint32_t currentFileSize;
    file.read(reinterpret_cast<char*>(&currentFileSize), sizeof(currentFileSize));

    // Déplacer le curseur à la position de l'octet 40 pour lire la taille des données
    file.seekg(40, ios::beg);

    // Lire la taille des données actuelle
    uint32_t currentDataSize;
    file.read(reinterpret_cast<char*>(&currentDataSize), sizeof(currentDataSize));

    // Mettre à jour la taille du fichier dans l'en-tête
    file.seekp(4, ios::beg);
    uint32_t newFileSize = currentFileSize - 8; // Taille totale moins 8 octets
    file.write(reinterpret_cast<const char*>(&newFileSize), sizeof(newFileSize));

    // Mettre à jour la taille des données dans l'en-tête
    file.seekp(40, ios::beg);
    uint32_t newDataSize = currentFileSize - 40; // Taille totale moins 40 octets
    file.write(reinterpret_cast<const char*>(&newDataSize), sizeof(newDataSize));

    // Fermer le fichier
    file.close();

    cout << "Les valeurs de l'en-tête ont été mises à jour avec succès." << endl;
}

int main() {
    const char* fileName = "../dependence/fichier_incorrect.wav";

    updateWavHeader(fileName);

    return 0;
}
