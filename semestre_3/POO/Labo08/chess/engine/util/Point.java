package chess.engine.util;

/**
 * Classe représentant un point sur un plan cartésien.
 */
public record Point(int x, int y) {

  /**
   * Retourne un nouveau point qui est la somme de ce point et de la direction donnée.
   * @param direction la direction à ajouter
   * @return un nouveau point qui est la somme de ce point et de la direction donnée
   */
  public Point withAdded(Direction direction) {
    return new Point(x + direction.xOffset(), y + direction.yOffset());
  }
}
