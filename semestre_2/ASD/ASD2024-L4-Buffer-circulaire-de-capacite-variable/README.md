# ASD2024-L4 Buffer circulaire de capacité variable
## Equipe 
Groupe 4
- Maxime Regenass
- Nathan Füllemann
## Description
Le but de ce laboratoire est de mettre en oeuvre un buffer circulaire de capacité variable sous la forme d'une classe générique ArrayDeque<T>

Pour tester cette classe, nous vous fournissons 4 codechecks de difficulté croissante. Notez cependant qu'il s'agit ici d'un seul exercice, le même code final devant être capable de passer les 4 codechecks.  

* [Buffer Circulaire (A)](https://codecheck.io/files/2304190927dre4qi4nm4rck8d0aysa5k19x) spécifie la capacité 
  du buffer à la construction, et il n'est donc pas nécessaire d'avoir codé l'augmentation de capacité pour le 
  passer. 
* [Buffer Circulaire (B)](https://codecheck.io/files/230419094189mnnu2oo8gylwfso0yfv1a4v)
  reprend le même test mais en stockant des objets d'une classe C qui affiche quels constructeurs, 
  `operator=` et destructeurs sont appelés. Allocation de la mémoire et construction des 
  éléments sont faites séparément, de même que destruction et libération. Pour rappel, 
    * il faut réserver la mémoire nécessaire pour stocker `capacité` éléments avec `operator new`
    * quand on écrit dans un emplacement mémoire actuellement non utilisé, il faut construire l'élément avec le `new` en place. 
    * quand on écrit dans un emplacement mémoire actuellement utilisé, il faut affecter avec l'opérateur `=`. 
    * quand on n'utilise plus un emplacement mémoire, il faut détruire l'élément qui s'y trouvait en appelant `std::destroy_at` ou les destructeur si l'on utilise un C++ antérieur à C++17.
    * quand on n'utilise plus de mémoire, il faut la libérer avec `operator delete`.
* [Buffer Circulaire (C)](https://codecheck.io/files/23041909408un8f812mkkntod3lxsyvyifr) 
  modifie le test en commençant avec un buffer de capacité nulle. Ensuite, il utilise 
  la stratégie de doublement si nécessaire vue au cours pour augmenter au fur et à mesure 
  la capacité. Il ajoute également une nouvelle méthode: `shrink_to_fit`, qui doit se 
  comporter comme celle de `std::vector`.
* [Buffer Circulaire (D)](https://codecheck.io/files/2304190922269na4wfdq2h3632mno34pp0j)
  reprend tout d'abord le même test mais en stockant des objets qui affichent quels 
  constructeurs, `operator=` et destructeurs sont appelés. Ensuite, il vérifie les 
  garanties offertes par les différentes méthodes et par le constructeur de copie 
  quand la copie de certains éléments lève des exceptions. Toutes les méthodes doivent 
  offrir des garanties fortes et le constructeur de copie la garantie faible. 

Le code de ces 4 codechecks est disponible dans le répertoire [src](./src). Modifiez uniquement le fichier [ArrayDeque.h](./src/ArrayDeque.h). La sortie attendue de chacun des ces tests est disponible dans le répertoire [txt](./txt). 

Sauvegardez les fichiers zip générés par codecheck dans le répertoire [zips](./zips).

Pour vous aider, vous pouvez voir ou revoir les capsules vidéos suivantes, issues du cours d'ASD1 de 2020 : 

* [4.2 - Tableaux de taille fixe](https://tinyurl.com/yc88dntx) pour la gestion des garanties
  en cas d'exception
* [4.4 - Buffer circulaire](https://tinyurl.com/y9fb3bmm) pour le type de donnée buffer circulaire,
  mais présenté avec une capacité fixe
* [4.5 - Tableaux de capacité variable](https://tinyurl.com/yctdn646) pour la gestion de la 
capacité variable

Nous vous recommandons de commencer par effectuer les exercices 4.4 à 4.6 du recueil d'exercices avant de vous lancer dans ce laboratoire. 