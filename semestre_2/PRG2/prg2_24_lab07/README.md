# PRG2 L7 - Manipulations de fichiers

Le but de ce laboratoire est d'entraîner la manipulation de fichiers au travers d'opérations sur des images au format `.bmp`.
Vous aurez aussi l'occasion de faire appel à la clause `goto` pour gérer les erreurs.
## groupe
- Nathan Füllemann 
- Maxime Regenass

## Introduction

Le format `.bmp` (ou windows bitmap) est un format permettant de stocker des images de manière simple, mais peu optimisée.

Les données sont stockées sous la forme d'un header qui contient de nombreuses informations sur le contenu du fichier, puis les datas des pixels.

La première étape à réaliser sera donc de lire le header des fichiers fournis en entrée de vos programmes et d'en tirer toutes les informations dont vous aurez besoin. Il y'a beaucoup d'informations dans ces headers et elles ne vous seront pas forcément toutes utiles, à vous de juger lesquelles utiliser ou non. Gardez tout de même en tête qu'à l'écriture de votre image de sortie, vous devrez commencer par écrire un header entier (qui peut être le même que celui de l'une des images d'entrée).

Le contenu du header est le suivant (l'ordre est important).

```c
uint16_t magic; // Nombre MAGIC
uint32_t fileSize; // Taille totale du fichier
uint16_t reserved1; // Réservé (0)
uint16_t reserved2; // Réservé (0)
uint32_t dataOffset; // Offset des données de l'image
uint32_t headerSize; // Taille de l'en-tête du fichier
int32_t width; // Largeur de l'image
int32_t height; // Hauteur de l'image
uint16_t planes; // Nombre de plans (toujours 1)
uint16_t bpp; // Bits par pixel (24 bits dans notre cas)
uint32_t compression; // Méthode de compression (0 pour non compressé)
uint32_t imageSize; // Taille de l'image (sans en-tête)
int32_t xResolution; // Résolution horizontale (en pixels par mètre)
int32_t yResolution; // Résolution verticale (en pixels par mètre)
uint32_t colorsUsed; // Nombre de couleurs utilisées dans l'image (0 pour toutes)
uint32_t importantColors; // Nombre de couleurs importantes (0 pour toutes)
```

Note: Le champ `MAGIC` n'est pas un nom que nous avons choisi au hasard, il existe réellement. Il est présent dans la plupart des headers de fichiers et comporte une valeur pour chaque format de fichier. Les fichiers `.bmp`, par exemple, ont tous le même magic qui vaut `0x4D42`, cela permet d'aisément s'assurer que le fichier ouvert est un fichier `.bmp`.

Les pixels, quant à eux, sont stockés par groupe de trois valeurs sur 8 bits, d'abord le bleu, puis le vert et enfin le rouge. L'ordre est important et les pixels sont stockés à la suite.

## Structure du laboratoire

Ce laboratoire est constitué de trois exercices. Dans chacun de ces exercices, vous allez devoir accéder à des fichiers au format `.bmp`, lire leurs headers, leur datas, réaliser des opérations, puis créer un nouveau fichier de sortie. Une partie conséquente du code sera donc réutilisable entre les exercices. Les fichiers `bmp.h` et `bmp.c` sont donc à utiliser pour mettre en place toutes les parties communes aux trois exercices.

Concernant la gestion d'erreur, vous constaterez rapidement que beaucoup de fonctions peuvent en retourner. Afin d'éviter de libérer la mémoire ou de fermer les fichiers de manière répétitive, utilisez la clause `goto` pour terminer l'exécution de vos programmes correctement.

## Exercice 1 : Comparaison de deux images et calcul de la différence

Dans ce premier exercice, vous aller devoir réaliser un programme permettant de comparer une image avec une image de référence. Une nouvelle image sera alors générée. Celle-ci est une simple copie de l'image à comparer, sauf pour les pixels qui sont différents entre les deux images d'entrée, qui seront remplacés par des pixels rouges.

Le programme doit prendre en argument trois chemins vers les fichiers des images, dans l'ordre suivant : fichier à comparer, fichier de référence et fichier de sortie.

A la fin de la comparaison, un message doit également s'afficher afin d'informer l'utilisateur du résultat de la comparaison (images différentes ou non).

Dans les images mises à votre disposition, vous trouverez un répertoire nommé `img/compare` dans lequel se trouvent deux images: `ref.bmp` qui est l'image de référence et `input.bmp` qui est la même image, mais avec une ligne sur deux dont les pixels ont été remplacés par des pixels noirs.

Avec ces deux images, vous devriez donc obtenir une image résultante avec une ligne sur deux avec des pixels rouges et une ligne sur deux avec l'image de base.

## Exercice 2 : Conversion en noir et blanc

Dans ce second exercice, vous allez devoir réaliser un programme qui va convertir une image en noir et blanc.

Le programme doit prendre en argument deux chemins d'accès vers des images : l'image à convertir en entrée et l'image à générer en sortie.

L'algorithme pour la conversion est très simple à mettre en place. Pour chaque pixel, vous devez prendre la moyenne des trois valeurs (rouge, vert et bleu) et mettre cette moyenne dans les trois valeurs du pixel de destination. La formule de conversion est donc la suivante:

$$  R_o = G_o = B_o = (R_i + G_i + B_i) / 3$$

Deux images ont été mises à votre disposition pour cet exercice dans le répertoire `img/gray`: Une image `input.bmp` à passer en entrée de votre programme et une image `expected_bw.bmp` qui correspond à l'image noir et blanc attendue.

Cette deuxième image vous permet donc, à l'aide du programme de l'exercice 1, de vérifier que votre conversion en noir et blanc fonctionne correctement.

## Exercice 3 : Filtre de bruit

Pour ce dernier exercice, une image `input.bmp` vous a été fournie dans le répertoire `img/pepper`, celle-ci est une reprise de l'image en noir et blanc générée à l'exercice 2, mais sur laquelle nous avons ajouté un bruit "poivre et sel".

Le principe du bruit poivre et sel est qu'un certains nombre de pixels aléatoires ont été rendus blanc ou noirs dans l'image.

Vous allez donc devoir implémenter un programme permettant de filtrer ce bruit. Pour filtrer celui-ci, vous allez utiliser l'algorithme du filtre médian. Cet algorithme est le suivant:

* Pour chaque pixel, récupérer les 8 pixels voisins ainsi que le pixel lui même.
* Enregistrer les 9 valeurs dans un tableau et les trier dans l'ordre croissant.
* Une fois le tri effectué, prendre la valeur médianne du tableau.
* Enregistrer cette valeur comme nouvelle valeur pour le pixel traité.

Par exemple, si on considère ces neuf pixels, dont une valeur aberrante (ici 255):

<div align="center">
<table border="1px solid black">
<tbody>
  <tr>
    <td align="center" width="20px">5</td>
    <td align="center" width="20px">6</td>
    <td align="center" width="20px">7</td>
  </tr>
  <tr>
    <td align="center" width="20px">6</td>
    <td align="center" width="20px">255</td>
    <td align="center" width="20px">8</td>
  </tr>
  <tr>
    <td align="center" width="20px">7</td>
    <td align="center" width="20px">8</td>
    <td align="center" width="20px">9</td>
  </tr>
</tbody>
</table>
</div>

Le filtre médian va considérer les valeurs du voisinage:

<div align="center">
<table border="1px solid black">
<tbody>
  <tr>
    <td align="center" width="20px">5</td>
    <td align="center" width="20px">6</td>
    <td align="center" width="20px">7</td>
    <td align="center" width="20px">6</td>
    <td align="center" width="20px">255</td>
    <td align="center" width="20px">8</td>
    <td align="center" width="20px">7</td>
    <td align="center" width="20px">8</td>
    <td align="center" width="20px">9</td>
  </tr>
</tbody>
</table>
</div>

Puis, il va trier dans l'ordre croissant les différentes valeurs:

<div align="center">
<table border="1px solid black">
<tbody>
  <tr>
    <td align="center" width="20px">5</td>
    <td align="center" width="20px">6</td>
    <td align="center" width="20px">6</td>
    <td align="center" width="20px">7</td>
    <td align="center" width="20px">7</td>
    <td align="center" width="20px">8</td>
    <td align="center" width="20px">8</td>
    <td align="center" width="20px">9</td>
    <td align="center" width="20px">255</td>
  </tr>
</tbody>
</table>
</div>

Et prendre la valeur médiane, ici la valeur `7`. La sortie du filtre donnera donc :

<div align="center">
<table border="1px solid black">
<tbody>
  <tr>
    <td align="center" width="20px">5</td>
    <td align="center" width="20px">6</td>
    <td align="center" width="20px">7</td>
  </tr>
  <tr>
    <td align="center" width="20px">6</td>
    <td align="center" width="20px">7</td>
    <td align="center" width="20px">8</td>
  </tr>
  <tr>
    <td align="center" width="20px">7</td>
    <td align="center" width="20px">8</td>
    <td align="center" width="20px">9</td>
  </tr>
</tbody>
</table>
</div>

Ce qui a permis de remplacer la valeur aberrante par une valeur « de consensus » entre les valeurs voisines.

Les pixels se trouvant dans les bords de l'image ne sont pas à traiter. Ils n'ont pas été affectés par le bruit poivre et sel. Ils peuvent simplement être copié dans l'image de sortie

Important: pour trier les valeurs, vous devez utiliser un tri à bulles que vous aurez réalisé à la main.

Le fichier d'origine étant en noir et blanc, les trois composantes de chaque pixel auront la même valeur, il vous suffit donc de réaliser votre algorithme sur une seule de ces composantes, mais n'oubliez pas de les écrire toutes les trois!

Nous vous avons également mis à disposition une image `expected_pepper.bmp` afin d'y comparer votre image de sortie.
