# ASD-B-2024, Labo 3 : Tris, Groupe 4

### Feedback

#### Implémentation des fonctions (21 / 25)
* Tri rapide
	* Attention, aux lignes 38-39, vous commentez "Shortcut when the range is empty or has only one element" alors que `distance(first, last) <= 0` n'est pas vrai pour un élément.
	* Ligne 55, un bloc else avec les deux dernières lignes de la boucle while serait préférable à `continue`.
* Fonction partition
	* Par convention en C++, un itérateur last en censé pointer après le dernier élément. Votre fonction partition considère last comme pointant le dernier élément.	
* Tri par base
	* Votre implémentation ne supporte pas 0 élément en entrée.
	* Problème de généricité : `unsigned long long` à remplacer par `T` dans la déclaration de `fn` à la ligne 56.
	* Optimisation possible en appelant 2 fois `tri_comptage` à chaque itération, ce qui évite de copier les éléments à chaque itération :
		```
		while (max) {
			max >>= 2 * NBITS;
			tri_comptage(first, last, output.begin(), SomeBits<T>(NBITS, pos++), N);
			tri_comptage(output.begin(), output.end(), first, SomeBits<T>(NBITS, pos++), N);
		}
		```

#### Programmes (6 / 10)
* Test des fonctions
	* Votre programme de test des fonctions n'est pas configuré dans le fichier `CMakeLists.txt`.
	* Votre implémentation ne test pas différentes tailles d'entrées.
	* La fonction `partition` n'est pas testée.
* Mesure du temps
	* Votre implémentation devrait moyenner les mesures de temps sur plusieurs essais.

#### Rapport (6 / 10)
* Comparaison des tris
	* Attention, le tri rapide a une complexité linéarithmique alors que le tri par base a une complexité linéaire.
	* Votre analyse devrait justifier vos observations par les complexités théoriques des algorithmes utilisés.
* CSV et graphique
	* Les axis de votre graphique doivent comporter un titre.
	* Le choix des couleurs des graphes n'est pas appropriés, les couleurs pour le tri comptage et le tri rapide sont indistinguables.
	* La taille du trait est trop grande

#### Rendu et propreté (1.5 / 5)
* Tag "Rendu" absent
* Noms des membres / numéro du groupe manquant dans le fichier `README.md`
* Attention, mettre des traits d'unions dans les noms de fichiers (main_check-tris.cpp) n'est généralement pas une bonne pratique.
* Votre implémentation des programmes de test des fonctions et de mesure du temps seraient plus lisibles en itérant sur les différents tris plutôt qu'en duplicant toutes les opérations pour chacun. 

### Note
* 34.5 / 50 points
* Note : 4.45 / 6