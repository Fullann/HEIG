# PRG2 L3 - Pointeurs et tableaux

Le but de ce laboratoire est d'entraîner l'utilisation de tableaux et de pointeurs au travers de 3 exercices.
## Nom du groupe
- Maxime Regenass
- Nathan Füllemann
## Exercice 1 : Bataille navale

Dans cet exercice, vous allez réaliser une version très simplifiée d'une bataille navale.

Pour y parvenir, vous devrez d'abord créer un tableau avec une taille fixe définie par un `define`.

Vous devrez ensuite définir 3 valeurs de votre choix pour représenter les cases vides, les cases contenant un bateau ennemi et les cases déjà attaquées.

Pour générer de l'aléatoire, vous devrez utiliser la fonction `rand`. Il est nécessaire d'appeler, au début de votre main, la fonction `srand(seed)` qui permet d'initialiser la randomisation. Le paramètre `seed` permet d'avoir une randomisation reproductible. Par exemple, avec une seed de 3, la randomisation serait la même à chaque exécution du programme. Une solution pour obtenir une solution proche d'une génération aléatoire réelle est de donner en seed un appel à  la fonction `time(NULL)` qui permettra de générer une seed basée sur la date et l'heure. L'appel sera donc de la forme `srand(time(NULL))`.

Une fois la randomisation initialisée, un appel de la fonction `rand()` renverra un entier aléatoire. Si le but est, par exemple, d'obtenir un entier aléatoire entre 0 et 3 (3 non compris), il faut effectuer un modulo sur le résultat de la fonction comme suit: `my_val = rand() % 3`.

Une fois ceci fait, un message devra être affiché pour demander à l'utilisateur de sélectionner une case à attaquer et informer ce dernier du nombre de vies et de bateaux restants. 

L'utilisateur devra ensuite sélectionner le numéro de la case à attaquer (si 10 cases, de 0 à 9). La saisie doit être vérifiée pour éviter des erreurs. Vous pouvez vous limiter à la gestion de valeurs numériques. Nous assumons qu'aucune autre valeur ne sera saisie.

En cas de saisie invalide, l'utilisateur est invité à saisir une nouvelle valeur. Une fois ceci fait, les trois cas de figure suivants doivent être gérés:

* Sélection d'une une case vide: un message est affiché et le joueur perd une vie. Le nombre de vies initial est de 5.
* Sélection d'une case déjà attaquée: un message est affiché et le joueur ne perd pas de vie.
* Sélection d'une case contenant un bateau ennemi: un message est affiché et le joueur ne perd pas de vie.

La partie continue jusqu'à ce que le joueur aie perdu toutes ses vies ou touché tous les bateaux.

Voici un exemple d'utilisation du programme :

```
5 lifes remaining, 3 ships remaining
Please select a position to attack between 0 and 9!
1
MISS
4 lifes remaining, 3 ships remaining
Please select a position to attack between 0 and 9!
2
HIT
4 lifes remaining, 2 ships remaining
Please select a position to attack between 0 and 9!
3
MISS
3 lifes remaining, 2 ships remaining
Please select a position to attack between 0 and 9!
3
Already attacked this position
3 lifes remaining, 2 ships remaining
Please select a position to attack between 0 and 9!
4
HIT
3 lifes remaining, 1 ships remaining
Please select a position to attack between 0 and 9!
5
MISS
2 lifes remaining, 1 ships remaining
Please select a position to attack between 0 and 9!
6
MISS
1 lifes remaining, 1 ships remaining
Please select a position to attack between 0 and 9!
7
HIT
YOU WIN
```

## Exercice 2 : Manipulation de pointeurs

### Partie 1 : Exploration

Dans cette première partie d'exercice, vous allez réaliser un code très simple permettant d'observer de manière exploiratoire le fonctionnement d'un pointeur. Vous allez devoir suivre les étapes suivantes:

* Création d'une variable de type `int` et assignation d'une valeur de votre choix
* Création d'un pointeur sur `int` et assignation de l'adresse de la variable
* Affichage de l'addresse pointée par le pointeur
* Affichage de la valeur de la variable en déréférençant le pointeur
* Modification de la variable de base
* Affichage de la valeur de la variable en déréférençant le pointeur
* Modification de la valeur de la variable à travers le pointeur
* Affichage de la valeur de la variable de base

### Partie 2 : Itération

Dans cette seconde partie d'exercice, vous allez devoir réaliser un petit programme dans lequel vous allez créer un tableau de 10 int initialisés à 0, afficher son contenu, puis itérer sur le tableau afin que son contenu soit le suivant: `0 1 2 3 4 5 6 7 8 9`. Vous finirez ensuite par un autre affichage du contenu. Il y'a cependant une contrainte: il vous est interdit d'accéder au tableau de la façon `array[idx]` autant pour l'affichage que pour la modification des valeurs. Vous devez impérativement vous baser sur le fait qu'un tableau est en réalité un pointeur sur une zone mémoire.

## Exercice 3 : Calculateur de moyenne

Dans cet exercice, vous allez réaliser un calculateur de moyenne simplifié pour ne gérer qu'une seule matière. Le nombre de notes maximal sera fixé à la compilation.

Plusieurs fonctionnalités doivent être mises en place :

  1. Ajout d'une note.
  2. Suppression d'une note à une position donnée.
  3. Modification de la valeur d'une note à une position donnée.
  4. Intervertir deux notes à des positions données.
  5. Calcul de la moyenne des notes.

Le menu principal devrait donc ressembler à cela :

```
1: Add a grade
2: Delete a grade
3: Modify a grade
4: Swap two grades
5: Compute average
6: Quit

Grades: 4.6, 5.4, 3.0
```

L'option 6, permet de quitter le programme. Aucune sauvegarde des notes ne doit être faite, celles-ci sont perdues à la fin de l'exécution du programme. Les notes saisies sont affichées (p. ex. `Grades: 4.6, 5.4, 3.0`) après le menu. Si aucune note n'a été saisie, le message `There are no grade yet.` est affiché à la place.

L'utilisateur entrera ensuite un chiffre entre 1 et 6 pour sélectionner l'une des options.

Chaque fonctionnalité doit être gérée par une fonction. La gestion des erreurs (affichage d'un message d'erreur, par exemple) devra se faire depuis la fonction main et non depuis les différentes fonctions. Ces dernières devront donc retourner des codes d'erreur en conséquence.

Pour cet exercice, vous pouvez assumer que les valeurs entrées par l'utilisateur ne seront que des nombres respectant le format demandé (à virgule pour les notes et sans virgule pour le choix et les indexes). Pas besoin de vérifier si des lettres ou autre sont entrées, vous pouvez vous limiter à la gestion des bornes des valeurs saisies.

Voici la description des différentes fonctionnalités :

### Ajouter une note

L'utilisateur sera appelé à saisir une nouvelle note. La saisie doit être vérifiée, si non valide, une nouvelle saisie sera demandée sans retourner d'erreur (sans quitter la fonction).

Dans le cas où le tableau de notes est déjà plein, la fonction doit retourner une erreur sans demander la saisie d'une nouvelle note.

### Supprimer une note

L'utilisateur sera appelé à saisir l'indexe de la note à supprimer (numéroté à partir de 1). La saisie doit être vérifiée, si non valide, une nouvelle saisie sera demandée sans retourner d'erreur (sans quitter la fonction).

Lors de la suppression d'une note, toutes celles stockés à la suite de cette dernière seront décalées afin de ne pas laisser d'espace vide dans le tableau.

Dans le cas où le tableau de notes est déjà vide, la fonction doit retourner une erreur sans demander la saisie de l'indexe.

### Modifier une note

L'utilisateur devra saisir dans un premier temps l'indexe de la note à modifier (toujours numéroté à partir de 1), puis la nouvelle valeur pour la note. A nouveau, les valeurs saisies devront être vérifiées.

Si le tableau de notes est vide, la fonction doit retourner une erreur sans demander de saisi utilisateur.

### Intervertir deux notes

L'utilisateur devra saisir l'indexe des deux notes à intervertir dans le tableau. Les deux valeurs seront saisies à la suite, séparées par un espace. Les valeurs saisies devront être vérifiées.

Si le tableau ne comporte pas au moins deux notes, la fonction doit retourner une erreur sans demander de saisi utilisateur.

Pour intervertir les deux notes, vous devrez créer une nouvelle fonction `swap` prenant en paramètres deux pointeurs sur les deux notes.

### Calcul de la moyenne

Cette fonction va simplement afficher la moyenne des différentes notes arrondie au dixième.

Si le tableau est vide, une erreur doit être retournée.

### Contraintes

Les contraintes suivantes doivent être respectées :

  - Les notes doivent être des nombres à virgule flottante compris entre 1.0 et 6.0.
  - Les notes et la moyenne sont affichées avec un chiffre après la virgule.
  - Lorsqu'une erreur est retournée par une fonction, un message exhaustif doit être affiché, par la fonction principale (gérant le choix de la fonctionnalité et non par les fonctions des fonctionnalités).
  - Le define `ARRAY_SIZE` doit être utilisé pour la taille maximale du tableau.
  - Pas de variable globale, passage du tableau par les paramètres des fonctions.

### Exemple d'utilisation

Voici un exemple d'utilisation du programme (le menu a été remplacé par `...` pour réduire l'affichage) :

```
1: Add a grade
2: Delete a grade
3: Modify a grade
4: Swap a grade
5: Compute average
6: Quit

There are no grade yet.

Enter your choice: 1
Enter the grade value: 4.8

1: Add a grade
2: Delete a grade
3: Modify a grade
4: Swap a grade
5: Compute average
6: Quit

Grades : 4.8

Enter your choice: 1
Enter the grade value: 7
Grade is not valid.
Enter the grade value: 6

...

Grades : 4.8, 6.0

Enter your choice: 1
Enter the grade value: 5.3

...

Grades : 4.8, 6.0, 5.3

Enter your choice: 5
The average is 5.4

...

Grades : 4.8, 6.0, 5.3

Enter your choice: 3
Enter the grade position: 4
Position is not valid.
Enter the grade position: 3
Enter the grade value: 5.4

...

Grades : 4.8, 6.0, 5.4

Enter your choice: 4
Enter the two grades positions to swap: 1 3

...

Grades : 5.4, 6.0, 4.8

Enter your choice: 5
The average is 5.4

...

Grades : 5.4, 6.0, 4.8

Enter your choice: 2
Enter the grade position: 2

...

Grades : 5.4, 4.8

Enter your choice: 5
The average is 5.1

...

Grades : 5.4, 4.8

Enter your choice: 6
```
