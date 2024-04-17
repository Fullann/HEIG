# Enoncé 

Ce laboratoire reprend largement les principes du labo 1 : comparer différents algorithmes de tri, mais cette fois 
avec des algorithmes de tri efficaces : 

* le tri rapide
* le tri par base

Dans un premier temps, mettez en oeuvre le tris en respectant les prototypes suivants: 

~~~cpp
#include <iterator>
#include <concepts>

template<typename T>
concept comparable_with_less = requires (const T& t, const T& u) {
   t < u;
};

template<typename T>
concept random_access_iterator_on_comparable_objects =
std::random_access_iterator<T> and comparable_with_less<T>;

template<random_access_iterator_on_comparable_objects Iterator>
Iterator partition(Iterator first, Iterator last);

template<random_access_iterator_on_comparable_objects Iterator>
void tri_rapide(Iterator first, Iterator last);
~~~ 

Notez que dans ces prototypes, le mot clé `typename` de la généricité est remplacé par le concept C++20
`random_access_iterator_on_comparable_objects` défini plus haut, qui garantit que `Iterator` est un 
itérateur qui permet un accès indexé et que le type des données sur lesquelles il itère peut être comparé 
avec l'opérateur `<`. 

La fonction `partition` retourne la position du pivot après partition. Elle suppose que le pivot a été placé en dernière position avant qu'on l'appelle. 

La fonction `tri_rapide` se charge de la récursion et de choisir le pivot de manière aléatoire. Elle
met en oeuvre l'approche "semi-récursive" vue au cours qui remplace l'appel récursif sur la partition la plus grande par une itération. 

Pour le tri par base, respectez l'interface suivant 

~~~cpp 
#include <iterator>
#include <concepts>

template<typename  T>
concept forward_iterator_on_unsigned_integrals = std::forward_iterator<T>
                                                 and std::unsigned_integral<typename T::value_type>;

template<std::forward_iterator Iterator, typename Fn>
void tri_comptage(Iterator first,  
                  Iterator last, 
                  Iterator output_first,  
                  Fn index_fn,  
                  size_t N);

template<forward_iterator_on_unsigned_integrals Iterator, size_t NBITS>
void tri_par_base(Iterator first,  
                  Iterator last);
~~~

La fonction `tri_comptage` effectue un tri comptage de la plage d'éléments `[first,last)` et stocke le résultat dans 
la plage de sortie commençant à `output_first`. La case de comptage d'un élément est déterminée par la fonction `index_fn` passée
en paramètre. Il y a `N` cases de comptage en tout. La fonction `tri_comptage` prend en paramètre des `std::forward_iterator`, 
ce qui veut dire que les opérateurs `[]`, `--`, `<`, `>`, `<=`, `>=`, `+`, et `-` ne sont pas nécessairement disponibles sur ces itérateurs. Vous
disposez par contre des opérateurs `++`, `==`, et `!=`, ainsi que des fonctions `next`, `prev`, `distance`, et `advance`. 

La fonction `tri_par_base` effectue le tri par base sur des entiers non signés stockés dans une plage définie par des `std::forward_iterator`,
ce qui est garanti par le concept `forward_iterator_on_unsigned_integrals`. Elle effectue le tri par base en divisant 
les `numeric_limits<T>::digits` bits de la représentation de ces nombres par groupes de  de `NBITS` bits et en appelant la fonction `tri_comptage` autant de fois que nécessaire. 

Le foncteur suivant vous est fourni pour extraire certains bits d'un entier non signé de type T. 

~~~cpp
#include <concepts>

template<std::unsigned_integral T>
class SomeBits {
    size_t shift;
    T mask;
public:
    SomeBits(size_t nombreDeBits, size_t part)
            : shift(part * nombreDeBits),
              mask((T(1u) << nombreDeBits) - T(1u)) {

    }
    T operator()(T const& t) {
        return T(mask & (t >> shift));
    }
};
~~~ 

## Tests à effectuer et rapport 

En plus des fonctions ci-dessus, nous vous demandons de fournir 

* un programme vérifiant que chacune des 4 fonctions ci-dessus fonctionnent correctement. 
* un programme effectuant des tests de temps d'exécution (mais pas de compte d'opérations) comme au labo 1. 

Ce 2ème programme doit vous permettre d'écrire un court rapport comparant 

* le tri rapide
* le tri par base en divisant les `unsigned int` par groupes de 1, 2, 4, 8 ou 16 bits. 

Pour ces comparaisons, triez des `vector<unsigned int>` remplis aléatoirement, dont la taille varie de 
10 à 1'000'000 éléments. 

Produisez 1 fichier .csv et 1 graphique résumant ces différentes mesures et expliquez les résultats observés. 
