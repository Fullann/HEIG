# EX1 - Base64
## Donnée
Joe Tartempion propose d’utiliser l’algorithme Base64 comme chiffrement pour sécuriser
le stockage de données confidentielles traitées dans une application web en cours de développement.
1. Expliquer comment fonctionne l’algorithme Base64.
2. Base64 est-il un algorithme cryptographique ? Si oui, est-il considéré comme sûr en
2025 ? Si non, quel est son usage habituel ?
3. Décoder le texte suivant, qui a été encodé en Base64
```
RU5UUkUgbGVzIGF1dHJlcyBkb25zIGRlIGdyYWNlIHF1J2lsIGEgcGxldSDDo
CBEaWV1IGltcGFydGlyIMOgIGwnaG9tbWUsIHBvdXIgYXVjdW5lbWVudCBsZS
ByZWNvbXBlbnNlciBkZXMgbWlzZXJlcyBldCBwYXV2cmV0ZXogb8O5IGxhIHR
yYW5zZ3Jlc3Npb24gZGVzIHByZW1pZXJzIHBhcmVucyBsZSBmYWl0IG5haXN0
cmU7IGV0IGRlIHRhbnQgZGUgdHJhdmF1eCwgbWVzYWlzZXMsIGRhbmdlcnMsI
GluY29udmVuaWVucywgZXQgbWFsaGV1cnMgw6AgcXVveSBzYSBmcmFnaWxpdM
OpIGwnYWJhbmRvbm5lLCBlc3QgbCd1c2FnZSBkZSBsYSByYWlzb24sIGV0IGR
lIGxhIHBhcm9sZSwgcXVlIGxlcyBHcmVjcywgbm9uIHNhbnMgZ3JhbmQgbXlz
dGVyZSwgY29tcHJlbm5lbnQgc291cyBsZSBzZXVsIG1vdCBkZSBsb2dvczsgY
2UgZG9udCBwcmluY2lwYWxlbWVudCBpbCBkaWZmZXJlIGRlcyBiZXN0ZXMgYn
J1dGVzLCBhdmVjIGxlc3F1ZWxsZXMgaWwgcGFydGljaXBlIGQndW4gY29zdMO
pIGRlcyBmYWN1bHRleiBzZW5zaXRpdmVzIGRlIGwnYW1lOyBldCBkZSBsJ2F1
dHJlLCBkZXMgbmF0dXJlbGxlcyBhdmVjIGxlcyBhcmJyZXMgZXQgbGVzIHBsY
W50ZXMu
```
Expliquer la méthode complète qui vous a permis de retrouver le texte clair. De quel
texte historique est-ce un fragment ?

4. Finalement, que pensez-vous de la décision de Joe Tartempion ?

## Réponse 
1. Il est sur 6bits. Donc 2^6=64 bits => Base 64 
   
   - Un flux d'octets est divisé en deux groupes, chacun constitué de trois octets consécutifs. Chaque groupe (trois octets en séquence, chacun composé de huit bits) est converti en une série de quatre chiffres composés de six bits.
   -  les chiffres sont convertis en caractères ASCII à l'aide de la table d'encodage Base64.

2. Non il n'est plus sur en 2025.Il est utiliser dans les CTF 
   
3. ENTRE les autres dons de grace qu'il a pleu à Dieu impartir à l'homme, pour aucunement le recompenser des miseres et pauvretez où la transgression des premiers parens le fait naistre; et de tant de travaux, mesaises, dangers, inconveniens, et malheurs à quoy sa fragilité l'abandonne, est l'usage de la raison, et de la parole, que les Grecs, non sans grand mystere, comprennent sous le seul mot de logos; ce dont principalement il differe des bestes brutes, avec lesquelles il participe d'un costé des facultez sensitives de l'ame; et de l'autre, des naturelles avec les arbres et les plantes.

en me basant sur ce site https://www.base64decode.org/ j'ai pu dechiffrer le passage de la bible.

4. Que ce'est une mauvaise idée car on peut tres simplement dechiffrer des informations

# EX2 - Puissance Parfaite
## Donnée
Le but de cet exercice est principalement de se familiariser avec le langage de programmation Python qui sera utilisé pour les laboratoires. Soit c = a
b
, avec a, b et c tous des entiers
positifs.
1
1. Ecrire une fonction qui prend b et c en argument et qui retourne a sans utiliser une
fonction calculant la racine nième d’un nombre.
Indice :L’utilisation d’un algorithme de recherche binaire peut être utile.
2. Testez votre programme avec b = 4 et c = 2323057227982592441500937982514410000

## Réponse
```py
def find_root(b, c):    
    low, high = 1, c 
    
    while low <= high:
        mid = (low + high) // 2
        power = mid ** b
        
        if power == c:
            return mid
        elif power < c:
            low = mid + 1
        else:
            high = mid - 1
    
    return None 


b = 4
c = 2323057227982592441500937982514410000
a = find_root(b, c)
print(f"a = {a}")
```

# EX3 - Chiffre de César
## Donnée
1. À quel texte clair le texte chiffré suivant correspond-il ?
```
WRXWH ODJDX OHHVW GLYLV HHQWU RLVSD UWLHV GRQWO XQHHV WKDEL WHSDU
OHVEH OJHVO DXWUH SDUOH VDTXL WDLQV ODWUR LVLPH SDUFH XATXL GDQVO
HXUOD QJXHV HQRPP HQWFH OWHVH WGDQV ODQWU HJDXO RLVFH VQDWL RQVGL
IIUHQ WHQWU HHOOH VSDUO HODQJ DJHOH VLQVW LWXWL RQVHW OHVOR LVOHV
JDXOR LVVRQ WVSDU VGHVD TXLWD LQVSD UODJD URQQH GHVEH OJHVS DUODP
DUQHH WODVH LQHOH VEHOJ HVVRQ WOHVS OXVEU DYHVG HWRXV FHVSH XSOHV
SDUFH TXLOV UHVWH QWWRX WIDLW WUDQJ HUVOD SROLW HVVHH WODFL YLOLV
DWLRQ GHODS URYLQ FHURP DLQHH WTXHO HVPDU FKDQG VDOOD QWUDU HPHQW
FKHCH XAQHO HXUSR UWHQW SRLQW FHTXL FRQWU LEXHQ HUYHU OHFRX UDJHG
DLOOH XUVYR LVLQV GHVJH UPDLQ VTXLK DELWH QWDXG HOGXU KLQLO VVRQW
FRQWL QXHOO HPHQW HQJXH UUHDY HFHXA SDUOD PPHUD LVRQO HVKHO YWHVV
XUSDV VHQWD XVVLH QYDOH XUOHV DXWUH VJDXO RLVFD ULOVH QJDJH QWFRQ
WUHOH VJHUP DLQVG HVOXW WHVSU HVTXH MRXUQ DOLUH VVRLW TXLOV OHVUH
SRXVV HQWGH OHXUS URSUH WHUUL WRLUH VRLWT XLOVH QYDKL VVHQW FHOXL
GHOHX UVHQQ HPLVO HSDBV KDELW FRPPH QRXVO DYRQV GLWSD UOHVJ DXORL
VFRPP HQFHD XUKQH HWHVW ERUQS DUODJ DURQQ HORFD QHWOH VIURQ WLUHV
GHVEH OJHVG XFWGH VVTXD QHVHW GHVKH OYWHV LOYDM XVTXD XUKLQ LOHVW
VLWXD XQRUG FHOXL GHVEH OJHVF RPPHQ FHOHA WUPHI URQWL UHGHO DJDXO
HHWHV WERUQ SDUOD SDUWL HLQIU LHXUH GXUKL QLOUH JDUGH OHQRU GHWOR
ULHQW ODTXL WDLQH VWHQG GHODJ DURQQ HDXAS BUQHV HWFHW WHSDU WLHGH
ORFDQ TXLED LJQHO HVFWH VGHVS DJQHH OOHHV WHQWU HOHFR XFKDQ WHWOH
QRUG
```
De quel texte historique est-ce un fragment ?

2. On décide d’utiliser le chiffre de César avec un nombre secret de décalages. À quel texte
clair le texte chiffré suivant correspond-il ?
```
ZOQFM DHCQS GHFWU CZC
```

## Réponse
Code :
```py
import string

def caesar_decrypt(ciphertext):
    """
    Décrypte un texte chiffré par César en testant tous les décalages possibles.
    """
    alphabet = string.ascii_lowercase
    results = []
    
    for shift in range(26):
        decrypted_text = "".join(
            alphabet[(alphabet.index(c) - shift) % 26] if c in alphabet else c
            for c in ciphertext.lower()
        )
        results.append((shift, decrypted_text))
    
    return results

def detect_text(text):
    """
    Vérifie si un texte contient des mots en français.
    """
    common_words = {"le", "la", "les", "un", "une", "et", "est", "je", "tu", "il", "elle", "nous", "vous", "ils", "elles", "the",}
    words = set(text.split())
    return len(words & common_words) > 1

# Exemple d'utilisation
ciphertext = "wklv lv d whvwhg whaw"
decryptions = caesar_decrypt(ciphertext)

for shift, text in decryptions:
    if detect_text(text):
        print(f"Décalage {shift}: {text}")

```
Question 1
```
TOUTE LAGAU LEEST DIVIS EENTR OISPA RTIES DONTL UNEES THABI TEPAR
LESBE LGESL AUTRE PARLE SAQUI TAINS LATRO ISIME PARCE UXQUI DANSL
EURLA NGUES ENOMM ENTCE LTESE TDANS LANTR EGAUL OISCE SNATI ONSDI
FFREN TENTR EELLE SPARL ELANG AGELE SINST ITUTI ONSET LESLO ISLES
GAULO ISSON TSPAR SDESA QUITA INSPA RLAGA RONNE DESBE LGESP ARLAM
ARNEE TLASE INELE SBELG ESSON TLESP LUSBR AVESD ETOUS CESPE UPLES
PARCE QUILS RESTE NTTOU TFAIT TRANG ERSLA POLIT ESSEE TLACI VILIS
ATION DELAP ROVIN CEROM AINEE TQUEL ESMAR CHAND SALLA NTRAR EMENT
CHEZE UXNEL EURPO RTENT POINT CEQUI CONTR IBUEN ERVER LECOU RAGED
AILLE URSVO ISINS DESGE RMAIN SQUIH ABITE NTAUD ELDUR HINIL SSONT
CONTI NUELL EMENT ENGUE RREAV ECEUX PARLA MMERA ISONL ESHEL VTESS
URPAS SENTA USSIE NVALE URLES AUTRE SGAUL OISCA RILSE NGAGE NTCON
TRELE SGERM AINSD ESLUT TESPR ESQUE JOURN ALIRE SSOIT QUILS LESRE
POUSS ENTDE LEURP ROPRE TERRI TOIRE SOITQ UILSE NVAHI SSENT CELUI
DELEU RSENN EMISL EPAYS HABIT COMME NOUSL AVONS DITPA RLESG AULOI
SCOMM ENCEA URHNE ETEST BORNP ARLAG ARONN ELOCA NETLE SFRON TIRES
DESBE LGESD UCTDE SSQUA NESET DESHE LVTES ILVAJ USQUA URHIN ILEST
SITUA UNORD CELUI DESBE LGESC OMMEN CELEX TRMEF RONTI REDEL AGAUL
EETES TBORN 
```
De astérix et obélix l introduction des bd

Question 2
```
LACRY PTOCE STRIG OLO
```

# EX4 -  ROT13
## Donnée
1. L’algorithme ROT13 est parfois utilisé dans certains forums sur Internet. Expliquer son
fonctionnement.
2. À quel texte clair le texte chiffré suivant correspond-il ?
V nz n unpxre, naq guvf vf zl znavsrfgb.
Lbh znl fgbc guvf vaqvivqhny, ohg lbh pna’g
fgbc hf nyy... nsgre nyy, jr’er nyy nyvxr.
De quel texte historique est-ce un fragment ?
3. Quelle est la sécurité de ROT13 ? Dans quel but est-il utilisé sur Internet ?
## Réponse
1. Il s'agit du meme fonctionnement que cesart mise a part que la clé est définie à 13 ce qui permet au chiffre d'être réversible
2. Du film Hackers
```
I am a hacker, and this is my manifesto.
You may stop this individual, but you can’t
stop us all... after all, we’re all alike.
```
3. N'est pas dutout sécuriser car juste equivalent a cesar mais en plus on connais la cles

# EX5 - Adversaire Passif/Actif
## Donnée
On chiffre un message m de k bits de la manière suivante :
1. On tire une clef aléatoire K de k bits.
2. On effectue un XOR bit par bit du message avec la clef pour obtenir le chiffré.
   
Questions :
1. Quel est le nom de ce système de chiffrement ?
2. Quelle est la sécurité de ce système contre un adversaire passif ? Pourquoi (une justification informelle suffit) ?
3. Quelle est la sécurité de ce système contre un adversaire actif ? Pourquoi ?
## Réponse
1. Nom : One-Time Pad (OTP).
2. Sécurité contre un adversaire passif : Parfaitement sécurisé si la clé est aléatoire, de même longueur que le message et jamais réutilisée.
3. Sécurité contre un adversaire actif : Vulnérable aux modifications du chiffré et aux attaques si la clé est réutilisée.

# EX6 -  Chiffrement Inconnu
## Donnée
Les services de renseignement d’un pays lointain ont intercepté ce message chiffré :
```
VVVDA AGVVG VVDAA GXXFF FVVAG VAVFF VVAGG
VDVVV XAXDX DVVVA AXVXV XVGDF VFAFX VGFFV AX
```
Par chance, ils disposent également de l’information suivante, volée astucieusement par l’agente
```
Nata Marrie :
Grid: a1b2c3d4e5f6g7h8i9j0klmnopqrstuvwxyz
Key: LARS Perm: 2,1,3,4
```
- Êtes-vous capable de décrypter ce texte ? Si oui, dans quel contexte cette phrase célèbre
a-t-elle été prononcée ?

Indice : Quels sont les seules lettres utilisées dans le chiffré ? Pensez à effectuer une recherche
dans votre moteur de recherche favori

## Réponse
### Analyse du message
Le message intercepté est le suivant : 
```
VVVDA AGVVG VVDAA GXXFF FVVAG VAVFF VVAGG VDVVV XAXDX DVVVA AXVXV XVGDF VFAFX VGFFV AX
```

Il utilise uniquement les lettres **A, V, G, D, X, F**.  
Cela correspond au **chiffrement ADFGVX**, un système utilisé par l'armée allemande en 1918.  
Ce chiffrement fonctionne en **deux étapes** :  
1. **Substitution** : Chaque lettre est remplacée par une combinaison de deux lettres parmi ADFGVX, selon une grille.  
2. **Transposition** : Les groupes de lettres sont mélangés selon une clé.  

### Utilisation de la grille de substitution
La grille donnée dans l’énoncé est :  

```
a1b2c3d4e5f6g7h8i9j0klmnopqrstuvwxyz
```

Cela suggère que les lettres et chiffres sont placés dans une table 6x6.  
Chaque lettre chiffrée représente une position dans cette table.

### Application de la clé "LARS" et de la permutation (2,1,3,4)
La clé "LARS" est utilisée pour **ordonner les colonnes de la grille lors de la transposition**.  
L'indication "Perm: 2,1,3,4" signifie que les colonnes ont été mélangées dans cet ordre.  
On doit donc **inverser cette permutation** pour retrouver le texte clair.

### Décodage et interprétation
Après déchiffrement avec ces étapes, on obtient une phrase célèbre :  

> **"IF IT IS PROVABLY SECURE IT IS PROBABLY NOTZ"**
