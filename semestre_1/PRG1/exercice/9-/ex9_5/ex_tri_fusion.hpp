/* Fichier ex_tri_fusion.hpp */
#include <vector>

/* Fusion de 2 vector supposément déjà triés, en utilisant un vector supplémentaire res avec plus ou moins: if (w[j]) < v[i]) res.push_back(w[j]); else res.push_back(v[i]);
Retourne res */
template <typename T>
std::vector<T> fusion(const std::vector<T> & v, const std::vector<T> & w);

/* Fusion de 2 vector supposément déjà triés, modification directe du premier
paramètre pour optimiser l'utilisation de la mémoire
avec plus ou moins: if (*iter_v > *iter_w) v.insert(iter_v, *iter_w); */
template <typename T>
void fusion_insertion(std::vector<T> & v, const std::vector<T> & w);

// Tri à bulle
template <typename T>
void tri_a_bulle (std::vector<T> & v);

#include "ex_tri_fusion.tpp"