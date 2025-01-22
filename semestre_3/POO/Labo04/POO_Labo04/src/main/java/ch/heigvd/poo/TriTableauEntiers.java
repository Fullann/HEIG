package ch.heigvd.poo;

// TriTableauEntiers.java
public class TriTableauEntiers {

  // Méthode pour convertir une chaîne de caractères en entier
  public static int stringToInt(String s) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (s.charAt(0) == '-') {
      sign = -1;
      i++;
    } else if (s.charAt(0) == '+') {
      i++;
    }

    while (i < s.length()) {
      char c = s.charAt(i);
      if (c >= '0' && c <= '9') {
        result = result * 10 + (c - '0');
      } else {
        System.out.println("Erreur: caractère non valide détecté.");
        System.exit(1);
      }
      i++;
    }

    return result * sign;
  }

  // Algorithme de tri à bulles
  public static void bubbleSort(int[] arr) {
    int n = arr.length;
    boolean swapped;
    do {
      swapped = false;
      for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
          int temp = arr[i];
          arr[i] = arr[i + 1];
          arr[i + 1] = temp;
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
    int[] tableau = new int[args.length];
    for (int i = 0; i < args.length; i++) {
      tableau[i] = stringToInt(args[i]);
    }

    // Tri du tableau
    bubbleSort(tableau);

    // Affichage du tableau trié
    System.out.println("Tableau trié :");
    for (int num : tableau) {
      System.out.print(num + " ");
    }
  }
}
