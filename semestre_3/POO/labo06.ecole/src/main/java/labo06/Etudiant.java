package labo06;

public class Etudiant extends Personne {
    private int matricule;
    private Groupe groupe;

    public Etudiant(String nom, String prenom, int matricule) {
        super(nom, prenom);
        this.matricule = matricule;
    }

    public void setGroupe(Groupe groupe) {
        this.groupe = groupe;
    }

    public String toString() {
        return "Etud. " + prenom + " " + nom + " (#" + matricule + ")" +
                (groupe != null ? " - " + groupe.nom() : "");
    }
}
