# Mini-Rapport sur la Résolution du Taquin

## Introduction
Ce mini-rapport présente une analyse de la résolution d'un taquin de taille n x n, en se concentrant sur trois aspects principaux : le nombre de sommets du graphe, la complexité temporelle de l'algorithme, et le coût en mémoire de la solution. Une étude de cas est également fournie pour un taquin de taille 4x4.

## Nombre de Sommets du Graphe
Le nombre de sommets dans le graphe d'un taquin de taille n x n est donné par le nombre total de configurations possibles des pièces du taquin. Cela est calculé par la formule des permutations des n^2 - 1 pièces (la case vide est fixe) :

\[ (n^2 - 1)! \]

Pour un taquin de taille 4x4 (n=4) :

\[ (4^2 - 1)! = 15! = 1 307 674 368 000 \]

## Complexité Temporelle de l'Algorithme
La complexité temporelle d'un algorithme de résolution de taquin dépend de l'algorithme utilisé. Supposons l'utilisation d'un algorithme de type A* (A-star), qui est couramment utilisé pour ce type de problème. La complexité temporelle dans le pire des cas est généralement approximée par :

\[ O(b^d) \]

où b est le facteur de branchement (nombre moyen de mouvements possibles à chaque étape) et d est la profondeur de la solution optimale.

Pour un taquin 4x4, le facteur de branchement moyen b est environ 2.7 (dépend des mouvements possibles) et la profondeur moyenne d est approximativement 80. Donc, la complexité temporelle est de l'ordre de :

\[ O(2.7^{80}) \]

## Coût en Mémoire de la Solution
Le coût en mémoire pour la résolution d'un taquin dépend également de l'algorithme utilisé. Pour A*, la mémoire nécessaire pour stocker les nœuds ouverts et fermés est souvent le facteur limitant. En général, la mémoire requise est approximée par :

\[ O(b^d) \]

Pour un taquin 4x4, en utilisant les mêmes valeurs que précédemment (b ≈ 2.7 et d ≈ 80), le coût en mémoire est de l'ordre de :

\[ O(2.7^{80}) \]

## Résolution d'un Taquin 4x4

### Nombre de Sommets
\[ 15! = 1 307 674 368 000 \]

### Complexité Temporelle
\[ O(2.7^{80}) \]

### Coût en Mémoire
\[ O(2.7^{80}) \]

## Conclusion
La résolution d'un taquin, en particulier pour une taille de 4x4, présente des défis significatifs en termes de complexité temporelle et de coût en mémoire en raison du nombre astronomique de configurations possibles. L'utilisation d'algorithmes efficaces et d'optimisations est cruciale pour rendre ce problème tractable en pratique.

