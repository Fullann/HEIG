# Rapport_CRY_labo03 - Nathan Füllemann
## Exercice 1 - “Encryption”
### Donnée
Le fichier encryption.sage contient un algorithme de chiffrement asymétrique.
1. Dessinez un schéma correspondant à cet algorithme. (0.2 pts)
2. Donnez une description mathématique du chiffrement et du déchiffrement correspondant.
(0.2 pts)
Indice : Regardez bien ce que fait la fonction pad.
3. Implémentez le déchiffrement. Testez votre code et montrez votre test dans votre rapport. (0.3
pts)
4. On suppose que les quatre racines carrées d’un texte chiffré ont fuité lors du déchiffrement. Vous
trouverez dans votre fichier de paramètres la clef publique n, un message clair m, son texte chiffré
correspondant c, les quatre racines carrées de c. Vous trouverez aussi un texte chiffré “challenge”
chiffré avec la même clef. Décryptez-le. Donnez dans votre rapport le message récupéré ainsi
qu’une explication mathématique expliquant votre attaque. (1 pt)
Indice : Visualisez ces racines dans Zp × Zq et effectuez des opérations sur ces dernières afin
d’obtenir un multiple de p ou de q.
5. Sur quel problème difficile est basé cette construction ? (0.1 pt)
6. A quoi sert la redondance dans la construction (variable REDUNDANCY) ? (0.2 pts)
## Réponses


---
## Exercice 2 - Courbes Elliptiques
### Donnée
Vous trouverez dans le fichier elliptic.sage un algorithme de chiffrement asymétrique basé sur les
courbes elliptiques.
1. Dessinez un schéma correspondant à cet algorithme. (0.2 pts)
2. Donnez une description mathématique du chiffrement et du déchiffrement correspondant.
(0.2 pts)
3. Implémentez le déchiffrement. Testez votre code et montrez votre test dans votre rapport. (0.3
pts)
4. Il y a un problème dans cet algorithme. Lequel ? (0.1 pts)
5. Cassez la construction. Vous trouverez dans votre fichier de paramètres la clef publique et un texte
chiffré complet (avec nonce et tag). Tout est en base64. Donnez dans votre rapport le message
récupéré ainsi qu’une explication de votre attaque. (1 pt)
6. Corrigez l’erreur dans la construction. (0.2 pts)
### Réponses


---
## Exercice 3 - RSA (1pt)
### Donnée
Vous trouverez dans le fichier rsa.sage une implémentation de textbook RSA.
1. Implémentez le déchiffrement. Testez votre code et montrez votre test dans votre rapport. (0.5
pts)
2. Cassez la construction. Vous trouverez dans votre fichier de paramètres la clef publique et un texte
chiffré complet. Le texte chiffré est en base64. Donnez dans votre rapport le message récupéré ainsi
qu’une explication de votre attaque. (0.5 pts)

### Réponses
1) Implementation du decode RSA
```
Test du système RSA:
Message original: b'Crypto'
Message chiffré: 0e3efc03db1255b4619b7160994c39581fa270ce33a2316a671a3bc0c299eb1f...
Message déchiffré: b'Crypto'
```

2) Cassage de la construction
#### Cassage de la construction
On peut voir que cette ligne est problematique ```q = next_prime(p + ZZ.random_element(2^15))```. Car en temps normal dans la génération d'une clés RSA **p** et **q** ne sont pas en relation. Ici **q** depend de **p** et donc cela réduis l'espace de recherche pour un attaquant qui tenterait de factoriser n. Car au lieu de chercher parmi tous les nombres premiers possibles, il va le faire uniquement sur ceux qui sont proches de la racine carrée de n dans l'intervalle 2^15.

#### Résultat
Message déchiffré : **What is your quest? To seek the holy grail. What is your favorite color? waiving**