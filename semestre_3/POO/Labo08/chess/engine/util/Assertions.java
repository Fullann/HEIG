package chess.engine.util;

/**
 * Classe utilitaire pour les assertions
 */
public final class Assertions {

  private Assertions() {
  }

  /**
   * Permet de vérifier qu'une condition est vraie
   * @param condition la condition à vérifier
   * @param message le message à afficher si la condition est fausse
   */
  public static void assertTrue(boolean condition, String message) {
    if (!condition) {
      throw new IllegalArgumentException(message);
    }
  }

  /**
   * Permet de vérifier qu'une valeur n'est pas nulle
   * @param value la valeur à vérifier
   * @param message le message à afficher si la valeur est nulle
   */
  public static void assertNotNull(Object value, String message) {
    if (null == value) {
      throw new IllegalArgumentException(message);
    }
  }
}
