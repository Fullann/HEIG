1. **Avantage du χ² :**  
   Il compare l’ensemble des fréquences de lettres, offrant une mesure globale et robuste, contrairement à une simple comparaison de la lettre la plus fréquente.

2. **Limitation sur Vigenère :**  
   Le chiffrement Vigenère utilise plusieurs décalages, ce qui mélange les fréquences et masque la distribution typique du langage.

3. **Indice de coïncidence :**  
   Il mesure la probabilité que deux lettres choisies au hasard soient identiques, reflétant la redondance du texte.

4. **Invariance avec César généralisé :**  
   Ce chiffre ne fait qu’un décalage constant, conservant les fréquences relatives des lettres et donc l’indice inchangé.

5. **Clé de même taille (one-time pad) :**  
   Un document chiffré avec une clé de la même taille, si la clé est aléatoire et utilisée une seule fois, est théoriquement inviolable sans la clé.

6. **Attaque sur Vigenère amélioré :**  
   On récupère la clé initiale en ciblant le premier bloc (chiffré avec la clé non modifiée) via une analyse fréquentielle/χ², puis on met à jour la clé pour déchiffrer les blocs suivants.

7. **Distinguer anglais/français :**  
   On calcule le χ² entre les fréquences du texte et celles de référence pour chaque langue. Le texte est attribué à la langue présentant le χ² le plus faible. Les tests montrent une grande précision avec des textes suffisamment longs.

8. **Clef et texte en clairs**
   1. Clé retrouvée : ASTERIXOBELIX
   2. Texte déchiffré VOUSSAVEZMOIJENECROISPASQUILYAITDEBONNEOUDEMAUVAISESITUATIONMOISIJEDEVAISRESUMERMAVIEAUJOURDHUIAVECVOUSJEDIRAISQUECESTDABORDDESRENCONTRESDESGENSQUIMONTTENDULAMAINPEUTETREAUNMOMENTOUJENEPOUVAISPASOUJETAISSEULCHEZMOIETCESTASSEZCURIEUXDESEDIREQUELESHASARDSLESRENCONTRESFORGENTUNEDESTINEEPARCEQUEQUANDONALEGOUTDELACHOSEQUANDONALEGOUTDELACHOSEBIENFAITELEBEAUGESTEPARFOISONNETROUVEPASLINTERLOCUTEURENFACEJEDIRAISLEMIROIRQUIVOUSAIDEAAVANCERALORSCANESTPASMONCASCOMMEJEDISAISLAPUISQUEMOIAUCONTRAIREJAIPUETJEDISMERCIALAVIEJELUIDISMERCIJECHANTELAVIEJEDANSELAVIEJENESUISQUAMOURETFINALEMENTQUANDDESGENSMEDISENTMAISCOMMENTFAISTUPOURAVOIRCETTEHUMANITEJELEURREPONDSTRESSIMPLEMENTQUECESTCEGOUTDELAMOURCEGOUTDONCQUIMAPOUSSEAUJOURDHUIAENTREPRENDREUNECONSTRUCTIONMECANIQUEMAISDEMAINQUISAITPEUTETRESIMPLEMENTAMEMETTREAUSERVICEDELACOMMUNAUTEAFAIRELEDONLEDONDESOI
9. 