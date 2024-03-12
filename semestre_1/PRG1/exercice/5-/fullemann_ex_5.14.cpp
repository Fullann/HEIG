/**
 * Laboratoire sur l'exercice 5.14
 * Author : Nathan Füllemann
 * Date : 06.11.2023
 * Updated on :
 *
 * Name: Affichage des mots uniques
 * Desc :   Ce programme affiche tous les mots uniques d'un texte
 */

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <locale>

using namespace std;
// Fonction pour extraire et imprimer les mots du texte
void printUniqueWords(const string &text)
{
    unordered_set<string> uniqueWords;
    string currentWord;

    for (char c : text)
    {
        if (isalpha(c, locale::classic()) || (c & 0xC0) == 0xC0)
        {
            // Caractère alphabétique ou caractère spécial
            currentWord += c;
        }
        else if (!currentWord.empty())
        {
            // Mot complet trouvé, ajoutez-le à l'ensemble des mots uniques
            uniqueWords.insert(currentWord);
            currentWord.clear();
        }
    }

    for (const string &word : uniqueWords)
    {
        cout << word << endl;
    }
}

int main()
{
    ifstream inputFile("../dependence/les_miserables.txt");

    if (inputFile)
    {
        string text;
        char c;
        while (inputFile.get(c))
        {
            text += c;
        }

        printUniqueWords(text);
    }
    else
    {
        cerr << "Erreur lors de l'ouverture du fichier." << endl;
    }

    return 0;
}
