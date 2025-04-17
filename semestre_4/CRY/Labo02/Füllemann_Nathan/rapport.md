# Labo 02
## Ex1 - Spongy AES (1.5 pts)
### Partie 1
>Dessinez un schéma de la construction pour un message de 19 caractères ASCII. Soyez le plus précis possible concernant le “rate” et la taille de la sortie.

### Partie 2 
> Vous avez que le message a la forme suivante FLAG{...} avec 13 caractères entre les accolades.Vous trouverez dans votre fichier de paramètres le hash de ce message. Récupérez le message. Expliquez dans votre rapport comment vous avez procédé. Indice : vous aurez besoin de faire un peu de bruteforce. Vous savez aussi que le flag ne contient uniquement des caractères ASCII imprimables.

Flag trouvé : `FLAG{disengagement}`

## Ex2 - GCM (2.5 pts)
### Partie 1 
> Trouvez une erreur d’implémentation dans ce code. La fonction f dans le code est correcte et fait partie du standard. Elle permet de fixer une représentation des éléments. L’inverse de la fonction f est f elle-même.

L'erreur principale se situe dans la fonction authenticate où la transformation f est appliquée deux fois de manière incorrecte :

Sur chaque bloc de texte chiffré avant son traitement dans GHASH

Sur le tag final après calcul

Dans le standard GCM, les blocs de texte chiffré sont traités directement dans GHASH sans transformation préalable. L'application de f (qui est une conversion endianness) à ce stade introduit une divergence par rapport au standard.

### Partie 2
>  Implémentez la déchiffrement GCM tout en conservant l’erreur d’implémentation. Testez votre implémentation.
``` py
def GCM_Decrypt(key, IV, c, t):
    cipher = AES.new(key, AES.MODE_ECB)
    T = cipher.encrypt(IV + b"\x00"*(COUNTER_SIZE -1) + b"\x01")
    calculated_tag = authenticate(key, c, T)
    
    if calculated_tag != t:
        raise Exception("Tag invalide")
    
    return CTR(key, IV, c)

```
### Partie 3
> Vous trouverez dans votre fichier de paramètres deux textes chiffrés (iv, chiffré, tag) ainsi que le texte clair correspondant au premier message. Que remarquez-vous d’étrange dans ces textes chiffrés?

Les deux messages partagent le même IV mais ont des tags différents. Ce comportement est critique car GCM exige des IV uniques pour chaque message sous la même clé, sous peine de compromettre la sécurité.


### Partie 4
> Récupérez le texte clair correspondant au deuxième texte chiffré (iv2, c2, t2). Expliquez votre attaque dans votre rapport

### Partie 5
> Cassez aussi l’intégrité en fournissant un texte chiffré valide (iv, c, t) en base64 correspondant au message mChall que vous trouverez dans votre fichier de paramètres


## Ex3 - Speck (1 pt)

### Partie 1
>Lorsqu’un client légitime se connecte, il n’a pas forcément pu récupérer l’IV. Expliquez comment il peut tout de même récupérer le mot de passe. Un client connait la clef secrète utilisée par Speck. On suppose que le message est aligné sur la taille des blocs.

Le client légitime peut récupérer le mot de passe sans l'IV grâce aux propriétés du mode CBC et de la structure connue du message. Voici le mécanisme :

## Mécanisme de récupération
1. **Décryptage partiel** :  
   Avec la clé secrète, le client déchiffre tous les blocs **sauf le premier** (qui dépend de l'IV inconnu) en utilisant la relation CBC :  
   $$
   P_i = \text{Decrypt}(C_i) \oplus C_{i-1}
   $$
   
2. **Exploitation de la structure périodique** :  
   Le message clair étant de la forme `[password][0000][password][0000]...`, les blocs pairs (2,4,6...) contiennent toujours :  
   $$
   P_{2k} = \text{password} \oplus \text{Decrypt}(C_{2k-1})
   $$
   
3. **Isolation du motif** :  
   En XORant deux blocs clairs consécutifs :  
   $$
   P_{2k} \oplus P_{2k+2} = (\text{password} \oplus X) \oplus (\text{password} \oplus X) = 0
   $$
   La différence nulle révèle la période du motif.



### Partie 2
> Vous avez intercepté une partie de cette séquence chiffrée2 mais vous n’avez pas réussi à récupérer
l’IV utilisé pour chiffrer le message. Cette séquence (en base64) se trouve dans un fichier séparé
nommé prenom_nom-speck.txt. Le main du fichier speck.py contient aussi tout le code de la
tour radio. Le fichier contenant la séquence chiffrée est très grand. N’essayez pas de l’ouvrir
avec votre éditeur de texte. Récupérez le mot de passe et indiquez-le dans votre rapport. Expliquez aussi comment fonc-
tionne votre attaque et pourquoi elle fonctionne.
Indice : est-ce que des blocs de texte chiffrés se répètent? Faites un schéma pour comprendre ce
que cela implique.

Mot de passe trouvé : `C5)Z`

### Partie 3
>Est-ce que cette attaque fonctionnerait aussi sur AES-CBC? Justifiez et soyez précis.

L'attaque spécifique utilisée sur Speck en mode CBC **ne fonctionne pas directement sur AES-CBC** en raison de différences structurelles critiques. Voici l'analyse détaillée :

---

#### 1. **Différence de taille de bloc**
- **Speck** : Bloc de **32 bits** → Collisions probables après $$2^{16}$$ blocs (paradoxe des anniversaires).
- **AES** : Bloc de **128 bits** → Collisions attendues après $$2^{64}$$ blocs, rendant les répétitions **improbables** en pratique[7][15].

---

#### 2. **Mécanisme CBC et dépendance contextuelle**
En CBC, chaque bloc chiffré $$C_i$$ dépend du précédent ($$C_{i-1}$$). Même avec un texte clair répétitif :
- Pour Speck (32 bits), la structure `[password][0000]` génère rapidement un cycle $$C_a, C_b$$ par saturation des combinaisons.
- Pour AES (128 bits), la probabilité de cycle est **négligeable** sans réutilisation d'IV ou de clé[12][15].

---

#### 3. **Conditions nécessaires pour une attaque similaire**
L'attaque sur Speck repose sur deux conditions :
1. **Texte clair périodique** avec une période courte (ex : 8 octets).
2. **Taille de bloc réduite** permettant des collisions rapides.

Avec AES-CBC :
- Une période de texte clair de **16 octets** (taille de bloc AES) serait nécessaire.
- Même dans ce cas, l'absence de collisions probables empêcherait la détection du motif[15][16].

---

#### 4. **Vulnérabilités alternatives d'AES-CBC**
Bien que résistant à cette attaque, AES-CBC présente d'autres risques :
- **Malléabilité** : Modification ciblée de blocs chiffrés pour altérer le texte clair (ex : attaques par oracle de remplissage)[2][3].
- **Réutilisation d'IV** : Si l'IV est réutilisé, des patterns pourraient être exploités (contre-indiqué par les bonnes pratiques)[19].

---

#### 5. **Preuve par simulation**
Supposons un texte clair répétitif `P = [secret][0000][secret][0000]...` :
- **AES-CBC** : Les blocs chiffrés $$C_i = \text{Encrypt}(P_i \oplus C_{i-1})$$ varient même si $$P_i$$ se répète, car $$C_{i-1}$$ change.
- **Speck-CBC** : La petite taille de bloc permet $$C_{i-1}$$ de boucler rapidement, annulant l'effet de propagation.

---

#### Conclusion
L'attaque sur Speck-CBC **ne s'applique pas à AES-CBC** en raison de sa taille de bloc élevée et de la dépendance contextuelle renforcée. Cependant, AES-CBC nécessite toujours :
- Un **IV aléatoire** pour chaque chiffrement.
- Une **authentification** (ex : HMAC) pour contrer les attaques par malléabilité[2][12]. 

