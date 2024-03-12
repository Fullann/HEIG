#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <span>

#include "tris.cpp"
using namespace std;

// Enumération pour spécifier le type d'entrée à générer
enum class InputType
{
    SortedAscending,
    SortedDescending,
    RandomDistinct,
    AlmostSorted
};

// Fonction générant un vector<T> en fonction des paramètres spécifiés
template <typename T>
vector<T> generateInputVector(int N, int seed, InputType inputType)
{
    vector<T> inputVector(static_cast<unsigned long long int>(N));

    // Générateur de nombres aléatoires avec la possibilité de spécifier une graine
    mt19937 rng(static_cast<unsigned int>(seed));

    switch (inputType)
    {
    case InputType::SortedAscending:
        // Génération d'une séquence triée par ordre croissant
        iota(inputVector.begin(), inputVector.end(), T(1));
        break;

    case InputType::SortedDescending:
        // Génération d'une séquence triée par ordre décroissant
        iota(inputVector.rbegin(), inputVector.rend(), T(1));
        break;

    case InputType::RandomDistinct:
        // Génération d'une séquence aléatoire avec des valeurs toutes différentes
        iota(inputVector.begin(), inputVector.end(), T(1));
        shuffle(inputVector.begin(), inputVector.end(), rng);
        break;

    case InputType::AlmostSorted:
        // Génération d'une séquence "presque" triée sur tout le vecteur
        iota(inputVector.begin(), inputVector.end(), T(1));

        for (auto &elem : inputVector)
        {
            elem += static_cast<T>(rng() % 5);
        }
        break;
    }

    return inputVector;
}

template <typename T>
double measureTime(void (*sortFunction)(span<T>), vector<T> data)
{
    auto start = chrono::high_resolution_clock::now();
    sortFunction(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

// Fonction pour afficher les résultats
void printResults(const string &functionName, double time)
{
    cout << functionName << ": " << time << " seconds" << endl;
}

int main()
{
    const int seed = 42;

    vector<int> sizes = {100, 500, 1000, 5000, 10000};

    for (int size : sizes)
    {
        cout << "Size: " << size << endl;

        // Générer les vecteurs pour chaque type d'entrée
        vector<int> sortedVector = generateInputVector<int>(size, seed, InputType::SortedAscending);
        vector<int> descendingVector = generateInputVector<int>(size, seed, InputType::SortedDescending);
        vector<int> randomDistinctVector = generateInputVector<int>(size, seed, InputType::RandomDistinct);
        vector<int> almostSortedVector = generateInputVector<int>(size, seed, InputType::AlmostSorted);

        // Mesurer le temps d'exécution pour chaque fonction de tri
        double time;

        time = measureTime(tri_a_bull<int>, sortedVector);
        printResults("Tri à Bulles (Sorted)", time);
        time = measureTime(tri_a_bull<int>, descendingVector);
        printResults("Tri à Bulles (Descending)", time);
        time = measureTime(tri_a_bull<int>, randomDistinctVector);
        printResults("Tri à Bulles (Random Distinct)", time);
        time = measureTime(tri_a_bull<int>, almostSortedVector);
        printResults("Tri à Bulles (Almost Sorted)", time);

        time = measureTime(tri_par_selection<int>, sortedVector);
        printResults("Tri par sélection (Sorted)", time);
        time = measureTime(tri_par_selection<int>, descendingVector);
        printResults("Tri par sélection (Descending)", time);
        time = measureTime(tri_par_selection<int>, randomDistinctVector);
        printResults("Tri par sélection (Random Distinct)", time);
        time = measureTime(tri_par_selection<int>, almostSortedVector);
        printResults("Tri par sélection (Almost Sorted)", time);

        time = measureTime(tri_par_insertion<int>, sortedVector);
        printResults("Tri par insertion (Sorted)", time);
        time = measureTime(tri_par_insertion<int>, descendingVector);
        printResults("Tri par insertion (Descending)", time);
        time = measureTime(tri_par_insertion<int>, randomDistinctVector);
        printResults("Tri par insertion (Random Distinct)", time);
        time = measureTime(tri_par_insertion<int>, almostSortedVector);
        printResults("Tri par insertion (Almost Sorted)", time);

        time = measureTime(sortFunction<int>, sortedVector);
        printResults("sortFunction (Sorted)", time);
        time = measureTime(sortFunction<int>, descendingVector);
        printResults("sortFunction (Descending)", time);
        time = measureTime(sortFunction<int>, randomDistinctVector);
        printResults("sortFunction (Random Distinct)", time);
        time = measureTime(sortFunction<int>, almostSortedVector);
        printResults("sortFunction (Almost Sorted)", time);

        time = measureTime(sortStableFunction<int>, sortedVector);
        printResults("stable_sort (Sorted)", time);
        time = measureTime(sortStableFunction<int>, descendingVector);
        printResults("stable_sort (Descending)", time);
        time = measureTime(sortStableFunction<int>, randomDistinctVector);
        printResults("stable_sort (Random Distinct)", time);
        time = measureTime(sortStableFunction<int>, almostSortedVector);
        printResults("stable_sort (Almost Sorted)", time);

        cout << endl;
    }

    return 0;
}
