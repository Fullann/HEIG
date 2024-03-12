#include <iostream>
using namespace std;

int main() {
    string s1 = "ABC";
    
    cout << '|' << s1[1] << '|' << endl; // Affiche le caractère à l'indice 1 (B)
    cout << '|' << s1[1] << '|' << endl; // Affiche le caractère à l'indice 1 (B)
    cout << '|' << s1[1] << '|' << endl; // Affiche le caractère à l'indice 1 (B)
    
    cout << '|' << s1[3] << '|' << endl; // Affiche le caractère à l'indice 3 (le caractère n'existe pas, résultat indéfini)
    cout << '|' << s1[4] << '|' << endl; // Affiche le caractère à l'indice 4 (le caractère n'existe pas, résultat indéfini)
    cout << '|' << s1.at(3) << '|' << endl; // Affiche le caractère à l'indice 3 (le caractère n'existe pas, provoque une exception std::out_of_range)

    string s7;
    cout << s7.length() << endl; // Affiche la longueur de la chaîne vide (0)
    
    cout << s1.length() << endl; // Affiche la longueur de la chaîne s1 (3)
    
    cout << s1.size() << endl; // Affiche la taille de la chaîne s1 (3)
    
    s1.resize(5); // Redimensionne s1 à la taille 5 en ajoutant des caractères nuls
    cout << '|' << s1 << '|' << endl; // Affiche la chaîne s1 redimensionnée (|ABC  |)
    
    string s11 = "ABC";
    s11.resize(2, 'x'); // Redimensionne s11 à la taille 2 en ajoutant des 'x'
    cout << '|' << s11 << '|' << endl; // Affiche la chaîne s11 redimensionnée (|AB|)
    
    string s12 = "ABC";
    s12.resize(4, 'x'); // Redimensionne s12 à la taille 4 en ajoutant des 'x'
    cout << '|' << s12 << '|' << endl; // Affiche la chaîne s12 redimensionnée (|ABxx|)
    
    string s13 = "ABCDE";
    cout << '|' << s13.substr(1, 2) << '|' << endl; // Extrait une sous-chaîne à partir de l'indice 1 de longueur 2 (|BC|)
    
    string s14 = "ABCDE";
    cout << '|' << s14.substr(0, 10) << '|' << endl; // Extrait une sous-chaîne de l'indice 0 à la longueur 10 (la chaîne est tronquée à |ABCDE|)
    
    string s15 = "ABCDE";
    cout << '|' << s15.substr(3) << '|' << endl; // Extrait une sous-chaîne à partir de l'indice 3 jusqu'à la fin (|DE|)
    
    string s16 = "ABCDE";
    cout << '|' << s16.substr() << '|' << endl; // Extrait la chaîne complète (|ABCDE|)
}
