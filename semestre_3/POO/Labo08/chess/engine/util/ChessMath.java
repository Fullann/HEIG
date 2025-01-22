package chess.engine.util;

/**
 * Classe utilitaire pour les opérations mathématiques.
 *
 */
public class ChessMath {

  /**
   * Permet de calculer le plus grand commun diviseur de deux entiers.
   */
  public static int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
  }
}
