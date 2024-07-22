# PRG2 L8 - B-Tree et CUnit

Le but de ce laboratoire est de mettre à profit les notions principales abordées tout au long du cours PRG2 afin de mettre en oeuvre un B-Tree. 
Des tests unitaires seront également mis en place à travers CUnit. 

## B-Tree

Le B-Tree fonctionne sur le même principe qu'un arbre binaire, mais peut stocker plusieurs clés dans chacun de ses noeuds. 
Vous devrez mettre en place un define permettant de définir un nombre maximal `M` de clés par noeuds. Chaque noeud pourra alors stocker entre `M/2` (arrondi à l'entier inférieur) et `M` clés. 

Concernant l'algorithme pour mettre en place le B-Tree, l'explication étant très longue à donner par écrit, vous trouverez toutes les informations dont vous aurez besoin sur la vidéo suivante: https://www.youtube.com/watch?v=K1a2Bk8NrYQ

Il vous est demandé de mettre les fonctions suivantes:

* Création d'un arbre et / ou d'un noeud.
* Recherche d'une clé dans l'arbre.
* Insertion d'une clé dans l'arbre. 
* Libération d'un noeud
* Libération (récursive) des enfants d'un noeud 

Il ne vous est pas demandé de mettre en place la suppression d'une valeur, car cela ajoute énormément de complexité au travail à effectuer. 

L'arbre n'est accessible que par son noeud racine, vous n'aurez donc que des structures `node` et vous vous baserez sur le noeud racine.

La structure `node` regroupera les informations suivantes:

* un entier pour le nombre de clés actuellement stockées dans le noeud
* un tableau (statique) d'entiers pour les clés
* un tableau de pointeurs sur noeuds pour les enfants du noeud courant
* un booléen pour savoir si le noeud est une feuille ou non

Vous devez déclarer votre structure et vos différentes fonctions dans le fichier `btree.h` et l'implémentation de vos fonctions dans `btree.c`. Libre à vous d'ajouter dans `btree.c` une fonction main pour des tests et / ou du debug rapide, mais cette fonction devra ensuite être supprimée pour que la partie des tests unitaires puisse fonctionner. 

Note: Attention, pensez bien au fait que la gestion peut différer légèrement si le nombre maximal de clés par noeud est paire ou impaire! 

## Tests unitaires

Le but de cet exercice n'est pas de vous faire passer des heures à réfléchir à quoi tester sur votre B-Tree, mais de vous faire pratiquer l'utilisation de CUnit. 

Vous allez donc devoir vous baser sur ce que vous avez pu voir en cours et dans vos exercices pour mettre en place un programme permettant d'effectuer des tests unitaires sur le B-Tree et d'utiliser l'interface de CUnit pour en visualiser le résultat. 

Pour installer CUnit, utilisez la commande suivante: 
```
sudo apt install libcunit1 libcunit1-dev libcunit1-doc libcunit1-ncurses libcunit1-ncurses-dev
```

En cas d'erreur à l'installation, réinstallez les packages, mais un seul à la fois.

Vos tests unitaires seront mis en place dans le fichier `unit_test.c`. 

Les cas à tester sont les suivants:

### Insertion simple

* création d'un arbre
* vérification de la validité du pointeur sur le noeud racine
* insertion d'une valeur dans l'arbre
* vérification du nombre de clé dans le noeud, de la valeur stockée dans le noeud et de l'état de la variable booléenne (feuille ou non). 

### Recherche simple

* création d'un arbre
* validation du pointeur
* recherche d'une valeur entière
* insertion dans l'arbre de cette valeur
* nouvelle recherche de la valeur entière

### Insertion avec split

* création d'un arbre
* ajout d'assez de valeurs entières pour entrainer un split de noeud
* vérification des différentes informations stockées dans les noeuds

### Insertion avec deux splits 
 
* création d'un arbre
* ajout d'assez de valeurs entières pour entrainer deux splits de noeuds
* vérification des différents informations stockées dans les noeuds

### Insertions avec split en profondeur

* création d'un arbre
* ajout d'assez de valeurs entières pour entrainer la création de trois étages de noeuds 
* vérification des différents informations stockées dans les noeuds. 










