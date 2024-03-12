#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <span>
#include <fstream>
#include <chrono>

#include "OpCounter.h"
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

void writeResultsToCSV(const string &filename, const string &functionName,const string &typevector,int nbelements, size_t comparisons, size_t assignments,double time)
{
    ofstream outputFile(filename, ios::app);
    if (outputFile.is_open())
    {
        outputFile << functionName << ";" << typevector<< ";" << nbelements << ";" << comparisons << ";" << assignments<< ";" << time << endl;
        outputFile.close();
    }
    else
    {
        cerr << "Erreur : Impossible d'ouvrir le fichier CSV." << endl;
    }
}

template <typename T>
double measureTime(void (*sortFunction)(span<T>), vector<T> data)
{
    OpCounter::reset_all();
    auto start = chrono::high_resolution_clock::now();
    sortFunction(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

int main()
{
    const int seed = 1;
    const string csvFilename = "../../rapport/csv/example.csv";
    vector<int> sizes = {100, 500, 1000, 5000, 10000};

    // Écriture de l'en-tête du fichier CSV
    ofstream headerFile(csvFilename);
    if (headerFile.is_open())
    {
        headerFile << "Tri;type de vector;Nombre d'éléments du vector;Comparaisons;Affectations;Temps" << endl;
        headerFile.close();
    }
    else
    {
        cerr << "Erreur : Impossible de créer le fichier CSV." << endl;
        return 1;
    }

    for (int size : sizes)
    {
        // Générer les vecteurs pour chaque type d'entrée
        vector<OpCounter> sortedVector = generateInputVector<OpCounter>(size, seed, InputType::SortedAscending);
        vector<OpCounter> descendingVector = generateInputVector<OpCounter>(size, seed, InputType::SortedDescending);
        vector<OpCounter> randomDistinctVector = generateInputVector<OpCounter>(size, seed, InputType::RandomDistinct);
        vector<OpCounter> almostSortedVector = generateInputVector<OpCounter>(size, seed, InputType::AlmostSorted);

        double time;
        //Tris a bulle
        time = measureTime( tri_a_bull<OpCounter>,sortedVector);
        writeResultsToCSV(csvFilename, "Tri à Bulles","(Sorted)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( tri_a_bull<OpCounter>,descendingVector);
        writeResultsToCSV(csvFilename, "Tri à Bulles","(Descending)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( tri_a_bull<OpCounter>,randomDistinctVector);
        writeResultsToCSV(csvFilename, "Tri à Bulles","(Random Distinct)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( tri_a_bull<OpCounter>,almostSortedVector);
        writeResultsToCSV(csvFilename, "Tri à Bulles","(Almost Sorted)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        //Tri par sélection
        time = measureTime( tri_par_selection<OpCounter>,sortedVector);
        writeResultsToCSV(csvFilename, "Tri par sélection","(Sorted)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( tri_par_selection<OpCounter>,descendingVector);
        writeResultsToCSV(csvFilename, "Tri par sélection","(Descending)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( tri_par_selection<OpCounter>,randomDistinctVector);
        writeResultsToCSV(csvFilename, "Tri par sélection","(Random Distinct)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( tri_par_selection<OpCounter>,almostSortedVector);
        writeResultsToCSV(csvFilename, "Tri par sélection","(Almost Sorted)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        //Tri par insertion
        time = measureTime( tri_par_insertion<OpCounter>,sortedVector);
        writeResultsToCSV(csvFilename, "Tri par insertion","(Sorted)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( tri_par_insertion<OpCounter>,descendingVector);
        writeResultsToCSV(csvFilename, "Tri par insertion","(Descending)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( tri_par_insertion<OpCounter>,randomDistinctVector);
        writeResultsToCSV(csvFilename, "Tri par insertion","(Random Distinct)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( tri_par_insertion<OpCounter>,almostSortedVector);
        writeResultsToCSV(csvFilename, "Tri par insertion","(Almost Sorted)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        //sortFunction
        time = measureTime( sortFunction<OpCounter>,sortedVector);
        writeResultsToCSV(csvFilename, "sortFunction","(Sorted)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( sortFunction<OpCounter>,descendingVector);
        writeResultsToCSV(csvFilename, "sortFunction","(Descending)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( sortFunction<OpCounter>,randomDistinctVector);
        writeResultsToCSV(csvFilename, "sortFunction","(Random Distinct)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( sortFunction<OpCounter>,almostSortedVector);
        writeResultsToCSV(csvFilename, "sortFunction","(Almost Sorted)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        //sortStableFunction
        time = measureTime( sortStableFunction<OpCounter>,sortedVector);
        writeResultsToCSV(csvFilename, "sortStableFunction","(Sorted)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( sortStableFunction<OpCounter>,descendingVector);
        writeResultsToCSV(csvFilename, "sortStableFunction","(Descending)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( sortStableFunction<OpCounter>,randomDistinctVector);
        writeResultsToCSV(csvFilename, "sortStableFunction","(Random Distinct)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);
        time = measureTime( sortStableFunction<OpCounter>,almostSortedVector);
        writeResultsToCSV(csvFilename, "sortStableFunction","(Almost Sorted)", size,OpCounter::get_nb_comp(), OpCounter::get_nb_affec(),time);


        cout << endl;
    }

    return 0;
}
