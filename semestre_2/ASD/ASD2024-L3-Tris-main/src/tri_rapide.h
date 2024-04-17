#ifndef TRI_RAPIDE
#define TRI_RAPIDE

#include <iterator>
#include <concepts>
#include <random>
using namespace std;

extern const unsigned SEED;

template<typename T>
concept comparable_with_less = requires (const T& t, const T& u) {
   t < u;
};

template<typename T>
concept random_access_iterator_on_comparable_objects =
random_access_iterator<T> and comparable_with_less<T>;

template<random_access_iterator_on_comparable_objects Iterator>
Iterator partition(Iterator first, Iterator last)
{
    Iterator i = prev(first);
    Iterator j = last;
    while (1) {
        do {
            advance(i, 1);
        } while (*i < *last);

        do {
            advance(j, -1);
        } while (j > first && *last < *j);

        if (i >= j) {
            break;
        }
        iter_swap(i, j);
    }

        iter_swap(i, last);
        return i;
}

template<random_access_iterator_on_comparable_objects Iterator>
void tri_rapide(Iterator first, Iterator last)
{
    // Shortcut when the range is empty or has only one element
    if (distance(first, last) <= 0) {
        return;
    }

    // Seed a new random generator to provide consistent results
    default_random_engine seededRandom(SEED);
    while (first < last) {
        // Randomly choose the pivot, and move it to the end
        Iterator pivot = next(first, ((long long) seededRandom()) % distance(first, last));
        iter_swap(prev(last), pivot);
        // Partition expects the pivot to be given as the last iterator
        Iterator i = partition(first, prev(last));

        if (distance(first, i) < distance(i, last)) {
            tri_rapide(first, i);
            first = next(i);
            continue;
        }

        tri_rapide(next(i), last);
        last = i;
    }
}

#endif
