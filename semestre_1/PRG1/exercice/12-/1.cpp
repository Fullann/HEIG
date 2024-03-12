#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
using namespace std;

int main() {
    vector<int> v(10); // Assumons que le vecteur a une taille de 10 pour cet exemple

    // Mettre tous les éléments v à la valeur 1234
    fill(v.begin(), v.end(), 1234);

    // Remplir v avec des valeurs pseudo-aléatoires comprises entre 0 et 19
    generate(v.begin(), v.end(), []() { return rand() % 20; });

    // Vérifier que tous les éléments de v sont compris entre 0 et 19
    bool allInRange = all_of(v.begin(), v.end(), [](int x) { return x >= 0 && x <= 19; });

    // Compter le nombre d’éléments de valeur 6 dans v
    int countSix = count(v.begin(), v.end(), 6);

    // Compter le nombre d’éléments multiples de 6 dans v
    int countMultSix = count_if(v.begin(), v.end(), [](int x) { return x % 6 == 0; });

    // Trouver la position du dernier multiple de 11 différent de 0 dans v (−1 si aucun présent)
    auto itLastMult11 = find_if(v.rbegin(), v.rend(), [](int x) { return x % 11 == 0 && x != 0; });
    int positionLastMult11 = (itLastMult11 != v.rend()) ? v.rend() - itLastMult11 - 1 : -1;

    // Trouver la position de deux éléments identiques dans v
    auto itTwoIdentical = adjacent_find(v.begin(), v.end());
    int positionTwoIdentical = (itTwoIdentical != v.end()) ? distance(v.begin(), itTwoIdentical) : -1;

    // Trouver la position de 2 éléments consécutifs pairs dans v
    auto itTwoConsecutiveEven = search_n(v.begin(), v.end(), 2, 0, [](int x) { return x % 2 == 0; });
    int positionTwoConsecutiveEven = (itTwoConsecutiveEven != v.end()) ? distance(v.begin(), itTwoConsecutiveEven) : -1;

    // Trouver la position de 5 éléments consécutifs multiples de 3 dans v
    auto itFiveConsecutiveMult3 = search_n(v.begin(), v.end(), 5, 0, [](int x) { return x % 3 == 0; });
    int positionFiveConsecutiveMult3 = (itFiveConsecutiveMult3 != v.end()) ? distance(v.begin(), itFiveConsecutiveMult3) : -1;

    // Retourner la valeur du plus grand élément de v
    int maxElement = *max_element(v.begin(), v.end());

    // Faire une rotation de v de 5 positions vers la droite
    rotate(v.rbegin(), v.rbegin() + 5, v.rend());

    // Supprimer tous les multiples de 5 dans v (qui doit être éventuellement raccourci)
    v.erase(remove_if(v.begin(), v.end(), [](int x) { return x % 5 == 0; }), v.end());

    // Mélanger aléatoirement les éléments de v
    //random_shuffle(v.begin(), v.end());

    // Supprimer les éléments consécutifs identiques de v
    v.erase(unique(v.begin(), v.end()), v.end());

    // Afficher tous les éléments de v dans la console
    cout << "Elements of v: ";
    for (int elem : v) {
        cout << elem << " ";
    }
    cout << endl;

    // Multiplier tous les éléments de v par 5
    transform(v.begin(), v.end(), v.begin(), [](int x) { return x * 5; });

    // Diviser la seconde moitié des éléments de v par 5
    transform(v.begin() + v.size() / 2, v.end(), v.begin() + v.size() / 2, [](int x) { return x / 5; });

    // Trier les éléments de v par ordre décroissant
    sort(v.begin(), v.end(), greater<int>());

    // Re-trier les éléments de v par ordre croissant (alors qu’ils l’étaient par ordre décroissant)
    sort(v.begin(), v.end());

    // Retourner la somme des éléments de v
    int sumElements = accumulate(v.begin(), v.end(), 0);

    // Retourner le carré de la norme du vecteur v
    int squareNorm = inner_product(v.begin(), v.end(), v.begin(), 0);

    cout << "Sum of elements: " << sumElements << endl;
    cout << "Square of norm: " << squareNorm << endl;

    return 0;
}
