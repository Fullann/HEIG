#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Mot {
public:
    // Constructeur avec un mot (initialise le nombre à 1)
    Mot(const string& mot) : mot(mot), nombre(1) {}

    // Fonction membre pour incrémenter le nombre
    void incrementerNombre() {
        nombre++;
    }

    // Fonction membre pour accéder au mot
    string getMot() const {
        return mot;
    }

    // Fonction membre pour accéder au nombre
    int getNombre() const {
        return nombre;
    }

private:
    string mot;
    int nombre;
};

// Fonction dichotomie pour trouver la position d'insertion ou du mot existant
int rechercheDichotomique(const vector<Mot>& lexique, const string& mot) {
    int debut = 0;
    int fin = lexique.size() - 1;

    while (debut <= fin) {
        int milieu = debut + (fin - debut) / 2;

        if (lexique[milieu].getMot() == mot) {
            return milieu; // Mot trouvé
        } else if (lexique[milieu].getMot() < mot) {
            debut = milieu + 1;
        } else {
            fin = milieu - 1;
        }
    }

    return debut; // Position d'insertion
}

// Fonction pour mettre à jour le lexique avec un nouveau mot
void mettreAJourLexique(vector<Mot>& lexique, const string& mot) {
    int position = rechercheDichotomique(lexique, mot);

    if (position < lexique.size() && lexique[position].getMot() == mot) {
        // Le mot existe déjà dans le lexique, donc on l'incrémente
        lexique[position].incrementerNombre();
    } else {
        // Le mot n'existe pas dans le lexique, on l'insère à la position trouvée
        Mot nouveauMot(mot);
        lexique.insert(lexique.begin() + position, nouveauMot);
    }
}

int main() {
    // Exemple d'utilisation
    vector<Mot> lexique;

    // Supposons que vous avez un texte et que vous divisez les mots
    vector<string> motsDuTexte = {"mot1", "mot2", "mot1", "mot3", "mot2"};

    // Construire le lexique en parcourant les mots du texte
    for (const string& mot : motsDuTexte) {
        mettreAJourLexique(lexique, mot);
    }

    // Afficher le lexique
    cout << "Lexique :\n";
    for (const Mot& mot : lexique) {
        cout << mot.getMot() << " : " << mot.getNombre() << " occurrences\n";
    }

    return 0;
}
