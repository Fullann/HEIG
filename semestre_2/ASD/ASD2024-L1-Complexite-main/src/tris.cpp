#include <iostream>
#include <span>

using namespace std;

/*
 * Tri à bulle
 */
template<typename T>
void tri_a_bull(span<T> v){
    size_t last = v.size();
    for (size_t j = 1; j < v.size(); ++j) {
        int check = 0;
        for (size_t i = 1; i < last; ++i){
            if (v[i] < v[i - 1]) {
                swap(v[i], v[i - 1]);
                check = 1;
            }
        }
        --last;

        if (check == 0)return;
    }
}

/*
 * Tri par selection
 */
template<typename T>
size_t indice_min(span<const T> v) {
    size_t imin = 0;
    for (size_t i = 1; i < v.size(); ++i){
        if (v[i] < v[imin]){
            imin = i;
        }
    }

    return imin;
}

template<typename T>
void tri_par_selection(span<T> v) {
    for (size_t i = 0; i < v.size()-1 ; ++i) {
        size_t imin = i + indice_min<T>(v.subspan(i));
        swap(v[i], v[imin]);
    }
}

/*
 * Tri par selection
 */
template<typename T>
void inserer_dernier_element(span<T> v) {
    if (v.size() < 2) return;
    T t = v.back();
    size_t i = v.size()-1;
    for (; i > 0 and t < v[i-1]; --i)
        v[i] = v[i-1];
    v[i] = t;
}

template<typename T>
void tri_par_insertion(span<T> v) {
    for (size_t i = 2; i <= v.size(); ++i) {
        inserer_dernier_element(v.first(i));
    }
}

// Fonction de tri pour std::sort avec std::span
template <typename T>
void sortFunction(std::span<T> data) {
    sort(data.begin(), data.end());
}


// Fonction de tri pour table_sort avec std::span
template <typename T>
void sortStableFunction(std::span<T> data) {
    stable_sort(data.begin(), data.end());
}
