/**
 * Laboratoire sur l'exercice 9.5
 * Author : Nathan Füllemann
 * Date : 27.11.2023
 * Updated on :
 *
 * Name : Algorithme de tri
 * Desc : Ce fichier contient les fonctions de tri fusion, tri à bulle et fusion-insertion
 */
/*

* Fonction fusion
Meilleur Cas :

La meilleure situation se produit lorsque les vecteurs d'entrée v et w sont déjà triés.
Dans ce cas, la fusion se fait en parcourant une fois chaque vecteur et en comparant les éléments.
La complexité temporelle est de l'ordre de O(n), où n est la taille du vecteur.
Pire Cas :

Le pire cas survient lorsque les vecteurs d'entrée v et w sont dans un ordre inverse (décroissant).
Dans ce cas, la complexité temporelle est également de l'ordre de O(n), car chaque élément des deux vecteurs doit être comparé et ajouté au vecteur résultant.

* Fonction fusion_insertion
Meilleur Cas :

Le meilleur cas se produit lorsque le vecteur d'entrée v est déjà trié, car il n'y aura pas besoin d'insertions au milieu du vecteur.
La complexité temporelle est de l'ordre de O(n), où n est la taille du vecteur.
Pire Cas :

Le pire cas se produit lorsque le vecteur d'entrée v est dans un ordre inverse et que chaque élément du vecteur w doit être inséré au début du vecteur v.
Dans ce cas, la complexité temporelle est de l'ordre de O(n^2), car chaque élément de w nécessite une insertion, et le décalage des éléments suivants peut prendre jusqu'à O(n) pour chaque insertion.

*/
using namespace std;

/// @brief Tri fusion
/// @tparam T  Le type des éléments du vecteur
/// @param v  Le vecteur à trier
/// @param w  Un vecteur temporaire
/// @return  Le vecteur trié
template <typename T>
vector<T> fusion(const vector<T> &v, const vector<T> &w)
{
    vector<T> res;
    size_t i = 0, j = 0;
    // Parcourir les deux vecteurs
    while (i < v.size() && j < w.size())
    {
        // Si l'élément de w est plus petit, on l'ajoute à res
        if (w[j] < v[i])
        {
            res.push_back(w[j]);
            ++j;
        }
        else
        {
            res.push_back(v[i]);
            ++i;
        }
    }

    // Ajouter les éléments restants de v, s'il y en a
    while (i < v.size())
    {
        res.push_back(v[i]);
        ++i;
    }

    // Ajouter les éléments restants de w, s'il y en a
    while (j < w.size())
    {
        res.push_back(w[j]);
        ++j;
    }
    return res;
}

/// @brief Tri fusion
/// @tparam T  Le type des éléments du vecteur
/// @param v  Le vecteur à trier
/// @param w  Un vecteur temporaire
/// @return  Le vecteur trié
template <typename T>
void fusion_insertion(vector<T> &v, const vector<T> &w)
{
    auto iter_v = v.begin();
    auto iter_w = w.begin();
    // Fusionner les vecteurs v et w avec insertion
    while (iter_v != v.end() && iter_w != w.end())
    {
        // Si l'élément de w est plus petit, on l'insère dans v
        if (*iter_w < *iter_v)
        {
            v.insert(iter_v, *iter_w);
            ++iter_w;
        }
        else
        {
            ++iter_v;
        }
    }

    // Ajouter les éléments restants de w, s'il y en a
    while (iter_w != w.end())
    {
        v.push_back(*iter_w);
        ++iter_w;
    }
}

/// @brief Tri à bulle
/// @tparam T  Le type des éléments du vecteur
/// @param v  Le vecteur à trier
/// @return  Le vecteur trié
template <typename T>
void tri_a_bulle(vector<T> &v)
{
    bool isSwap;
    auto last = v.end();

    do
    {
        isSwap = false;
        auto it = v.begin();
        auto next_it = next(it);
        // Parcourir le vecteur tant qu'il y a des permutations
        while (next_it != last)
        {
            // Si l'élément suivant est plus petit, on le swap
            if (*next_it < *it)
            {
                iter_swap(it, next_it);
                isSwap = true;
            }
            ++it;
            ++next_it;
        }

        --last;

        // Si aucune permutation n'est effectuée, le tableau est trié
        if (!isSwap)
            break;

    } while (last != v.begin());
}
