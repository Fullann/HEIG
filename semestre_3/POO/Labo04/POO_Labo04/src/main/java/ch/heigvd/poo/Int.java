package ch.heigvd.poo;

// Int.java
public class Int {
  private int valeur;

  // Constructeur
  public Int(int valeur) {
    this.valeur = valeur;
  }

  // Méthode pour obtenir la valeur encapsulée
  public int getValeur() {
    return valeur;
  }

  // Méthode pour modifier la valeur encapsulée
  public void setValeur(int valeur) {
    this.valeur = valeur;
  }

  // Méthode pour échanger la valeur avec un autre objet Int
  public void echangeAvec(Int autre) {
    int temp = this.valeur;
    this.valeur = autre.getValeur();
    autre.setValeur(temp);
  }

  // Représentation en chaîne de caractères de l'objet courant
  @Override
  public String toString() {
    return String.valueOf(valeur);
  }

  // Fonction main pour tester la classe Int
  public static void main(String[] args) {
    Int a = new Int(5);
    Int b = new Int(10);

    System.out.println("Avant échange : a = " + a + ", b = " + b);
    a.echangeAvec(b);
    System.out.println("Après échange : a = " + a + ", b = " + b);
  }
}
