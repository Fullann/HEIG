#ifndef TRI_PAR_BASE
#define TRI_PAR_BASE

#include <iterator>
#include <concepts>
#include <vector>
#include <algorithm>
#include <iostream>
#include "some_bits.h"

template<typename  T>
concept forward_iterator_on_unsigned_integrals = std::forward_iterator<T>
                                                 and std::unsigned_integral<typename T::value_type>;

template<std::forward_iterator Iterator, typename Fn>
void tri_comptage(Iterator first, Iterator last, Iterator output_first, Fn index_fn, size_t N){
    //vecteur de compteurs
    std::vector<size_t> count(N, 0);

    //parcours le tableau et incrémente les bons index
    for (auto it = first; it != last; ++it) {
        size_t index = index_fn(*it);
        ++count[index];
    }

    //Décalage pour donner l'emplacement dans le tableau
    for (size_t i = 1; i < N; ++i) {
        count[i] += count[i - 1];
    }

    //Tri le tableau par rapport au index
    for (auto it = last - 1; it >= first; --it) {
        size_t index = index_fn(*it);
        //Cast dans le type du vecteur pour faire la soustraction. Sans le cast, il y a un warning
        *(output_first + static_cast<typename std::iterator_traits<Iterator>::difference_type>(count[index] - 1)) = *it;
        --count[index];
    }
}

template<forward_iterator_on_unsigned_integrals Iterator, size_t NBITS>
void tri_par_base(Iterator first, Iterator last)
{
    using T = typename Iterator::value_type;

    //On obtient la taille et on crée un tableau temporaire
    auto distance = (size_t)std::distance(first, last);
    std::vector<T> output(distance);

    //On récupère l'élément le plus grand
    T max = *std::max_element(first, last);
    size_t pos = 0;
    const T size = max + 1;

    //On parcours la valeur max en décalant le bon nombre de bit
    while (max){
        auto fn = SomeBits<unsigned long long>(NBITS, pos++);
        max >>= NBITS;

        //Appel de la méthode de tri
        tri_comptage(first, last, output.begin(), fn, size);
        std::swap_ranges(first, last, output.begin());
    }
}


#endif
