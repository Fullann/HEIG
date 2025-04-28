# Labo 02
## Ex1 - Spongy AES (1.5 pts)
### Partie 1
>Dessinez un schéma de la construction pour un message de 19 caractères ASCII. Soyez le plus précis possible concernant le “rate” et la taille de la sortie.

### Partie 2 
> Vous avez que le message a la forme suivante FLAG{...} avec 13 caractères entre les accolades.Vous trouverez dans votre fichier de paramètres le hash de ce message. Récupérez le message. Expliquez dans votre rapport comment vous avez procédé. Indice : vous aurez besoin de faire un peu de bruteforce. Vous savez aussi que le flag ne contient uniquement des caractères ASCII imprimables.

Flag trouvé : `FLAG{disengagement}`
comment j'ai fait :
En premier j ai fait une boucle pour brute-force le 16ème octet manquant en exploitant la propriété ECB où chaque bloc est chiffré indépendamment. Ensuite j'inverse une opération de chiffrement via decrypt(). Puis pour finir je fait un brut force sur 3 caractères qui me  permet de valider le format du flag. Et enfin j'utilise un xor() qui me permet d'annuler l'effet du chiffrement sur les blocs connus.

## Ex2 - GCM (2.5 pts)
### Partie 1 
> Trouvez une erreur d’implémentation dans ce code. La fonction f dans le code est correcte et fait partie du standard. Elle permet de fixer une représentation des éléments. L’inverse de la fonction f est f elle-même.

Erreur d'implémentation
```py
ctr = (IV + b"\x00"*(COUNTER_SIZE-1)+b"\x02")  # Erreur ici
```
En GCM standard, le compteur CTR doit commencer à 1 pour le chiffrement initial.Le code initialise le compteur avec b"\x02", décalant toutes les opérations de chiffrement/déchiffrement. Donc cela entraine chiffrement/déchiffrement incorrect des blocs etl échec systématique de la vérification du tag d'authentification.
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

Les deux messages partagent le même IV mais ont des tags différents. Ce comportement est bizarre car GCM exige des IV uniques pour chaque message sous la même clé, sous peine de compromettre la sécurité.


### Partie 4
> Récupérez le texte clair correspondant au deuxième texte chiffré (iv2, c2, t2). Expliquez votre attaque dans votre rapport
``` py
import base64

m1       = b'This is a Test !'
iv1      = b'W5ZS9Yu3dEs3hDtB'
c1       = b'2s9IB8rcQZh/Gljgb+WWQw=='
t1       = b'MD4tYk+xhF1j58oX7m3AXA=='
iv2      = b'W5ZS9Yu3dEs3hDtB'
c2       = b'3sZSB8qIEtFqU2LgbvDEGw=='
t2       = b'IajN3Q9omEsjsAS2nbg9SA=='
mChall   = b'100.00CHF to ADC'

def xor(data1, data2):
	return bytes(a ^ b for a, b in zip(data1, data2))

c1_xor_c2 = xor(base64.b64decode(c1), base64.b64decode(c2))
m2 = xor(c1_xor_c2, m1)
print(f"m2: {m2}")
```

m2: b'Pass = itinerary'
Explication :
J'utilise une faille liée à la réutilisation du vecteur d'initialisation (IV) dans le mode de chiffrement de type flux. Donc pour l'attaque j'utlise ses deux propriétés:
1. **XOR inversible** : $$ a \oplus b \oplus b = a $$
2. **Réutilisation de keystream** : même IV → même séquence de chiffrement
En premier je combine les deux ciphertexts avec un xor puis je récupère le message m2 via le known-plaintext (m1)

### Partie 5
> Cassez aussi l’intégrité en fournissant un texte chiffré valide (iv, c, t) en base64 correspondant au message mChall que vous trouverez dans votre fichier de paramètres
Je trouve ceci en base64 

IV forgé : VzVaUzlZdTNkRXMzaER0Qg==
Cihertext forgé : v5cRWtqFcfBYGnjqPNDyIQ==
Tag forgé : MD4tYk+xhF1j58oX7m3AXA==

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

Explication :

**1. Structure du message clair**  
La tour radio diffuse en boucle une séquence `mot_de_passe + 4 octets nuls`, chiffrée en CBC avec un IV inconnu. Cette répétition crée un motif identifiable dans le texte chiffré.

**2. Propriétés du mode CBC**  
En déchiffrement CBC, chaque bloc clair est obtenu par :
$$ P_i = D(C_i) \oplus C_{i-1} $$
où $$ D $$ est la fonction de déchiffrement du bloc, et $$ C_{i-1} $$ le bloc chiffré précédent.

**3. Exploitation des blocs de padding**  
Les blocs de zéros en fin de mot de passe génèrent une relation particulière entre blocs chiffrés consécutifs :
$$ C_{i+1} = E(C_i) $$
L'opération $$ C_i \oplus C_{i+1} $$ révèle alors :
$$ C_i \oplus E(C_i) $$

**4. Détection du motif ASCII**  
J'analyse les paires de blocs chiffrés et filtre celles dont le XOR produit des caractères ASCII imprimables. Le motif le plus fréquent correspond au mot de passe, car :
- Les zéros du padding annulent l'impact de la clé dans le XOR
- La répétition du mot de passe augmente la fréquence de sa signature

## Validation de l'approche
| Étape                      | Résultat obtenu               |
|----------------------------|--------------------------------|
| Analyse statistique        | Identification du XOR dominant|
| Décodage ASCII             | Extraction des 4 caractères   |
| Vérification sur le flux   | Cohérence avec le chiffrement |

**Exemple technique** :  
Pour deux blocs consécutifs $$ C_a $$ et $$ C_b $$ :
```python
xor_bytes = bytes([a ^ b for a, b in zip(C_a, C_b)])
```
Si $$ C_b = E(C_a) $$, alors $$ xor\_bytes $$ correspond au mot de passe original.


### Partie 3
>Est-ce que cette attaque fonctionnerait aussi sur AES-CBC? Justifiez et soyez précis.

Cela ne fonctionne pas directement sur AES-CBC car:

#### 1. **Différence de taille de bloc**
- **Speck** : Bloc de **32 bits** → Collisions probables après $$2^{16}$$ blocs (paradoxe des anniversaires).
- **AES** : Bloc de **128 bits** → Collisions attendues après $$2^{64}$$ blocs, rendant les répétitions **improbables** en pratique.


#### 2. **Mécanisme CBC et dépendance contextuelle**
En CBC, chaque bloc chiffré $$C_i$$ dépend du précédent ($$C_{i-1}$$). Même avec un texte clair répétitif :
- Pour Speck (32 bits), la structure `[password][0000]` génère rapidement un cycle $$C_a, C_b$$ par saturation des combinaisons.
- Pour AES (128 bits), la probabilité de cycle est négligeable sans réutilisation d'IV ou de clé.


#### 3. **Conditions nécessaires pour une attaque similaire**
L'attaque sur Speck repose sur deux conditions :
1. **Texte clair périodique** avec une période courte (ex : 8 octets).
2. **Taille de bloc réduite** permettant des collisions rapides.

Avec AES-CBC :
- Une période de texte clair de **16 octets** (taille de bloc AES) serait nécessaire.
- Même dans ce cas, l'absence de collisions probables empêcherait la détection du motif.


---

####  **Preuve par simulation**
Supposons un texte clair répétitif `P = [secret][0000][secret][0000]...` :
- **AES-CBC** : Les blocs chiffrés $$C_i = \text{Encrypt}(P_i \oplus C_{i-1})$$ varient même si $$P_i$$ se répète, car $$C_{i-1}$$ change.
- **Speck-CBC** : La petite taille de bloc permet $$C_{i-1}$$ de boucler rapidement, annulant l'effet de propagation.



