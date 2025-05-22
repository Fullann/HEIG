# Rapport_CRY_labo03 - Nathan Füllemann
## Exercice 1 - “Encryption” (2 pts)
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
1) Schema de l'algorithme
   
2) Description mathématique
### 🔒 Chiffrement

Soit :

* $n = pq$, où $p \equiv q \equiv 3 \mod 4$ sont deux grands nombres premiers,
* $m \in \{0,1\}^*$ le message en clair (de taille limitée),
* $r \in_R \{0,1\}^{128 \cdot 8}$ une chaîne aléatoire de 128 octets,
* $\text{MGF}(r, \ell)$ une fonction de masquage déterministe basée sur $r$ et de longueur $\ell$,
* $\text{pad}(m)$ le message avec un padding ISO/IEC 7816-4, qui ajoute un octet `0x80` suivi de `0x00` jusqu'à atteindre la taille cible.

**Étapes mathématiques** :

1. **Padding :**
   $m_{\text{pad}} = \text{pad}(m) \in \{0,1\}^{\ell}$

2. **Masquage :**
   $h = \text{MGF}(r, \ell)$
   $m' = m_{\text{pad}} \oplus h$

3. **Concaténation :**
   $x = \text{bytes\_to\_int}(m' \Vert r) \in \mathbb{Z}_n$

4. **Chiffrement :**
   $c = x^2 \mod n$
3) Déchiffrement
```bash
message chiffrer 4797148059281529151495676506019336499464708436785113748063530450732414481910008224707369356073621842177629480469407532919011276074309454798348097723927551868931234469946810459479631141738406546806325885434152122243782147978292290291687261051811081721171744941664530668184818675442858940482085412097854925131937806027795295848578623280899134920297302485946270035823082851444966566051043336156924679108833832882130655444003315796213567400873910689962479856374717408566335203345459495463096924671485957903564365579619235635722100831129105001249814555747800201088091780586779655220053654642805809340642855002832234386705
Message original : b'Crypto'
Message déchiffré : b'Crypto'
Succès : True
```
4) Crackage de l'algorithme
   1) Cassage de l'algorithme
   
   En connaissant les 4 racines carrées $r_1, r_2, r_3, r_4$ d’un même message chiffré $c$, on peut factoriser $n$ en exploitant le fait que :

   $$
   r_1^2 \equiv r_2^2 \mod n \Rightarrow (r_1 - r_2)(r_1 + r_2) \equiv 0 \mod n
   $$

   Donc :

   $$
   \gcd(r_1 - r_2, n) = p \quad \text{ou} \quad q
   $$
   Donc contrairement au chiffrement Rabin qui évite ceci mon attaque se base sur les 4 racines et une fois $p$ et $q$ obtenus, on peut déchiffrer n’importe quel message chiffré avec $n$.

   2) Résulatat
   ```bash
   Facteurs récupérés : p = 165527578793874775288637020134360874828287960545808881015503547430743992512185022046154882144120894948748692714168867874056900947085017148379777857236454071168518109382923294809412723291436760492193302946115214232181484394963264815599872596866716045202444484303370094099885997741978603541401937724171469351287, q = 151454526570491640123745343356079546942489923225137567709201369042178064633128913941609018141463041177517168901467680700472427469466049668791084679886130740036494968497881663299556130588091177886494119170940628249190959995538363602544627503352168620331766413607101622605419905721240043982894884925519168755811
   Facteurs récupérés : p = 151454526570491640123745343356079546942489923225137567709201369042178064633128913941609018141463041177517168901467680700472427469466049668791084679886130740036494968497881663299556130588091177886494119170940628249190959995538363602544627503352168620331766413607101622605419905721240043982894884925519168755811, q = 165527578793874775288637020134360874828287960545808881015503547430743992512185022046154882144120894948748692714168867874056900947085017148379777857236454071168518109382923294809412723291436760492193302946115214232181484394963264815599872596866716045202444484303370094099885997741978603541401937724171469351287
   Facteurs récupérés : p = 165527578793874775288637020134360874828287960545808881015503547430743992512185022046154882144120894948748692714168867874056900947085017148379777857236454071168518109382923294809412723291436760492193302946115214232181484394963264815599872596866716045202444484303370094099885997741978603541401937724171469351287, q = 151454526570491640123745343356079546942489923225137567709201369042178064633128913941609018141463041177517168901467680700472427469466049668791084679886130740036494968497881663299556130588091177886494119170940628249190959995538363602544627503352168620331766413607101622605419905721240043982894884925519168755811
   Message challenge déchiffré : b'Ni! Ni! Ni! We want a adenoidal'
   ```
5) Le problème difficile
Le problème difficile est la difficulté de factoriser un grand entier n = p*q où p et q sont des très grand nombre premier et $p \equiv q \equiv 3 \mod 4$.

6) La redondance dans la construction
Dans ce bout de code 
```py
if len(m) > BYTE_LEN_MESSAGE_PART - REDUNDANCY - 1:
    raise Exception("Message too long.")
```
On peut trouver le paramètre **REDUNDANCY**


---
## Exercice 2 - Courbes Elliptiques (2 pts)
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
1) Schéma de la construction

2) Description mathématique
   1) **Paramètres publics et secrets**
   On utilise une **courbe elliptique** $E/\mathbb{F}_p$, définie par cette équation:
    $$
    E: y^2 = x^3 + ax + b \quad \text{sur} \quad \mathbb{F}_p
    $$
    Avec :
      * $p \in \mathbb{N}$ : un nombre premier
      * $a, b \in \mathbb{F}_p$
      * $G \in E(\mathbb{F}_p)$ : un générateur d'ordre $n$
      * $n \in \mathbb{N}$ : l’ordre du point $G$
  
   1) **Génération de clé**
   Chaque utilisateur choisit :
      * Une **clé privée** $a \in \mathbb{Z}_n$
      * Une **clé publique** $A = aG \in E(\mathbb{F}_p)$
   2) **Chiffrement**
Pour chiffrer un message $M \in \{0,1\}^*$ (des octets), l'algorithme suis ses étapes :
      1. **Choix aléatoire** : $r \in \mathbb{Z}_n$
      2. **Calcul du point partagé (ECDH)** :
      $$
      P = rA = r(aG) = arG \in E(\mathbb{F}_p)
      $$
      3. **Compression du point** $P$, puis dérivation d'une **clé symétrique** $k$ à partir de $P$ :
      $$
      k = \text{HKDF}(\text{compress}(P), \text{len}=32)
      $$
      4. **Chiffrement AES-GCM** :
      $$
      \text{AES-GCM}_k(M) = (\text{nonce}, C, \text{tag})
      $$
      5. L’expéditeur envoie :
      $$
      \text{C} = (R, \text{nonce}, C, \text{tag})
      $$
      où $R = rG \in E(\mathbb{F}_p)$ est la **clé publique éphémère** (compressée).
   1) **Déchiffrement**
        Le destinataire, possédant la clé privée $a$, reçoit $R = rG$ et :
        1. **Recalcule le point partagé** :
        $$
        P = aR = a(rG) = arG
        $$
        2. **Dérive la clé symétrique** :
        $$
        k = \text{HKDF}(\text{compress}(P), \text{len}=32)
        $$
        3. **Déchiffre avec AES-GCM** :
        $$
        M = \text{AES-GCM}_k^{-1}(\text{nonce}, C, \text{tag})
        $$
3) Implémentation du déchiffrement
   ```bash
   Paramètres de la courbe elliptique
    - Générateur G : (34736706601617260336801089627448256371787243214661931571076381713565253696521 : 5887497935320424287803691270199037907654978138532428031269063384390017951571 : 1)
    - Ordre n       : 2550513000803
    - Equation      : Elliptic Curve defined by y^2 = x^3 + 43327883319811199442996705732365163443043431995328598938729525921048235234958*x + 45494814375791703888029144132071347443317277861841182091738819980027414195528 over Finite Field of size 50043062554237280172405801360375653460619548838234052036762494431728976610313

    Clés de Bob
    - Clé privée a  : 963178213981
    - Clé publique A: (13976030234605413735643637033165381524432614984208610805756637485647500884502 : 35824549147280859880677490714451853472127394838790221812639000505508885181579 : 1)

   Message clair à chiffrer : Crypto

    Chiffrement par Alice
    - Point éphémère R (compressé) : 0224f3b266d0b8f75a2db2dfd7b07b92ed5d8bf089a7080de13222d7f69db25c59
    - Nonce AES                    : f2583519a4ed55affd03e5195006959d
    - Ciphertext                   : fdbef7e54cf0
    - Tag                          : ec216a1b8127eb3d9ee16b6a5c405357
    - Message déchiffré : Crypto

   Le message envoyé de Bob et celui d'Alice sont les même  
   ```
4) Problème de l'algorithme
   
5) Cassage de la construction

6) Correction de l'erreur
---
## Exercice 3 - RSA (1pt)
### Donnée
Vous trouverez dans le fichier rsa.sage une implémentation de textbook RSA.
1. Implémentez le déchiffrement. Testez votre code et montrez votre test dans votre rapport. (0.5
pts)
1. Cassez la construction. Vous trouverez dans votre fichier de paramètres la clef publique et un texte
chiffré complet. Le texte chiffré est en base64. Donnez dans votre rapport le message récupéré ainsi
qu’une explication de votre attaque. (0.5 pts)

### Réponses
1) Implementation du decode RSA
```bash
Message original: b'Crypto'
Message chiffré: 0e3efc03db1255b4619b7160994c39581fa270ce33a2316a671a3bc0c299eb1f...
Message déchiffré: b'Crypto'
```

2) Cassage de la construction
#### Cassage de la construction
On peut voir que cette ligne est problematique ```q = next_prime(p + ZZ.random_element(2^15))```. Car en temps normal dans la génération d'une clés RSA **p** et **q** ne sont pas en relation. Ici **q** depend de **p** et donc cela réduis l'espace de recherche pour un attaquant qui tenterait de factoriser n. Car au lieu de chercher parmi tous les nombres premiers possibles, il va le faire uniquement sur ceux qui sont proches de la racine carrée de n dans l'intervalle 2^15.

#### Résultat
Message déchiffré : **What is your quest? To seek the holy grail. What is your favorite color? waiving**