#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include "tri_rapide.h"
#include "tri_par_base.h"

using namespace std;

const unsigned SEED = 123456789;

int main() {
    // Utiliser une seed basée sur l'heure actuelle
    unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
    default_random_engine seedRandom(seed);

    // Taille du vecteur
    size_t size_vector = 100;

    // Générer des données aléatoires
    vector<unsigned> data(size_vector);
    generate(data.begin(), data.end(), [&]() { return seedRandom() % 100; });

    // Créer un vecteur trié pour vérification
    vector<unsigned> sortedVector(data);
    sort(sortedVector.begin(), sortedVector.end());

    // Afficher la taille du vecteur
    cout << "Sorting vectors of size " << size_vector << endl;

    cout << endl;


    vector<unsigned> tmp(data);
    // Tri en utilisant tri_comptage
    tri_comptage(data.begin(), data.end(), tmp.begin(), [](unsigned a) { return a; }, 100);
    cout << "tri_comptage: " << boolalpha << (tmp == sortedVector) << endl;

    tmp = data;
    tri_par_base<vector<unsigned>::iterator, 1>(tmp.begin(), tmp.end());
    cout << "tri_par_base (1): " << boolalpha << (tmp == sortedVector) << endl;

    tmp = data;
    tri_par_base<vector<unsigned>::iterator, 2>(tmp.begin(), tmp.end());
    cout << "tri_par_base (2): " << boolalpha << (tmp == sortedVector) << endl;

    tmp = data;
    tri_par_base<vector<unsigned>::iterator, 4>(tmp.begin(), tmp.end());
    cout << "tri_par_base (4): " << boolalpha << (tmp == sortedVector) << endl;

    tmp = data;
    tri_par_base<vector<unsigned>::iterator, 18>(tmp.begin(), tmp.end());
    cout << "tri_par_base (8): " << boolalpha << (tmp == sortedVector) << endl;

    tmp = data;
    tri_par_base<vector<unsigned>::iterator, 16>(tmp.begin(), tmp.end());
    cout << "tri_par_base (16): " << boolalpha << (tmp == sortedVector) << endl;

    // Tri en utilisant tri_rapide
    tmp = data;
    tri_rapide(tmp.begin(), tmp.end());
    cout << "tri_rapide: " << boolalpha << (tmp == sortedVector) << endl;

    cout << endl;

    return EXIT_SUCCESS;
}
