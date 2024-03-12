# PRG2 L2 - Générateur de formes

Le but de ce laboratoire est d'entrainer l'utilisation de boucles de bases et des fonctions d'entrée / sortie, ainsi que les casts de types. 
## Groupe - Nom
- Nathan Füllemann
- Maxime Regenass
## Indications

En cas de besoin, vous êtes libres d'implémenter vous même la configuration du debugger pour votre travail.

N'oubliez pas de compléter les entêtes des fichiers modifiés!

## Exercice 1: générateur de formes

Dans cet exercice, l'utilisateur devra avoir accès à un menu lui permettant de choisir un type de forme à afficher, puis sa taille.

Au démarrage du programme, le menu devra s'afficher sous la forme suivante:

```
Welcome to the PRG2-24 shape generator!

Please select one of the following shape to display:

1: Square
2: Triangle
3: Reverse triangle
4: Diamond

```

L'utilisateur devra alors saisir une des formes à l'aide du numéro 1 à 4. La saisie devra bien sûr être vérifiée afin de s'assurer que la valeur soit valide.

En cas de saisie invalide (valeur trop grande, valeur non numérique, etc.), le message suivant devra s'afficher avant de permettre à l'utilisateur de saisir une nouvelle valeur:

```
Invalid shape! Please select a number between 1 and 4
```

Une fois le choix de la forme effectué, l'utilisateur devra choisir une taille pour l'affichage de sa forme. La taille devra toujours être au moins comprise entre 1 et 20. De plus, pour le losange, la taille devra forcément être impaire.

Pour la sélection de la taille, le message suivant devra s'afficher:

```
Now select a size for your shape
```

Bien entendu, la valeur saisie pour la taille de la forme doit également être vérifiée. En cas de mauvaise saisie, le message suivant doit s'afficher:
```
Invalid size! Please select a valid value
```

Pour les différentes formes, la taille peut être interprétée différement. Pour le carré elle représente le nombre de lignes / colonnes, pour le triangle la hauteur et pour le losange la largeur de la ligne centrale (la ligne la plus large).

Voici un exemple d'affichage des différentes formes avec une taille fixée à 5.

Carré:
```
*****
*****
*****
*****
*****
```

Triangle:
```
*
**
***
****
*****
```

Triangle inversé:
```
    *
   **
  ***
 ****
*****
```

Losange:
```
  *
 ***
*****
 ***
  *
```

Afin d'entraîner l'utilisation des différentes boucles, les contraintes suivantes sont à respecter:

* Pour le carré, vous ne pouvez utiliser que des boucles `for`
* Pour le triangle, vous ne pouvez utiliser que des boucles `do while`
* Pour le triangle inversé, vous ne pouvez utiliser que des boucles `while`
* Pour le losange, vous êtes libres d'utiliser les boucles de votre choix.

Après l'affichage de la forme demandée, le programme devra se terminer sans erreur. 

Voici un exemple d'utilisation du programme (avec des commentaires pour votre compréhension):

```
Welcome to the PRG2-24 shape generator!

Please select one of the following shape to display:

1: Square
2: Triangle
3: Reverse triangle
4: Diamond
6 // saisie de la valeur 6 par l'utilisateur
Invalid shape! Please select a number between 1 and 4
4 // saisie de la valeur 4 par l'utilisateur

Now select a size for your shape
8 // saisie de la valeur 8 par l'utilisateur (valeur paire)
Invalid size! Please select a valid value
59 // saisie de la valeur 59 par l'utilisateur (valeur trop grande)
Invalid size! Please select a valid value
7 // saisie de la valeur 7 par l'utilisateur
   *
  ***
 *****
*******
 *****
  ***
   *
```

Pour cet exercice, un fichier `shape.c` vous a été fourni et doit être complété.

## Exercice 2: problèmes de types

Pour cet exercice, nous vous avons fourni un code `variables.c` qui contient un programme qui, à première vue, fonctionne correctement. Dans ce programme, plusieurs calculs et affichages sont effectués, mais comme indiqué en commentaires, les résultats affichés ne sont pas ceux attendus. Vous devez donc vous baser sur les résultats demandés en commentaires pour trouver comment corriger les différences en ajoutant des casts et / ou en adaptant les formats d'affichages pour les `printf`!

IMPORTANT: Vous ne pouvez pas toucher aux types des variables directement, ni créer de nouvelles variables. Seuls les casts sont autorisés!
