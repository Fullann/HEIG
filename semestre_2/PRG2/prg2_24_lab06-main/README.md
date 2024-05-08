# PRG2 L6 - Structures, unions et directives de compilation

Le but de ce laboratoire est d'entraîner l'utilisation des structures, des unions, des directives de compilation ainsi que la compilation de programmes à fichiers multiples.
## Groupe
- Nathan Füllemann 
- Maxime Regenass
## Exercice 1 : Star Wars

Dans cet exercice, vous allez devoir réaliser un travail de modélisation d'une flotte spatiale sur le thème de Star Wars.

La flotte devra être créée par l'utilisateur au début de l'exécution à l'aide d'un menu, puis, une fois toutes les entrées saisies, les informations sur la flotte seront affichées par le programme au format YAML ou au format "texte lisible".

Pour ce travail, nous vous avons fourni un fichier `main.c` quasiment complet. Mais ce fichier ne compile pas correctement, car il utilise des structures pas encore déclarées. A vous de déclarer les éléments nécessaires dans les fichiers correspondants. Vous n'avez le droit de modifier le fichier `main.c` qu'aux endroits où des `TODO` ont été placés.

La structure représentant la flotte devra être créée dans le fichier `ship.h`, elle doit contenir les éléments suivants:

* Un pointeur sur une zone mémoire allouée dynamiquement (déjà fait dans le fichier `main.c`) pour les différents vaisseaux.
* Le nombre courant de vaisseaux dans la flotte.
* Le nombre maximal de vaisseaux pour la flotte.

Dans le fichier `ship.h` la structure `ship` doit aussi être mise en place pour contenir les informations communes aux différents vaisseaux. Les informations spécifiques à ces derniers seront quant à elles séparées dans les différents fichiers correspondants.

Les informations à gérer pour les vaisseaux sont les suivantes:

* Le nom du vaisseau: chaîne de caractère de longueur quelconque et pouvant contenir des espaces.
* Le nom modèle du vaisseau: chaîne de caractère de longueur quelconque et pouvant contenir des espaces.
* Le type de vaisseau parmi les trois types suivants: vaisseau de combat, vaisseau cargo et vaisseau de commandement.

Les informations spécifiques à chaque type de vaisseaux sont les suivantes:

Vaisseaux de combat:
* Le nom du pilote du vaisseau: chaîne de caractère de longueur quelconque et pouvant contenir des espaces.
* La série de son astromech (droïde) pouvant être l'une des suivantes: Série R1, Série R2, Série R3, Série BB.

Vaisseaux cargo:
* Le poids maximum de la cargaison

Vaisseaux de commandement:
* Le nom du commandant du vaisseau: chaîne de caractère de longueur quelconque et pouvant contenir des espaces.
* Le nombre de passagers du vaisseau.

Les parties spécifiques des données des vaisseaux doivent être stockées dans des structures dans leur fichier correspondant. A vous d'instancier ces structures le plus proprement possible dans la structure principale, sans utiliser de pointeur.

Les seuls éléments à allouer dynamiquement pour les vaisseaux (en plus de l'allocation déjà réalisée dans le fichier `main.c`) sont les espaces mémoires utilisés pour les différentes chaînes de caractères.

Une fois les éléments nécessaires à la modélisation du problème mis en place, il vous restera à implémenter les différentes fonctions permettant d'ajouter de nouveaux vaisseaux et d'afficher les informations relatives à ces derniers dans les deux formats possibles. Bien entendu, pensez à décomposer ces dernières dans les différents fichiers!

Dans le fichier `config.h`, vous devrez mettre en place un simple `define` permettant de choisir si l'affichage des informations sur la flotte se fait au format YAML ou au format texte. Le choix entre les deux versions d'affichage doit ensuite être réalisé à l'aide des directives de compilation.

Concernant les saisies utilisateur, vous pouvez partir du principe que lorsqu'un nombre est attendu, l'utilisateur ne saisira que des nombres, même chose pour les strings. Vous devez néanmoins vérifier que les valeurs saisies soient valides par rapport à ce qui est attendu (par exemple, un nombre de vaisseaux négatif pour la flotte n'est pas accepté, une saisie de la série ABC pour la série d'astromech ne serait pas acceptée non plus).

Conseil: Pour vos tests vous pouvez sans autre créer un fichier input.txt avec la liste des inputs à donner à votre programme (une input par ligne), puis appeler votre exécutable de la façon suivante: `./nom_executable < input.txt` cela effectuera automatiquement la saisie des différents éléments présents dans le fichier et vous fera gagner du temps si vous voulez effectuer des tests rapidement avec les deux versions d'affichage.

Voici deux exemples d'utilisation du programme afin de clarifier le fonctionnement de ce dernier.

Avec affichage format YAML:
```
Please select the number of ships for your fleet
3
Ship number 1:
Please enter a name for your ship!
Anakin Skywalker's Venator
Please enter a model for your ship!
Venator-Class Republic Attack Cruiser
Please choose the ship type:
1: Combat ship
2: Cargo ship
3: Command ship
3
Please enter the commander's name!
Wullf Yularen
Please enter the number of passengers in the ship!
3200

Ship number 2:
Please enter a name for your ship!
Millennium Falcon
Please enter a model for your ship!
YT-1300F
Please choose the ship type:
1: Combat ship
2: Cargo ship
3: Command ship
2
Please enter the maximum cargo's weight that the ship can transport!
100000

Ship number 3:
Please enter a name for your ship!
Red Five
Please enter a model for your ship!
X-wing
Please choose the ship type:
1: Combat ship
2: Cargo ship
3: Command ship
1
Please enter the pilot's name!
Luke Skywalker
Please choose an astromech serie from the following list: R1 R2 R3 BB
R2

- name: Anakin Skywalker's Venator
  mode: Venator-Class Republic Attack Cruiser
  type: command
  commander_name: Wullf Yularen
  nb_passengers: 3200
- name: Millennium Falcon
  mode: YT-1300F
  type: cargo
  max_cargo_weght [kg]: 100000
- name: Red Five
  mode: X-wing
  type: combat
  pilot_name: Luke Skywalker
  droid_serie: r2_series
```

Avec affichage format texte:
```
Please select the number of ships for your fleet
3
Ship number 1:
Please enter a name for your ship!
Anakin Skywalker's Venator
Please enter a model for your ship!
Venator-Class Republic Attack Cruiser
Please choose the ship type:
1: Combat ship
2: Cargo ship
3: Command ship
3
Please enter the commander's name!
Wullf Yularen
Please enter the number of passengers in the ship!
3200

Ship number 2:
Please enter a name for your ship!
Millennium Falcon
Please enter a model for your ship!
YT-1300F
Please choose the ship type:
1: Combat ship
2: Cargo ship
3: Command ship
2
Please enter the maximum cargo's weight that the ship can transport!
100000

Ship number 3:
Please enter a name for your ship!
Red Five
Please enter a model for your ship!
X-wing
Please choose the ship type:
1: Combat ship
2: Cargo ship
3: Command ship
1
Please enter the pilot's name!
Luke Skywalker
Please choose an astromech serie from the following list: R1 R2 R3 BB
R2

Ship number 1:
Ship name: Anakin Skywalker's Venator
Ship model: Venator-Class Republic Attack Cruiser
Ship type: Command
Commander's name: Wullf Yularen
Number of passengers: 3200

Ship number 2:
Ship name: Millennium Falcon
Ship model: YT-1300F
Ship type: Cargo
Max cargo weight [kg]: 100000

Ship number 3:
Ship name: Red Five
Ship model: X-wing
Ship type: Combat
Pilot's name: Luke Skywalker
Droid serie: R2 series
```
