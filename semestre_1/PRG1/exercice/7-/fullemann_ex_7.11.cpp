#include <iostream>
#include <fstream>

using namespace std;

// Fonction pour extraire un caractère du nom de fichier caché à partir des composantes RGB
char extractChar(ifstream& imageFile) {
    char character = 0;
    for (int i = 0; i < 8; ++i) {
        char pixelValue;
        imageFile.read(&pixelValue, sizeof(pixelValue));
        character |= ((pixelValue & 1) << i);
    }
    return character;
}

// Fonction pour extraire la taille du fichier caché à partir des composantes RGB
unsigned int extractFileSize(ifstream& imageFile) {
    unsigned int fileSize = 0;
    for (int i = 0; i < 32; ++i) {
        char pixelValue;
        imageFile.read(&pixelValue, sizeof(pixelValue));
        fileSize |= ((pixelValue & 1) << i);
    }
    return fileSize;
}

int main() {
    string imagePath;
    cout << "Entrez le chemin de l'image BMP : ";
    cin >> imagePath;

    ifstream imageFile(imagePath, ios::binary);

    if (!imageFile) {
        cerr << "Erreur : Impossible d'ouvrir le fichier image." << endl;
        return 1;
    }

    // Aller à la position où les données cachées commencent (à l'octet 10 du fichier BMP)
    imageFile.seekg(10, ios::beg);
    int dataOffset;
    imageFile.read(reinterpret_cast<char*>(&dataOffset), sizeof(dataOffset));

    // Aller à la position où les données cachées commencent
    imageFile.seekg(dataOffset, ios::beg);

    // Extraire le nom du fichier caché
    string hiddenFileName;
    char currentChar = extractChar(imageFile);
    while (currentChar != '\0') {
        hiddenFileName += currentChar;
        currentChar = extractChar(imageFile);
    }

    // Extraire la taille du fichier caché
    unsigned int hiddenFileSize = extractFileSize(imageFile);

    cout << "Nom du fichier caché : " << hiddenFileName << endl;
    cout << "Taille du fichier caché : " << hiddenFileSize << " octets" << endl;

    // Revenir au début des données cachées
    imageFile.seekg(dataOffset + hiddenFileName.size() * 8 + 32, ios::beg);

    // Demander confirmation pour extraire le fichier
    char confirmation;
    cout << "Voulez-vous extraire le fichier ? (o/n) : ";
    cin >> confirmation;

    if (confirmation == 'o' || confirmation == 'O') {
        ofstream outputFile(hiddenFileName, ios::binary);

        if (!outputFile) {
            cerr << "Erreur : Impossible de créer le fichier de sortie." << endl;
            return 1;
        }

        // Copier les données cachées dans le fichier de sortie
        char pixelValue = 0;
        int bitCount = 0;
        while (imageFile && outputFile && bitCount < 8 * hiddenFileSize) {
            char bit;
            imageFile.read(&bit, sizeof(bit));
            pixelValue |= ((bit & 1) << (bitCount % 8));
            bitCount++;

            if (bitCount % 8 == 0) {
                outputFile.write(&pixelValue, sizeof(pixelValue));
                pixelValue = 0;
            }
        }

        cout << "Extraction réussie." << endl;
    } else {
        cout << "Extraction annulée par l'utilisateur." << endl;
    }

    return 0;
}
