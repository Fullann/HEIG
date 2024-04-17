# PRG2 L4 - Allocation dynamique et tableaux multidimensionnels

Le but de ce laboratoire est d'entraîner l'allocation dynamique et des tableaux multidimensionnels.

## Amélioration du calculateur de moyenne

Pour cet exercice, il vous est demandé d'ajouter le support de plusieurs branches au calculateur de moyenne réalisé dans le laboratoire précédent. De plus, le nombre total de branches ainsi que le nombre de notes maximal (par branche) doit pouvoir être choisi au lancement du programme, en argument de ligne de commande. Lors du lancement, le nom des branches sera demandé à l'utilisateur.

Le programme sera lancé de la façon suivante :

```
./better_grades <N_SUBJECT> <MAX_GRADES>
```
`<N_SUBJECT>` étant le nombre de branches et `MAX_GRADES` le nombre maximal de note pas branche.

Le nouveau menu principal de l'application est le suivant :

```
1: Add a grade
2: Delete a grade
3: Modify a grade
4: Swap a grade
5: Compute average
6: Modify subject name
7: Add a subject
8: Quit

prg2      : 4.8, 5.0
asd       : No grades
```

Les options 1 à 4 restent les mêmes que pour le laboratoire précédent, sauf que le nom de la branche à modifier est demandé avant le reste.

Pour l'option 5, les moyennes de chaque branche devront être affichées.

L'option 6 permet de modifier le nom d'une branche, le nom actuel de la branche sera alors demandé suivi du nouveau nom à utiliser.

L'option 7 permet d'ajouter une nouvelle branche, seul le nom de celle-ci est demandé.

Des exemples d'utilisation de ces différentes options sont présentés plus bas.

## Contraintes

Les contraintes suivantes sont à respecter :

  - Tous les tableaux doivent être alloués dynamiquement (excepté pour les éventuels buffers pour la lecture des entrées utilisateurs) .
  - Le tableau multidimensionnel contenant les notes doit être déclaré de façon unidimensionnelle pour contenir le nombre maximal de note possible avec toutes les branches. A vous d'en interpréter le contenu de la bonne façon.
  - Le tableau des noms est un tableau de pointeur, pointant chacun sur un tableau de caractère contenant le nom. La taille du tableau de caractère doit correspondre à la taille minimum nécessaire pour contenir le nom.
  - Il est demandé de supporter des noms allant jusqu'à 10 caractères et ne contenant que des lettres (non accentuée) majuscules et minuscules et des chiffres.
  - L'affichage des notes doit avoir un alignement correct (voir les exmples).
  - Il ne doit pas y avoir de fuite de mémoire.
  - Toutes les options du menu (à part pour l'option n°8) doivent être gérées dans des fonctions séparées.
  - N'oubliez pas de libérer toute la mémoire allouée à la fin de l'exécution du programme.

## Gestion des erreurs

  - Si le programme n'est pas lancé avec les paramètres nécessaires, le message `Usage: ./better_grades <N_SUBJECT> <MAX_GRADES>` doit s'afficher et le programme se termine avec une erreur.
  - Pour toutes allocation effectuée, il est impératif de vérifier les valeurs de retour afin de vérifier le bon fonctionnement de l'allocation, dans le cas d'une erreur, une erreur sera affichée par le main.
  - Pour chaque fonctionnalité, les erreurs sont à gérer de la même façon que pour l'exercice 3 du laboratoire précédent: la fonction gère en interne une potentielle erreur de saisie de l'utilisateur et retourne un code d'erreur si jamais elle ne peut pas accomplir sa tâche (par exemple: tableau plein lors de l'ajout d'une note). Pour plus d'informations quant aux valeurs de retour des fonctions, vous pouvez ouvrir un terminal et saisir la commande `man <fonction désirée>` pour obtenir la documentation de la fonction (par exemple: `man malloc`).
  - Les erreurs de fonctions affichent un message d'erreur comme dans le laboratoire précédent mais n'arrêtent pas l'exécution du programme. Les erreurs d'allocation affichent un message d'erreur et le programme s'arrête ensuite (après avoir libéré la mémoire ayant pu être allouée avec succès avant cette erreur).

## Exemple d'utilisation

Voici des exemples d'utilisation du programme (le menu est remplacé par `...` pour réduire l'affichage).

### Lancement du programme

```
reds@reds$ ./better_grades
Usage: ./better_grades <N_SUBJECT> <MAX_GRADES>
reds@reds$ ./better_grades 2
Usage: ./better_grades <N_SUBJECT> <MAX_GRADES>
reds@reds$ ./better_grades 2 8 1
Usage: ./better_grades <N_SUBJECT> <MAX_GRADES>
reds@reds$ ./better_grades 2 8
Enter the name for the subject 1: prg2
Enter the name for the subject 2: asd

1: Add a grade
2: Delete a grade
3: Modify a grade
4: Swap a grade
5: Compute average
6: Modify subject name
7: Add a subject
8: Quit

prg2      : No grades
asd       : No grades

Enter your choice:
```

### Ajout de note

```
...

prg2      : 4.5, 5.6
asd       : 5.7, 3.8

Enter your choice: 1
Enter the subject name: asd
Enter the grade value: 6

...

prg2      : 4.5, 5.6
asd       : 5.7, 3.8, 6.0

Enter your choice: 1
Enter the subject name: pgr2
Subject not found.
Enter the subject name: prg2
Enter the grade value: 6.1
Grade is not valid.
Enter the grade value: 4.5

...

prg2      : 4.5, 5.6, 4.5
asd       : 5.7, 3.8, 6.0

Enter your choice:
```

### Suppression de note

```
...

prg2      : 4.5, 5.6, 4.5
asd       : 5.7, 3.8, 6.0

Enter your choice: 2
Enter the subject name: prg2
Enter the grade position: 4
Position is not valid.
Enter the grade position: 2

...

prg2      : 4.5, 4.5
asd       : 5.7, 3.8, 6.0

Enter your choice:
```

### Modification de note

```
...

prg2      : 4.5, 4.5
asd       : 5.7, 3.8, 6.0

Enter your choice: 3
Enter the subject name: asd
Enter the grade position: 2
Enter the grade value: 4

...

prg2      : 4.5, 4.5
asd       : 5.7, 4.0, 6.0

Enter your choice:
```

### Echange de deux notes

```
...

prg2      : No grades
asd       : 5.7, 4.0, 6.0

Enter your choice: 4
Enter the subject name: asd
Enter the two grades positions to swap: 1 3

...

prg2      : No grades
asd       : 6.0, 4.0, 5.7

Enter your choice: 4
Enter the subject name: prg2
Array is empty

...

prg2      : No grades
asd       : 6.0, 4.0, 5.7

Enter your choice:
```

### Calcul d'une moyenne

```
...

prg2      : 4.5
asd       : 6.0, 4.0, 5.7
mat2      : No grades

Enter your choice: 5
prg2      : 4.5
asd       : 5.2
mat2      : No grades
```

### Modification du nom d'une branche

```
...

pgr2      : 4.5
asd       : 6.0, 4.0, 5.7
mat2      : No grades

Enter your choice: 6
Enter the subject name: pgr2
Enter the name for the subject: prg2

...

prg2      : 4.5
asd       : 6.0, 4.0, 5.7
mat2      : No grades

Enter your choice:
```

### Ajout d'une branche

```
...

prg2      : 4.5
asd       : 6.0, 4.0, 5.7

Enter your choice: 7
Enter the name for the subject: mat2

...

prg2      : 4.5
asd       : 6.0, 4.0, 5.7
mat2      : No grades

Enter your choice:
```
