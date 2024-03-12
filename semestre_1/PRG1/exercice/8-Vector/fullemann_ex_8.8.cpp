/**
 * Laboratoire sur l'exercice 8.8
 * Author : Nathan Füllemann
 * Date : 20.11.2023
 * Updated on :
 *
 * Name:  Fibonacci
 * Desc : Ce programme calcule le nombre de Fibonacci fn pour une valeur de n donnée par l'utilisateur.
 */
#include <iostream>
#include <vector>

using namespace std;

// Fonction pour additionner deux vecteurs représentant des nombres en base 10
vector<int> add(const vector<int>& num1, const vector<int>& num2) {
    vector<int> resultat;

    int tailleMax = max(num1.size(), num2.size());
    int retenue = 0;

    for (int i = 0; i < tailleMax; ++i) {
        int chiffre1 = (i < num1.size()) ? num1[i] : 0;
        int chiffre2 = (i < num2.size()) ? num2[i] : 0;

        int somme = chiffre1 + chiffre2 + retenue;
        retenue = somme / 10;

        resultat.push_back(somme % 10);
    }

    if (retenue > 0) {
        resultat.push_back(retenue);
    }

    return resultat;
}

// Fonction pour calculer le nombre de Fibonacci fn
vector<int> fibonacci(int n) {
    vector<int> fn;

    if (n == 0) {
        fn.push_back(0);
    } else if (n == 1) {
        fn.push_back(1);
    } else {
        vector<int> fib_n_minus_1 = {0};
        vector<int> fib_n_minus_2 = {1};

        for (int i = 2; i <= n; ++i) {
            fn = add(fib_n_minus_1, fib_n_minus_2);
            fib_n_minus_1 = fib_n_minus_2;
            fib_n_minus_2 = fn;
        }
    }

    return fn;
}

int main() {
    // Demander à l'utilisateur une valeur de n
    int n;
    cout << "Entrez la valeur de n pour le nombre de Fibonacci : ";
    cin >> n;

    // Calculer le nombre de Fibonacci fn
    vector<int> resultatFibonacci = fibonacci(n);

    // Afficher le résultat
    cout << "Le nombre de Fibonacci fn pour n=" << n << " est : ";
    for (int i = resultatFibonacci.size() - 1; i >= 0; --i) {
        cout << resultatFibonacci[i];
    }
    cout << endl;

    return 0;
}
