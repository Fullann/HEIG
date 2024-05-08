# ASD2024-L5 : Liste simplement chaînée

Cet exercice vous demande de compléter la classe `ListeSimple` pour qu'elle passe le double 
codecheck [https://codecheck.io/files/24041912444be99k82r81c9sg5dw692cjey](https://codecheck.io/files/24041912444be99k82r81c9sg5dw692cjey). 

Le code source de cet exercice est disponible dans [src](./src), le résultat attendu dans [txt](./txt). Sauvez
le fichier .zip généré par codecheck dans [zips](./zips). 

Tout l'interface de la classe `ListeSimple` utilise des itérateurs dont la version variable (sous classe iterator
de ListeSimple<T>) vous est fournie et dont vous devez écrire la sous-classe const_iterator. 
Ces itérateurs stockent un pointeur privé vers un MaillonVide dans l'attribut `m`, qui est accessible depuis
    la classe `ListeSimple` qui en est amie.

Seules les fonctions `insert_after`, `erase_after` et `splice_after` manipulent directement les structures de maillon.
    Pour toutes les autres fonctions membres / constructeurs / destructeur il convient de n'utiliser que
des appels aux autres fonctions membres ou les itérateurs. 

Seule la fonction `insert_after` peut allouer de la mémoire. Seule la fonction `erase_after` peut libérer de la
mémoire. On utilise exclusivement l'allocation simple avec `new` et `delete`. 

Pour le tri, vous pouvez utiliser l'algorithme que vous voulez, y compris des tris simples comme le
tri à bulle ou le tri par sélection. Le tri modifie l'ordre des maillons de la liste en appelant
la fonction splice_after mais ne touche pas aux éléments stockés dans la liste. 

Faites attention de bien caractériser vos fonctions membres selon qu'elles sont `const` et / ou `noexcept` ou pas.
Pour celles qui ne sont pas `noexcept`, il convient d'offrir une garantie forte. 
