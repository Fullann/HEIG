# PRG2 L5 - Manipulations de bits et chaînes de caractères

Le but de ce laboratoire est d'entraîner les manipulations de bits ainsi que l'utilisation des chaînes de caractères.

## Exercice 1 : Bataille navale 2.0

Dans cet exercice, vous allez reprendre la bataille navale réalisée au lab03 avec une philiosphie très diffèrente: toutes les données du jeu seront stockées dans une seule et unique variable de 32 bits.

Les données seront donc encodées de la façon suivante dans les différents bits de la variable:

* bits[31:28] : Nombre de bateaux restants dans le jeu (valeur entière encodée sur 4 bits).
* bits[27:24] : Nombre de vies restantes (valeur entière encodée sur 4 bits).
* bits[23:12] : Positions déjà attaquées ou non par le joueur (une position par bit).
* bits[11:0] : Positions des bateaux (une position par bit).

ATTENTION: vous n'avez à aucun moment le droit d'utiliser des variables supplémentaires pour stocker les différentes valeurs et contourner la contrainte d'une unique variable 32bits. La seule exception à cette règle est que vous êtes autorisés à utiliser une variable tmp pour une manipulation simple comme par exemple:

```
tmp = nombre_de_vies
tmp++;
nombre_de_vies = tmp;
```

Le fonctionnement de l'application doit être exactement le même que pour le lab03, le même menu sera affiché et l'utilisateur devra saisir une position à attaquer.

Le nombre de vies inital sera de 6 et le nombre de bateaux sera également de 6 et leur emplacement sera défini aléatoirement.

Concernant les entrées utilisateur, vous pouvez vous limiter à la vérification des bornes numériques.

Pour rappel, voici les règles à suivre lors de la saisie d'une valeur par l'utilisateur:

* Sélection d'une une case vide: un message est affiché et le joueur perd une vie. Le nombre de vies initial est de 5.
* Sélection d'une case déjà attaquée: un message est affiché et le joueur ne perd pas de vie.
* Sélection d'une case contenant un bateau ennemi: un message est affiché et le joueur ne perd pas de vie.

La partie continue jusqu'à ce que le joueur aie perdu toutes ses vies ou touché tous les bateaux.

Voici également un exemple d'utilisation du programme :

```
6 lifes remaining, 6 ships remaining
Please select a position to attack between 0 and 11!
0
MISS
5 lifes remaining, 6 ships remaining
Please select a position to attack between 0 and 11!
1
HIT
5 lifes remaining, 5 ships remaining

(...)

Please select a position to attack between 0 and 11!
3
MISS
3 lifes remaining, 2 ships remaining
Please select a position to attack between 0 and 11!
3
Already attacked this position
3 lifes remaining, 2 ships remaining
Please select a position to attack between 0 and 11!
4
HIT
3 lifes remaining, 1 ships remaining
Please select a position to attack between 0 and 11!
5
MISS
2 lifes remaining, 1 ships remaining
Please select a position to attack between 0 and 11!
6
MISS
1 lifes remaining, 1 ships remaining
Please select a position to attack between 0 and 11!
7
HIT
YOU WIN
```

## Exercice 2 : Jeu du pendu

Dans cet exercice, vous allez créer un programme pour jouer au jeu du pendu.
Pour rappel, ce jeu consiste à retrouver un mot en proposant des lettres.
Si la lettre proposée apparaît dans le mot, toutes les occurrences de celle-ci sont dévoilées
et sinon le dessin d'une personne pendue est complété. Pour gagner, le mot doit être retrouvé
avant que le dessin soit complet. Pour cet exercice, le dessin sera remplacé par un nombre de vies.

Un argument d'entrée au programme doit permettre de choisir le nombre de vies selon le format suivant (`<n>` étant le nombre de vies voulu, valeur plus grande que 0) :

```
./pendu --lifes <n>
```

Si l'argument n'est pas renseigné, le nombre de vies est de 10.
Si d'autres valeurs sont renseignées, le programme doit quitter avec le message :

```
Usage: ./pendu [--lifes <n>]
```

Exemple :

```bash
$ ./pendu 5
Usage: ./pendu [--lifes <n>]

$ ./pendu --lifes
Usage: ./pendu [--lifes <n>]

$ ./pendu --lifes 5 1
Usage: ./pendu [--lifes <n>]

$ ./pendu --lifes 5
# Lance le programme avec 5 vies

$ ./pendu
# Lance le programme avec 10 vies
```

Au lancement du programme, le mot à deviner est choisi aléatoirement dans une liste
(= un tableau constant en dur dans le code fera l'affaire).
L'affichage suivant apparaît :

```
Lifes: 10
Tried letters:
-------------

Guess a letter or a word:
```

L'utilisateur peut alors entrer une lettre ou directement un mot.

En fonction de l'entrée les actions suivantes sont possibles :

  - Si une lettre est entrée et celle-ci n'est pas présente dans le mot, un message
    s'affiche pour l'indiquer à l'utilisateur et une vie est perdue.
  

    ```
    ...

    Guess a letter or a word: l
    l is not in the word...

    Lifes: 9
    Tried letters: l
    -------------

    Guess a letter or a word:
    ```


  - Si une lettre est entrée et celle-ci est présente dans le mot, un message indiquant le nombre d'occurrences
    s'affiche et la lettre est dévoilée.

    ```
    ...

    Guess a letter or a word: a
    There is 2 occurence of a in the word!

    Lifes: 9
    Tried letters: la
    -----a--a----

    Guess a letter or a word:
    ```

  - Si toutes les lettres sont dévoilées, le programme se termine avec un message indiquant à l'utilisateur qu'il a gagné.

    ```    
    ...

    Tried letters: loiur
    -ouri-

    Guess a letter or a word: s
    There is 2 occurence of s in the word!

    GG !! You win \o/
    ```

  - Si un mot est entré et ne correspond pas au mot recherché, un message s'affiche pour l'indiquer à l'utilisateur
    et deux vies sont perdues.

    ```
    Guess a letter or a word: language
    language isn't the word !

    Lifes: 7
    Tried letters: la
    -----a--a----

    Guess a letter or a word:
    ```

  - Si un mot est entré et correspond à celui recherché, un message indiquant que l'utilisateur à gagner
    s'affiche et le programme se quitte.

    ```
    ...

    Guess a letter or a word: programmation

    GG !! You win \o/
    ```

  - Quand toutes les vies sont perdues, que ce soit après avoir entré une mauvaise lettre ou mot,
    un message indiquant que l'utilisateur à perdu et le mot recherché s'affiche et le programme se termine.

    ```
    ...

    Lifes: 1
    Tried letters: aqwsxyrtgdvlpok
    progra--at-o-

    Guess a letter or a word: j
    j is not in the word...

    You loose... The word was programmation.
    ```

  - Tous les caractères entrés par l'utilisateur doivent être des lettres minuscules ou majuscules. Si une lettre déjà rentrée est saisie ou que tout autres caractères est rentré, une nouvelle saisie doit être faite :

    ```
    ...

    Lifes: 10
    Tried letters: p
    p------------

    Guess a letter or a word: p
    p has already been tried.
    Guess a letter or a word: chou-fleur
    - is not a letter.
    Guess a letter or a word: nombre10
    1 is not a letter.
    Guess a letter or a word:
    ```

Exemple 1 :

```
$ ./pendu --vies 5
Lifes: 5
Tried letters:
-------------

Guess a letter or a word: o
There is 2 occurence of o in the word!

Lifes: 5
Tried letters: o
--o--------o-

Guess a letter or a word: w
w is not in the word...

Lifes: 4
Tried letters: ow
--o--------o-

Guess a letter or a word: r
There is 2 occurence of r in the word!

Lifes: 4
Tried letters: owr
-ro-r------o-

Guess a letter or a word: p
There is 1 occurence of p in the word!

Lifes: 4
Tried letters: owrp
pro-r------o-

Guess a letter or a word: g
There is 1 occurence of g in the word!

Lifes: 4
Tried letters: owrpg
progr------o-

Guess a letter or a word: programmation

GG !! You win \o/
```

Exemple 2 :

```
$ ./pendu --vies 5
Lifes: 5
Tried letters:
------

Guess a letter or a word: l
l is not in the word...

Lifes: 4
Tried letters: l
------

Guess a letter or a word: o
There is 1 occurence of o in the word!

Lifes: 4
Tried letters: lo
-o----

Guess a letter or a word: i
There is 1 occurence of i in the word!

Lifes: 4
Tried letters: loi
-o--i-

Guess a letter or a word: u
There is 1 occurence of u in the word!

Lifes: 4
Tried letters: loiu
-ou-i-

Guess a letter or a word: r
There is 1 occurence of r in the word!

Lifes: 4
Tried letters: loiur
-ouri-

Guess a letter or a word: s
There is 2 occurence of s in the word!

GG !! You win \o/
```

Exemple 3

```
$ ./pendu --vies 5
Lifes: 5
Tried letters:
------

Guess a letter or a word: e
e is not in the word...

Lifes: 4
Tried letters: e
------

Guess a letter or a word: r
There is 1 occurence of r in the word!

Lifes: 4
Tried letters: er
---r--

Guess a letter or a word: d
d is not in the word...

Lifes: 3
Tried letters: erd
---r--

Guess a letter or a word: b
b is not in the word...

Lifes: 2
Tried letters: erdb
---r--

Guess a letter or a word: h
h is not in the word...

Lifes: 1
Tried letters: erdbh
---r--

Guess a letter or a word: p
p is not in the word...

You loose... The word was souris.
```
