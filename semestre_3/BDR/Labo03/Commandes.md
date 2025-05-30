# Rapport BDR labo03
## Partie 1
1. Les frais moyens d'inscription des événements organisés par la fédération 'BRITISH
GYMNASTICS'.
```sql
SELECT AVG(Evenement.fraisInscription) AS frais_moyens
FROM Evenement
JOIN Federation ON Evenement.idFederation = Federation.id
WHERE Federation.nom = 'BRITISH GYMNASTICS';
```

Résultat:

![Résultat](./CapturesEcran/1.png)

2. Les gymnastes qui pratiquent la discipline dont leur entraineur est le spécialiste et qui
sont originaires du même pays.
```sql
SELECT g.idPersonne AS idGymnaste, pg.nom, pg.prenom
FROM Gymnaste g
JOIN Coach c ON g.idCoach = c.idPersonne
JOIN Personne pg ON g.idPersonne = pg.id
JOIN Personne pc ON c.idPersonne = pc.id
JOIN Gymnaste_Discipline gd ON g.idPersonne = gd.idGymnaste
WHERE gd.codeDiscipline = c.codeDiscipline
    AND pg.idPays = pc.idPays
```

Résultat:

![Résultat](./CapturesEcran/2.png)

3. Les coachs nés entre 1981 et 1996 (années comprises) qui entrainent au moins un
gymnaste plus âgé qu'eux.
```sql
SELECT DISTINCT c.idPersonne AS idCoach, pc.nom AS nomCoach, pc.prenom AS prenomCoach
FROM Coach c
JOIN Gymnaste g ON g.idCoach = c.idPersonne
JOIN Personne pg ON g.idPersonne = pg.id
JOIN Personne pc ON c.idPersonne = pc.id
WHERE pc.dateNaissance BETWEEN '1981-01-01' AND '1996-12-31'
    AND EXISTS (SELECT g.idPersonne FROM Gymnaste WHERE pc.dateNaissance > pg.dateNaissance)
```

Résultat:

![Résultat](./CapturesEcran/3.png)

4. Les coachs qui entrainent plus de 2 gymnastes qui se sont inscrits à au moins 1
événement.
```sql
SELECT c.idPersonne AS idCoach, pc.nom AS nomCoach, pc.prenom AS prenomCoach, COUNT(DISTINCT g.idPersonne) AS nombreGymnastes
FROM Coach c
JOIN Gymnaste g ON g.idCoach = c.idPersonne
JOIN Personne pc ON c.idPersonne = pc.id
JOIN Inscription i ON g.idPersonne = i.idGymnaste
GROUP BY c.idPersonne, pc.nom, pc.prenom
HAVING COUNT(DISTINCT g.idPersonne) > 2;
```

Résultat:

![Résultat](./CapturesEcran/4.png)

5. Pour les gymnastes ayant participé à au moins 2 événements, indiquer l’écart entre les
frais d’inscription les moins élevés et les plus élevés payés. Classer les résultats par ordre
alphabétique croissant du nom, puis du prénom des gymnastes.
```sql
SELECT g.idPersonne AS idGymnaste, p.nom AS nomGymnaste, p.prenom AS prenomGymnaste, MAX(e.fraisInscription) - MIN(e.fraisInscription) AS differenceFrais
FROM Gymnaste g
JOIN Inscription i ON g.idPersonne = i.idgymnaste 
JOIN Personne p ON g.idPersonne = p.id
JOIN evenement e ON i.idevenement = e.id
GROUP BY g.idPersonne, p.nom, p.prenom
HAVING COUNT(DISTINCT i.idEvenement) >= 2
ORDER BY p.nom ASC, p.prenom ASC;
```

Résultat:

![Résultat](./CapturesEcran/5.png)

6. Indiquer (gymnaste + événement avec sa date d’ouverture + nombre de jours de retard)
toutes les inscriptions faites après la date d’ouverture d'un événement.
```sql
SELECT g.idPersonne AS idGymnaste, 
       p.nom AS nomGymnaste, 
       p.prenom AS prenomGymnaste, 
       e.nom AS nomEvenement, 
       TO_CHAR(e.dateOuverture, 'DD.MM.YYYY') AS dateEvenement,
       TO_CHAR(i.date, 'DD.MM.YYYY') AS dateInscription,
       (i.date - e.dateOuverture) AS joursDifference
FROM Gymnaste g
JOIN Inscription i ON g.idPersonne = i.idgymnaste
JOIN Personne p ON g.idPersonne = p.id
JOIN evenement e ON i.idevenement = e.id
WHERE i.date > e.dateOuverture;
```
``` TO_CHAR(e.dateOuverture, 'DD.MM.YYYY') ``` permet d'écrire la date sous la forme ``` jj.mm.aaaa ```.

Résultat:

![Résultat](./CapturesEcran/6.png)

7. Par événement, lister tous les gymnastes inscrits en les classant par date d'inscription à
l'événement (de la plus ancienne à la plus récente).
```sql
SELECT e.nom AS nomEvenement, 
       TO_CHAR(e.dateOuverture, 'DD.MM.YYYY') AS dateEvenement,
       p.id AS idGymnaste,
       p.nom AS nomGymnaste, 
       p.prenom AS prenomGymnaste,
       TO_CHAR(i.date, 'DD.MM.YYYY') AS dateInscription
FROM evenement e
JOIN inscription i ON e.id = i.idevenement
JOIN gymnaste g ON i.idgymnaste = g.idPersonne
JOIN personne p ON g.idPersonne = p.id
ORDER BY e.nom, i.date, p.nom, p.prenom;
```

Résultat:

![Résultat](./CapturesEcran/7.png)

8. En partant du principe que les coachs payent les frais d'inscription aux événements de
leurs gymnastes qui y participent en tant que juniors (moins de 16 ans au début de
l'événement), classer les coachs par le montant total des frais d’inscriptions qu'ils ont payé
(ordre décroissant) puis par ordre alphabétique de leur nom.
```sql
SELECT pc.id AS idCoach,
       pc.nom AS nomCoach, 
       pc.prenom AS prenomCoach,
       SUM(e.fraisInscription) AS totalPrix
FROM Coach c
JOIN Gymnaste g ON g.idCoach = c.idPersonne
JOIN Inscription i ON g.idPersonne = i.idgymnaste
JOIN evenement e ON i.idevenement = e.id
JOIN Personne pc ON c.idPersonne = pc.id
JOIN Personne p ON g.idPersonne = p.id
WHERE EXTRACT(YEAR FROM AGE(e.dateOuverture, p.dateNaissance)) < 16
GROUP BY pc.id, pc.nom, pc.prenom
ORDER BY totalPrix desc, pc.nom ASC, pc.prenom ASC;
```
``` EXTRACT(YEAR FROM AGE(e.dateOuverture, p.dateNaissance)) ``` permet d'avoir le nombre d'années entre 2 dates.

Résultat:

![Résultat](./CapturesEcran/8.png)

9. Par fédération qui a au moins 1 membre, indiquer le nombre de membres qui sont
originaires de son pays et le nombre qui sont originaires d'un autre pays.
```sql
SELECT f.nom AS federation,
       pf.nom AS paysFederation,
       SUM(CASE WHEN p.idPays = f.idPays THEN 1 ELSE 0 END) AS gymnastesMemePays,
       SUM(CASE WHEN p.idPays != f.idPays THEN 1 ELSE 0 END) AS gymnastesAutrePays
FROM Federation f
JOIN Gymnaste g ON f.id = g.idFederation
JOIN Personne p ON g.idPersonne = p.id
JOIN Pays pf ON f.idPays = pf.id
GROUP BY f.nom, pf.nom
ORDER BY f.nom;
```
``` CASE WHEN p.idPays = f.idPays THEN 1 ELSE 0 END ``` permet d'ajouter 1 au "compteur" si la condition est remplie. Ici si le pays du gymnaste est le même que celui de la fédération.

Résultat:

![Résultat](./CapturesEcran/9.png)

10. Pour chaque gymnaste, indiquer le nombre d'événements auxquels il est inscrit et qui
n'ont pas encore commencé.
```sql
SELECT g.idPersonne AS idGymnaste,
       p.nom AS nomGymnaste,
       p.prenom AS prenomGymnaste,
       COALESCE(COUNT(e.id), 0) AS nombreEvenementsAVenir
FROM Gymnaste g
JOIN Personne p ON g.idPersonne = p.id
LEFT JOIN Inscription i ON g.idPersonne = i.idgymnaste
LEFT JOIN evenement e ON i.idevenement = e.id AND e.dateOuverture > CURRENT_DATE
GROUP BY g.idPersonne, p.nom, p.prenom
ORDER BY p.nom, p.prenom;
```
``` COALESCE(COUNT(e.id), 0) ``` remplace les NULL générés par l'absence d'événements par 0.

``` LEFT JOIN ``` assure que tous les gymnastes sont inclus, même s'ils n'ont pas d'inscription.

Résultat:

![Résultat](./CapturesEcran/10.png)

11. Pour l’événement 'TRA RGI World Cup 2022', lister toutes les inscriptions (gymnastes +
frais réels).
Pour calculer les frais réels, on prend les frais d’inscription en tenant compte de 2 règles :
- On les double pour toute inscription hors délai (après l’ouverture de l’événement).
- Les gymnastes membres de la fédération qui organise l’événement ont un rabais de
20%.
```sql
SELECT e.nom AS nomEvenement,
       f.nom as organisateur,
       g.idPersonne AS idGymnaste,
       p.nom AS nomGymnaste,
       p.prenom AS prenomGymnaste,
       CASE 
           WHEN i.date > e.dateOuverture THEN e.fraisInscription * 2
           WHEN g.idFederation = e.idFederation THEN e.fraisInscription * 0.8
           ELSE e.fraisInscription
       END AS fraisReel
FROM Inscription i
JOIN Gymnaste g ON i.idgymnaste = g.idPersonne
JOIN evenement e ON i.idevenement = e.id
join federation f on e.idfederation = f.id 
JOIN Personne p ON g.idPersonne = p.id
WHERE e.nom = 'TRA RGI World Cup 2022'
ORDER BY p.nom, p.prenom;
```

Résultat:

![Résultat](./CapturesEcran/11.png)

12. Les fédérations (triées par leur nom) avec leurs événements ainsi que l'écart entre les frais
d'inscription à l'événement et les frais d'inscription moyens aux événements de la
fédération.
```sql
SELECT f.nom AS federation,
       e.nom AS evenement,
       e.fraisInscription AS fraisEvenement,
       AVG(e.fraisInscription) OVER (PARTITION BY f.id) AS fraisMoyensFederation,
       (e.fraisInscription - AVG(e.fraisInscription) OVER (PARTITION BY f.id)) AS ecartFrais
FROM Federation f
JOIN evenement e ON f.id = e.idFederation
ORDER BY f.nom, e.nom;
```

Résultat:

![Résultat](./CapturesEcran/12.png)

13. Les gymnastes qui ne se sont inscrits qu’à des événements organisés par leur fédération
```sql
-- TODO: vérifier pcq pas sur
SELECT p.id AS idGymnaste,
       p.nom AS nomGymnaste, 
       p.prenom AS prenomGymnaste,
       COUNT(DISTINCT e.id) AS nombreEvenements
FROM Gymnaste g
JOIN Personne p ON g.idPersonne = p.id
JOIN Inscription i ON g.idPersonne = i.idgymnaste
JOIN Evenement e ON i.idevenement = e.id
JOIN Federation f ON e.idFederation = f.id
WHERE f.id = g.idFederation
GROUP BY p.id, p.nom, p.prenom, g.idPersonne
HAVING COUNT(DISTINCT e.id) = 
       (SELECT COUNT(DISTINCT e2.id)
        FROM Inscription i2
        JOIN Evenement e2 ON i2.idevenement = e2.id
        JOIN Federation f2 ON e2.idFederation = f2.id
        WHERE i2.idgymnaste = g.idPersonne AND f2.id = g.idFederation);
```

Résultat:

![Résultat](./CapturesEcran/13.png)


## Partie 2
### Script SQL
Ecrire un script SQL qui permet de rajouter la vérification (CI) suivante :
Tout coach doit avoir au moins 18 ans.

``` sql
-- TODO: marche pas
$$
CREATE TRIGGER check_coach_age_before_insert
BEFORE INSERT ON Coach
FOR EACH ROW
BEGIN
    DECLARE age INT;

    -- Récupérer la date de naissance du coach depuis la table Personne
    SELECT EXTRACT(YEAR FROM AGE(CURDATE(), p.dateNaissance)) INTO age
    FROM Personne p
    WHERE p.id = NEW.idPersonne;

    -- Vérifier que le coach a au moins 18 ans
    IF age < 18 THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Coach must be at least 18 years old.';
    END IF;
END $$

$$
CREATE TRIGGER check_coach_age_before_update
BEFORE UPDATE ON Personne
FOR EACH ROW
BEGIN
    DECLARE age INT;

    -- Récupérer la date de naissance de la Personne
    SELECT EXTRACT(YEAR FROM AGE(CURDATE(), p.dateNaissance)) INTO age
    FROM Personne p
    WHERE p.id = NEW.idPersonne;

    -- Vérifier que le coach a au moins 18 ans
    IF age < 18 AND EXISTS(SELECT c.idPersonne FROM Coach c WHERE c.idPersonne = NEW.id) THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Coach must be at least 18 years old.';
    END IF;
END $$

```

### Tests
Test avec l'insertion d'un coach mineur:
``` sql
INSERT INTO Personne(nom, prenom, dateNaissance, idPays) VALUES ('Tester', 'testé', '2012-12-12', (SELECT id FROM Pays WHERE nom = 'Switzerland'));
INSERT INTO Coach (idPersonne, codeDiscipline) VALUES ((SELECT MAX(id) FROM Personne), 'TRA');
```
Résultat:
// TODO

Test avec l'insertion d'un coach majeur:
``` sql
INSERT INTO Personne(nom, prenom, dateNaissance, idPays) VALUES ('Tester', 'testé', '2000-12-12', (SELECT id FROM Pays WHERE nom = 'Switzerland'));
INSERT INTO Coach (idPersonne, codeDiscipline) VALUES ((SELECT MAX(id) FROM Personne), 'TRA');
```
Résultat:
// TODO

Test avec l'update du coach précédement inséré en mettant une date de naissance plus tard (coach ayant moins de 18 ans):
