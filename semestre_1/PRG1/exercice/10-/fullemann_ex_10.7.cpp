#include <iostream>
#include <cstdlib>

using namespace std;
// Fonction pour calculer le PGCD (Plus Grand Commun Diviseur)
int pgcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

class Rationnel {
private:
    int numerateur;
    int denominateur;

public:
    // Constructeur par défaut
    Rationnel() : numerateur(0), denominateur(1) {}

    // Constructeur avec numérateur et dénominateur
    Rationnel(int numerateur, int denominateur = 1) {
        if (denominateur == 0) {
            cerr << "Erreur : Division par 0." << endl;
            abort(); // Arrêter le programme en cas de division par 0
        }

        // Simplification du rationnel en divisant par le PGCD
        int gcd = pgcd(numerateur, denominateur);
        this->numerateur = numerateur / gcd;
        this->denominateur = denominateur / gcd;

        // Si le dénominateur est négatif, on inverse le signe du numérateur
        if (this->denominateur < 0) {
            this->numerateur = -this->numerateur;
            this->denominateur = -this->denominateur;
        }
    }

    // Opérateurs arithmétiques
    Rationnel operator+(const Rationnel& autre) const {
        return Rationnel(numerateur * autre.denominateur + autre.numerateur * denominateur, denominateur * autre.denominateur);
    }

    Rationnel operator-(const Rationnel& autre) const {
        return Rationnel(numerateur * autre.denominateur - autre.numerateur * denominateur, denominateur * autre.denominateur);
    }

    Rationnel operator*(const Rationnel& autre) const {
        return Rationnel(numerateur * autre.numerateur, denominateur * autre.denominateur);
    }

    Rationnel operator/(const Rationnel& autre) const {
        if (autre.numerateur == 0) {
            cerr << "Erreur : Division par 0." << endl;
            abort(); // Arrêter le programme en cas de division par 0
        }
        return Rationnel(numerateur * autre.denominateur, denominateur * autre.numerateur);
    }

    // Opérateurs de comparaison
    bool operator==(const Rationnel& autre) const {
        return (numerateur == autre.numerateur) && (denominateur == autre.denominateur);
    }

    bool operator<(const Rationnel& autre) const {
        return (numerateur * autre.denominateur) < (autre.numerateur * denominateur);
    }

    // Fonctions membres egal et plus_petit
    bool egal(const Rationnel& autre) const {
        return (*this == autre);
    }

    bool plus_petit(const Rationnel& autre) const {
        return (*this < autre);
    }

    // Fonction pour afficher le rationnel
    void afficher() const {
        cout << numerateur;
        if (denominateur != 1) {
            cout << '/' << denominateur;
        }
        cout << endl;
    }
};

int main() {
   
    Rationnel r1(1, 2);
    Rationnel r2(3, 4);

    Rationnel somme = r1 + r2;
    Rationnel difference = r1 - r2;
    Rationnel produit = r1 * r2;
    Rationnel quotient = r1 / r2;

    cout << "Somme : ";
    somme.afficher();

    cout << "Différence : ";
    difference.afficher();

    cout << "Produit : ";
    produit.afficher();

    cout << "Quotient : ";
    quotient.afficher();

    cout << "Comparaison : r1 == r2 ? " << (r1.egal(r2) ? "Oui" : "Non") << endl;
    cout << "Comparaison : r1 < r2 ? " << (r1.plus_petit(r2) ? "Oui" : "Non") << endl;

    return 0;
}
