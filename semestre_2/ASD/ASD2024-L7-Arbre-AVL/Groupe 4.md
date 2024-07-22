# ASD-B-2024, Labo 7 : Arbre AVL

## Groupe 4
* url: https://github.com/Fullann/ASD2024-L7-Arbre-AVL
* Étudiants :
	* nathan.fullemann@heig-vd.ch
	* maxime.regenass@heig-vd.ch

### Feedback

#### Implémentation AVL (32 / 35)
* Ajout/suppression d’éléments (insert, erase, erase_min et erase_max)
	* Problème d'implémentation : dans la fonction `avl::delete_min`, qui d'après votre implémentation doit extraire le nœud minimum, la hauteur du nœud extrait doit être recalculée et son équilibre rétabli après l'appel récursif en ligne 94 (mais avant de retourner).
	* Problème d'implémentation : dans la fonction `avl::deleteElement`, l'équilibre doit aussi être rétabli après avoir détruit le nœud.
* Opérateur de flux
	* L'opérateur d'extraction de flux (`>>`) ne supprime pas les nœuds préexistants

#### Tests unitaires avec catch2 (4.5 / 5)
* Fonction `avlTree::insert` pas testée dans un cas qui nécessite une rotation

#### Factorisation, rendu et propreté (7 / 10)
* Autres
	* Définir un nouveau constructeur d'une structure dont l'interface vous est donnée (`avlTree`) est une mauvaise pratique. En plus, cela ne vous est utile que pour vos tests (de manière générale l'implémentation de tests ne doit pas influencé les choix d'implémentation du code ou des structures de données à tester).
* Commentaires et propreté
	* Modification du fichier `avlNode.h` contrairement à ce qui était demandé dans l'énoncé.
	* Modification du fichier `avlTree.h` contrairement à ce qui était demandé dans l'énoncé

### Note
* 43.5 / 50 points
* Note : 5.4 / 6