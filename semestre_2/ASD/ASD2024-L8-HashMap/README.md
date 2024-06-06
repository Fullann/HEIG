# ASD2024-L8 HashMap

Le but de ce laboratoire est de mettre en oeuvre une table de hachage qui met en oeuvre une partie des fonctionalités de 
`std::unordered_map`. Son interface réduite est 

~~~cpp
template <typename Key, typename Value, typename HashKey = std::hash<Key>, typename EqualKey = std::equal_to<Key>>
class HashMap {
   HashKey hash_function;
   EqualKey is_equal;
   
public:
   HashMap();                     // constructeur

   Value& operator[](Key const&); // insertion et / ou accès à la valeur associée à une clé
   size_t erase(Key const&);      // suppression d'une paire clé/valeur
   void rehash(size_t);           // redimensionnement du tableau 

   [[nodiscard]] float load_factor() const noexcept;      // facteur de charge (nb d'éléments / taille du tableau)
   [[nodiscard]] float max_load_factor() const noexcept;  // lecture du facteur de charge maximum accepté par operator[] 
   void max_load_factor ( float z );                      // modification du facteur de charge maximum accepté par operator[] 

   friend std::ostream & operator<< <>(std::ostream &, const HashMap &);   // affichage
};
~~~

Ces méthodes doivent se comporter de manière similaires à leurs homogues de [std::unordered_map](https://cplusplus.com/reference/unordered_map/unordered_map/). 
Nous en ferons 2 versions, en appliquant les 2 techniques de gestion des collisions vues au cours. 

1. `HashMapChainage` met en oeuvre la gestion par chainage
2. `HashMapSondage` met en oeuvre la gestion par sondage linéaire 

Dans les 2 cas, vous disposez de la déclaration complète de la classe générique et d'un programme de test dont une sortie typique est disponible dans le répertoire [./outputs](./outputs).

## Attributs communs

Les 2 mises en oeuvre utilisent les attributs communs suivants

~~~cpp
size_t size;    // nombre d'éléments
float mlf;      // maximum load factor 
~~~

## Chainage

HashMapChainage stocke les données dans l'attribut

~~~cpp
std::vector<std::forward_list<std::pair<const Key,Value>>> data;
~~~

L'insertion d'une nouvelle paire se fait en tête de la liste simplement chainée désignée par son hash, à condition qu'elle
n'y soit pas déjà présente. Elle rehashe le tableau à une taille double si insérer conduirait à un facteur de charge 
supérieur au maximum autorisé. 

La suppression supprime le maillon spécifié par la clé, en ne fait rien si la clé est absente. Elle ne change pas la
taille de `data`. 

La fonction `rehash` qui modifie la taille de la table le fait en utilisant `splice_after` de sorte à ne pas construire 
et détruire des `pair<Key, Value>` inutilement.

## Sondage 

`HashMapSondage` dispose des attributs

~~~cpp 
std::vector<std::pair<Key,Value>> data;
std::vector<bool> is_used;
~~~

Les données sont stockées dans `data`, et le vecteur `is_used` permet de savoir quelles cases de `data` contiennent 
des données et lesquelles sont vides. 

L'insertion cherche la clé à partir de son hash, et si elle est absente, l'insère au premier emplacement vide à partir de
l'indice du hash. Elle rehashe en doublant la taille si nécessaire. 

La suppression cherche la clé à partir de son hash, et si elle la trouve met `is_used` à false pour son emplacement. 
Elle recalcule les hash et déplace si nécessaire les éléments qui suivent jusqu'à trouver un emplacement vide. 

## Affichage 

L'affichage d'une `HashMapChainage` affiche une liste chainée par ligne, avec le numéro de la liste, suivi de ses éléments
au format `(key,value)`, séparés par `->`, et fini par NULL.

Par exemple, la table de 6 éléments utilisant 4 liste chainées pourrait être 

~~~
1 : (Francis,5) -> (Alice,0) -> (Elena,4) -> NULL
2 : NULL
3 : (Bob,1) -> (Chiara,2) -> NULL
4 : (David,3) -> NULL
~~~

L'affichage d'une `HashMapSondage` affiche le facteur de charge, suivi du contenu du tableau `data` sur une ligne. Quand
la case n'est pas utilisée, on affiche `()`. Pour les cases utilisées, on affiche `(hash_function(key):key,value)`. 

Par exemple, une table de 8 éléments dans un tableau à 10 cases pourrait être 

~~~
LF:  0.8 (0:Chiara,2) (1:Gertrude,6) (1:David,3) () (4:Francis,5) (4:Elena,10) (6:Bob,1) (7:Hector,7) (6:Isabelle,8) ()
~~~
