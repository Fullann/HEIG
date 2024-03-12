/**
 * Laboratoire sur l'exercice 5.13
 * Author : Nathan Füllemann
 * Date : 06.11.2023
 * Updated on :
 *
 * Name:  Remplacement de chaînes dans un string
 * Desc :   Ce programme remplace toutes les occurrences d'une chaîne par une autre dans un string
 */

#include <iostream>
#include <string>
#include <locale>
#include <fstream>

using namespace std;

string &replace_all(string &str, const string &from, const string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
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

        string from = "de ";
        string to = "xYxYx";


        replace_all(text, from, to);

        cout << "Texte modifié : " << text << endl;
    }
    else
    {
        cerr << "Erreur lors de l'ouverture du fichier." << endl;
    }

    return 0;
}
