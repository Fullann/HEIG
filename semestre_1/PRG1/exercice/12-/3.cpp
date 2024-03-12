#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

template <typename Iterator>
void tri_peigne(Iterator begin, Iterator end) {
    size_t delta = distance(begin, end);
    
    while (delta > 34) {
        delta /= 1.33;
        
        for (Iterator i = begin; distance(i, end) >= delta; ++i) {
            if (*i > *(i + delta)) {
                swap(*i, *(i + delta));
            }
        }
    }

    for (Iterator i = begin + 1; i < end; ++i) {
        auto tmp = *i;
        Iterator j = i;

        while (j > begin && *(j - 1) > tmp) {
            swap(*j, *(j - 1));
            --j;
        }

        *j = tmp;
    }
}

int main() {
    // Comparaison des temps avec std::sort
    vector<int> data;
    for (int i = 100; i <= 100000; i *= 10) {
        data.resize(i);
        
        // Remplir le vecteur avec des valeurs aléatoires
        generate(data.begin(), data.end(), []() { return rand(); });

        // Mesurer le temps pour le tri par peigne
        auto start_peigne = chrono::high_resolution_clock::now();
        tri_peigne(data.begin(), data.end());
        auto end_peigne = chrono::high_resolution_clock::now();
        auto duration_peigne = chrono::duration_cast<chrono::microseconds>(end_peigne - start_peigne);

        // Mesurer le temps pour std::sort
        auto start_sort = chrono::high_resolution_clock::now();
        sort(data.begin(), data.end());
        auto end_sort = chrono::high_resolution_clock::now();
        auto duration_sort = chrono::duration_cast<chrono::microseconds>(end_sort - start_sort);

        cout << "Nombre d'éléments : " << i << endl;
        cout << "Tri par peigne : " << duration_peigne.count() << " microseconds" << endl;
        cout << "std::sort : " << duration_sort.count() << " microseconds" << endl;
        cout << endl;
    }

    return 0;
}
