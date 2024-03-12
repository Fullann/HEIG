#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
bool areVectorsEqual(const vector<T>& vec1, const vector<T>& vec2) {
    // Vérifie si les vecteurs ont la même taille
    if (vec1.size() != vec2.size()) {
        return false;
    }

    // Trie les vecteurs
    vector<T> sortedVec1 = vec1;
    vector<T> sortedVec2 = vec2;
    sort(sortedVec1.begin(), sortedVec1.end());
    sort(sortedVec2.begin(), sortedVec2.end());

    // Vérifie si les vecteurs triés sont des permutations l'un de l'autre
    return is_permutation(sortedVec1.begin(), sortedVec1.end(), sortedVec2.begin());
}

int main() {
    // Exemple d'utilisation
    vector<int> vector1 = {1, 2, 3, 4, 4, 5};
    vector<int> vector2 = {4, 3, 5, 2, 1, 4};

    if (areVectorsEqual(vector1, vector2)) {
        cout << "Les vecteurs sont égaux." << endl;
    } else {
        cout << "Les vecteurs ne sont pas égaux." << endl;
    }

    return 0;
}
