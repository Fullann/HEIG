#include "ex_tri_fusion.hpp"
#include <iostream>
#include <chrono>
using namespace std;

// Tri par fusion pour des vector génériques
template <typename T>
void tri_fusion(vector<T> &v)
{
    if (v.size() < 2)
        return;                                            // Déjà trié, on ne fait rien
    vector<int> w(v.begin() + (int)v.size() / 2, v.end()); // Deuxième moitié de v
    v.resize(v.size() / 2);                                // Première moitié de v
    tri_fusion(v);
    tri_fusion(w);
    fusion_insertion(v, w); // v = fusion(v, w); si on n’optimise pas l’utilisation de la mémoire
}

int main()
{
    size_t n = 100;
    double temps; // Temps pour trier n nombres
    do
    {
        vector<int> v;
        v.reserve(n);
        for (size_t i = 0; i < n; ++i) // Création d’un vector de n entiers aléatoires
            v.push_back(rand());

        chrono::high_resolution_clock::time_point heure_avant =
            chrono::high_resolution_clock::now();
        tri_a_bulle(v);
        temps = chrono::duration_cast<chrono::duration<double> >(chrono::high_resolution_clock::now() - heure_avant).count();
        cout << n << " " << temps << endl;
        n *= 2;
    } while (temps < 20.0);

}