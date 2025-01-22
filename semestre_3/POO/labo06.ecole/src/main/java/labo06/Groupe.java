package labo06;

import java.util.ArrayList;

public class Groupe {
    private int numero;
    private String orientation;
    private int trimestre;
    private ArrayList<Etudiant> etudiants = new ArrayList<>();
    private ArrayList<Lecon> lecons = new ArrayList<>();

    public Groupe(int numero, String orientation, int trimestre) {
        this.numero = numero;
        this.orientation = orientation;
        this.trimestre = trimestre;
    }

    public void ajouterEtudiant(Etudiant etudiant) {
        etudiant.setGroupe(this);
        etudiants.add(etudiant);
    }

    public void definirLecons(Lecon... lecons) {
        for (Lecon lecon : lecons) {
            this.lecons.add(lecon);
        }
    }

    public String nom() {
        return orientation + trimestre + "-" + numero;
    }

    public int nombreEtudiants() {
        return etudiants.size();
    }

    public String horaire() {
        return Lecon.horaire(lecons.toArray(new Lecon[0]));
    }
}
