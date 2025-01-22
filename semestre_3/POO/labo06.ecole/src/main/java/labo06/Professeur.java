package labo06;

public class Professeur extends Personne {
    private String abreviation;

    public Professeur(String nom, String prenom, String abreviation) {
        super(nom, prenom);
        this.abreviation = abreviation;
    }

    public String getAbreviation() {
        return abreviation;
    }

    public String horaire(Lecon[] lecons) {
        return Lecon.horaire(lecons);
    }
    
    public String toString() {
        return "Prof. " + prenom + " " + nom + " (" + abreviation + ")";
    }
}
