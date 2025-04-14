# Labo 02
## Ex1 - Spongy AES (1.5 pts)
### Partie 1
>Dessinez un schéma de la construction pour un message de 19 caractères ASCII. Soyez le plus précis possible concernant le “rate” et la taille de la sortie.

### Partie 2 
> Vous avez que le message a la forme suivante FLAG{...} avec 13 caractères entre les accolades.Vous trouverez dans votre fichier de paramètres le hash de ce message. Récupérez le message. Expliquez dans votre rapport comment vous avez procédé. Indice : vous aurez besoin de faire un peu de bruteforce. Vous savez aussi que le flag ne contient uniquement des caractères ASCII imprimables.

[SUCCESS] Flag found: FLAG{disengagement}

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