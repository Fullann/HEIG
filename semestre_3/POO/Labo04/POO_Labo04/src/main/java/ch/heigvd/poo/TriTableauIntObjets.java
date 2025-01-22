package ch.heigvd.poo;

// TriTableauIntObjets.java
public class TriTableauIntObjets {

  // Méthode pour échanger deux éléments d'un tableau d'objets Int
  public static void echangeElementsTableau(Int[] arr, int i, int j) {
    Int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }

  // Méthode pour échanger la valeur de deux objets Int
  public static void echangeValeursObjets(Int a, Int b) {
    int temp = a.getValeur();
    a.setValeur(b.getValeur());
    b.setValeur(temp);
  }

  // Méthode dans la classe Int pour échanger la valeur avec un autre objet Int
  public static void echangeValeursClasse(Int a, Int b) {
    a.echangeAvec(b);
  }

  // Algorithme de tri à bulles pour un tableau d'objets Int
  public static void bubbleSort(Int[] arr) {
    int n = arr.length;
    boolean swapped;
    do {
      swapped = false;
      for (int i = 0; i < n - 1; i++) {
        if (arr[i].getValeur() > arr[i + 1].getValeur()) {
          // Choisissez l'une des trois méthodes d'échange :
          // echangeElementsTableau(arr, i, i + 1);
          // echangeValeursObjets(arr[i], arr[i + 1]);
          echangeValeursClasse(arr[i], arr[i + 1]);
          swapped = true;
        }
      }
    } while (swapped);
  }

  // Fonction main
  public static void main(String[] args) {
    if (args.length == 0) {
      System.out.println("Veuillez fournir des nombres en arguments.");
      return;
    }

    // Récupération et conversion des arguments
    Int[] tableau = new Int[args.length];
    for (int i = 0; i < args.length; i++) {
      tableau[i] = new Int(TriTableauEntiers.stringToInt(args[i]));
    }

    // Tri du tableau
    bubbleSort(tableau);

    // Affichage du tableau trié
    System.out.println("Tableau trié d'objets Int :");
    for (Int obj : tableau) {
      System.out.print(obj + " ");
    }
  }
}
