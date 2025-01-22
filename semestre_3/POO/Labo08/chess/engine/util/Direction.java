package chess.engine.util;

/**
 * Enumération qui représente les directions possibles pour un déplacement.
 */
public enum Direction {
  NORTH(0, 1),
  EAST(1, 0),
  SOUTH(0, -1),
  WEST(-1, 0),
  NORTH_EAST(1, 1),
  SOUTH_EAST(1, -1),
  SOUTH_WEST(-1, -1),
  NORTH_WEST(-1, 1),
  L_EAST_NORTH(2, 1),
  L_NORTH_EAST(1, 2),
  L_EAST_SOUTH(2, -1),
  L_SOUTH_EAST(1, -2),
  L_WEST_SOUTH(-2, -1),
  L_SOUTH_WEST(-1, -2),
  L_WEST_NORTH(-2, 1),
  L_NORTH_WEST(-1, 2);

  private final int xOff;
  private final int yOff;

  Direction(int xOff, int yOff) {
    this.xOff = xOff;
    this.yOff = yOff;
  }

  /**
   * Méthode utilisée pour obtenir le décalage de deux coordonnées représentées par une Direction.
   *
   * @param x La coordonnée x.
   * @param y La coordonnée y.
   * @return La Direction représentant le décalage des deux coordonnées.
   *         Si le décalage n'est pas valide, retourne null.
   */
  public static Direction offSetOf(int x, int y) {
    int length = Math.abs(ChessMath.gcd(x, y));
    if (length != 0) {
      x /= length;
      y /= length;
    }

    for (Direction direction : values()) {
      if (direction.xOff == x && direction.yOff == y) {
        return direction;
      }
    }

    return null;
  }

  /**
   * Méthode utilisée pour obtenir le décalage entre deux points représentés par une Direction.
   *
   * @param from La position de départ.
   * @param to   La position d'arrivée.
   * @return La Direction représentant le décalage entre les deux points.
   *         Si le décalage n'est pas valide, retourne null.
   */
  public static Direction offSetOf(Point from, Point to) {
    return offSetOf(to.x() - from.x(), to.y() - from.y());
  }

  /**
   * Méthode utilisée pour obtenir la longueur du décalage entre deux coordonnées.
   * Si la direction n'est pas valide, retourne 0.
   *
   * @param from La position de départ.
   * @param to   La position d'arrivée.
   * @return La longueur du décalage entre les deux coordonnées si la direction est valide, 0 sinon.
   */
  public static int moveDistance(Point from, Point to) {
    if (Direction.offSetOf(from, to) == null) {
      return 0;
    }

    int xDiff = to.x() - from.x();
    int yDiff = to.y() - from.y();
    return Math.abs(ChessMath.gcd(xDiff, yDiff));
  }

  /**
   * Vérifie si la direction donnée est valide.
   *
   * @param dir La direction à vérifier.
   * @return True si la direction est valide, false sinon.
   */
  public static boolean exists(Direction dir) {
    return dir != null;
  }

  /**
   * Méthode utilisée pour vérifier si une direction est diagonale.
   *
   * @return True si la direction est diagonale, false sinon.
   */
  public boolean isDiagonal() {
    return Math.abs(xOff) == Math.abs(yOff);
  }

  /**
   * Méthode utilisée pour obtenir le décalage x de la direction actuelle.
   *
   * @return Le décalage x de la direction.
   */
  public int xOffset() {
    return xOff;
  }

  /**
   * Méthode utilisée pour obtenir le décalage y de la direction actuelle.
   *
   * @return Le décalage y de la direction.
   */
  public int yOffset() {
    return yOff;
  }

  /**
   * Méthode utilisée pour obtenir la direction opposée à la direction actuelle.
   *
   * @return La direction opposée à la direction actuelle.
   */
  public Direction opposite() {
    return offSetOf(-xOff, -yOff);
  }
}
