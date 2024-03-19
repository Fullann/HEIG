# Rapport Labo 2 - Récursivité
## Auteurs
- Nathan Füllemann
- Maxime Regenass
## Première approche du code 
#### A chaque étape

- On a un vecteur des pièces disponibles, dans toutes leurs rotations
- Dès qu'une pièce est testée (solution valide ou non), on la retire des pièces à tester en position X
- On teste jusqu'à ne plus avoir de pièces à tester (vecteur vide)
#### Etape
- 1ère pièce - Pas de check => 1er emplacement : on peut mettre l'ensemble des pièces, dans l'ensemble des positions -> Vecteur de pièces dans leurs positions
- pièces 2 et 3 -> check à gauche
- pièce 4 -> check en haut (1ère ligne)
- pièces 5 et 6 -> check gauche et en haut
- pièce 7 -> check en haut (2ème ligne)
- pièces 8 et 9 -> check en haut et à gauche ()

#### Déplacement dans le vecteur
Cases adjacentes calculées avec n%3 (colonne) et n/3 (ligne)
#### Methode
En paramètres -> vecteur de pièces pour la solution actuellement testée

Type de retour : void
1 vecteur (les solutions)
1 vecteur (la solution en cours de test)
1 vecteur (Pieces encore disponibles)
#### Cas de win
Si on a un vecteur de 9 pièces pour la solution -> on l'ajoute à la liste de solutions

#### Comment s'y prendre
On crée un vecteur avec toute les conditions possible. On regarde chaque possibilité savoir si elle fonctionne ou pas si oui on l ajoute au vecteur de solution 
## Nombre de possibilité
9! * 4^9 = 95'126'814'720
Car on a 9 pieces donc dans la première pièce dans la première case puis la deuxieme dans la seconde case et ainsi de suite donc 9*8*7*6*5*4*3*2*1. Puis ensuite chaque  pièce peut etre dans 4 direction différente puis les 9 pièces 
## Les solutions 
Toutes les solutions :
- 1b 5d 4a 7a 6a 2a 8a 3a 9d
- 1c 9a 6b 2a 4b 8b 7a 3a 5a
- 4b 2b 9a 5a 6b 3b 1c 7b 8b
- 5c 3c 7c 8d 4d 2c 6d 9c 1a
- 6c 8c 5b 9b 4c 3b 1d 2b 7b
- 7d 2d 1b 3d 4a 9d 5d 8a 6a
- 8d 7d 1a 3d 6d 5c 9c 2d 4d
- 9b 3c 8c 2c 6c 7c 4c 5b 1d 
## Nombre d'appel de la methode recursive
Nombre d'appel : 2819