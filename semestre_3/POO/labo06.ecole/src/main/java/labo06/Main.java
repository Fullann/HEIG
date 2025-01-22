package labo06;
import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {
        // Création des professeurs
        Professeur profPDO = new Professeur("Donini", "Pier", "PDO");
        Professeur profDRE = new Professeur("Rossier", "Daniel", "DRE");

        // Création des leçons
        Lecon leconPOO1 = new Lecon("POO", 3, "13:15", 90, "H02", profPDO);
        Lecon leconPOO2 = new Lecon("POO", 4, "13:15", 90, "H02", profPDO);
        Lecon leconPOO3 = new Lecon("POO", 4, "14:55", 90, "H02", profPDO);
        Lecon leconSYE1 = new Lecon("SYE", 1, "8:30", 90, "G01", profDRE);
        Lecon leconSYE2 = new Lecon("SYE", 4, "10:25", 90, "A09", profDRE);
        Lecon leconTIC = new Lecon("TIC", 2, "16:35", 90, "F06", null);

        // Création des étudiants
        Etudiant etud1 = new Etudiant("Lennon", "John", 1234);
        Etudiant etud2 = new Etudiant("Mc Cartney", "Paul", 2341);
        Etudiant etud3 = new Etudiant("Starr", "Ringo", 3241);
        Etudiant etud4 = new Etudiant("Harisson", "George", 4321);
        Etudiant etud5 = new Etudiant("Waters", "Roger", 1324);
        Etudiant etud6 = new Etudiant("Gilmour", "David", 4312);

        // Création des groupes
        Groupe groupeIL6_1 = new Groupe(1, "IL", 6);
        groupeIL6_1.ajouterEtudiant(etud1);
        groupeIL6_1.ajouterEtudiant(etud2);
        groupeIL6_1.ajouterEtudiant(etud3);
        groupeIL6_1.ajouterEtudiant(etud4);
        groupeIL6_1.definirLecons(leconPOO1, leconPOO2, leconPOO3, leconSYE1, leconTIC,leconSYE2);

        Groupe groupeSI6_1 = new Groupe(1, "SI", 6);
        groupeSI6_1.ajouterEtudiant(etud5);
        groupeSI6_1.ajouterEtudiant(etud6);
        groupeSI6_1.definirLecons(leconPOO1, leconPOO2, leconPOO3);

        // Affichage des membres de l'école
        ArrayList<Personne> personnes = new ArrayList<>();
        personnes.add(profPDO);
        personnes.add(profDRE);
        personnes.add(etud1);
        personnes.add(etud2);
        personnes.add(etud3);
        personnes.add(etud4);
        personnes.add(etud5);
        personnes.add(etud6);

        System.out.println("-- Membres de l'école");
        for (Personne personne : personnes) {
            System.out.println(personne);
        }

        // Affichage de l'horaire du groupe IL6-1
        System.out.println("\n-- Horaire du groupe " + groupeIL6_1.nom() + " (" + groupeIL6_1.nombreEtudiants() + " étudiants)");
        System.out.println(groupeIL6_1.horaire());

        // Affichage de l'horaire du professeur PDO
        System.out.println("\n-- Horaire Prof. " + profPDO.getAbreviation());
        System.out.println(profPDO.horaire(new Lecon[]{leconPOO1, leconPOO2, leconPOO3}));
    }
}