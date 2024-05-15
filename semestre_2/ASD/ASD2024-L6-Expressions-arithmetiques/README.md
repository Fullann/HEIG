# Evaluation d'expressions

Le but de ce laboratoire est d'évaluer des expressions arithmétiques avec 3 approches  

* une approche récursive
* l'algorithme de Dijkstra à 2 piles vu au cours
* la construction d'un arbre binaire explicite représentant cette expression. 

Ces 3 approches sont testées via 3 codechecks 

* Récursif : [https://codecheck.io/files/2404261241ll5prqupxv5u7k91l77gn1b1](https://codecheck.io/files/2404261241ll5prqupxv5u7k91l77gn1b1)
* Piles : [https://codecheck.io/files/24042612425qskh17jvj3pvo4irbvpwy23j](https://codecheck.io/files/24042612425qskh17jvj3pvo4irbvpwy23j)
* Arbre : [https://codecheck.io/files/24042612424e1gt90tdfn6qa5n9axdd99g4](https://codecheck.io/files/24042612424e1gt90tdfn6qa5n9axdd99g4)

Le code de ces codechecks est disponible dans [src](./src). Les expressions testées sont disponibles 
en commentaire des fichiers main.cpp et les sorties attendues sont disponibles 
dans le répertoire [outputs](./outputs). Les résultats de vos codechecks doivent être sauvés dans le répertoire [zips](./zips).

Pour information, les solutions "officielles" utilisent les éléments suivants de la STL, mais vous n'êtes pas obligés de 
faire de même. 

* [std::stack](http://www.cplusplus.com/reference/stack/stack/)
* [std::string](http://www.cplusplus.com/reference/string/)
    * [string::find](http://www.cplusplus.com/reference/string/string/find/)
* [&lt;cctype&gt;](http://www.cplusplus.com/reference/cctype/)
    * [isblank](http://www.cplusplus.com/reference/cctype/isblank/)
    * [isdigit](http://www.cplusplus.com/reference/cctype/isdigit/)
* [std::istringstream](http://www.cplusplus.com/reference/sstream/istringstream/)
    * [istream::get](http://www.cplusplus.com/reference/istream/istream/get/)
    * [istream::putback](http://www.cplusplus.com/reference/istream/istream/putback/)
