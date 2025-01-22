/***
 * Labo 05 - MatriceModulo
 * Desc: Créez une classe MatriceModulo qui permet de manipuler des matrices modulo n. 
 *       En faisant des additions, des soustractions et des multiplications composante par composante.
 * Date: 30/10/2024
 * Auteur: Mathéo Lopez, Nathan Füllemann
 */

import java.util.Random;

class MatriceModulo {
    private int[][] matrice;
    private int rows;
    private int cols;
    private int modulo;

    // Constructeur pour créer une matrice vide avec des dimensions données et un modulo
    public MatriceModulo(int rows, int cols, int modulo) {
        this.rows = rows;
        this.cols = cols;
        this.modulo = modulo;
        this.matrice = new int[rows][cols];
    }

    // Constructeur pour générer une matrice aléatoire avec des valeurs entre 0 et modulo-1
    public MatriceModulo(int rows, int cols, int modulo, boolean aleatoire) {
        this(rows, cols, modulo);
        if (aleatoire) {
            Random rand = new Random();
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    this.matrice[i][j] = rand.nextInt(modulo);
                }
            }
        }
    }

    // Constructeur pour créer une matrice avec des valeurs données
    public MatriceModulo(int[][] valeurs, int modulo) {
        this.rows = valeurs.length;
        this.cols = valeurs[0].length;
        this.modulo = modulo;
        this.matrice = new int[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                this.matrice[i][j] = Math.floorMod(valeurs[i][j], modulo);
            }
        }
    }

    // Méthode pour afficher la matrice
    public void afficher() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                System.out.print(matrice[i][j] + " ");
            }
            System.out.println();
        }
    }

    // Méthode générique pour appliquer une opération entre deux matrices
    public MatriceModulo operationMatrice(MatriceModulo autre, String operation) {
        if (this.modulo != autre.modulo) {
            throw new RuntimeException("Les modules des deux matrices ne correspondent pas.");
        }

        int maxRows = Math.max(this.rows, autre.rows);
        int maxCols = Math.max(this.cols, autre.cols);
        MatriceModulo resultat = new MatriceModulo(maxRows, maxCols, this.modulo);

        for (int i = 0; i < maxRows; i++) {
            for (int j = 0; j < maxCols; j++) {
                int valA = (i < this.rows && j < this.cols) ? this.matrice[i][j] : 0;
                int valB = (i < autre.rows && j < autre.cols) ? autre.matrice[i][j] : 0;

                // Appliquer l'opération spécifiée
                switch (operation) {
                    case "addition":
                        resultat.matrice[i][j] = Math.floorMod(valA + valB, this.modulo);
                        break;
                    case "soustraction":
                        resultat.matrice[i][j] = Math.floorMod(valA - valB, this.modulo);
                        break;
                    case "multiplication":
                        resultat.matrice[i][j] = Math.floorMod(valA * valB, this.modulo);
                        break;
                    default:
                        throw new RuntimeException("Opération non reconnue: " + operation);
                }
            }
        }

        return resultat;
    }

    // Programme de test
    public static void main(String[] args) {
        // Paramètres : N1, M1, N2, M2, n
        int N1 = 3, M1 = 4, N2 = 3, M2 = 5, modulo = 5;

        // Matrice aléatoire N1 x M1
        MatriceModulo matrice1 = new MatriceModulo(N1, M1, modulo, true);
        System.out.println("Matrice 1:");
        matrice1.afficher();

        // Matrice aléatoire N2 x M2
        MatriceModulo matrice2 = new MatriceModulo(N2, M2, modulo, true);
        System.out.println("Matrice 2:");
        matrice2.afficher();

        // Addition
        MatriceModulo somme = matrice1.operationMatrice(matrice2, "addition");
        System.out.println("Addition:");
        somme.afficher();

        // Soustraction
        MatriceModulo difference = matrice1.operationMatrice(matrice2, "soustraction");
        System.out.println("Soustraction:");
        difference.afficher();

        // Multiplication composante par composante
        MatriceModulo produit = matrice1.operationMatrice(matrice2, "multiplication");
        System.out.println("Multiplication composante par composante:");
        produit.afficher();
    }
}
