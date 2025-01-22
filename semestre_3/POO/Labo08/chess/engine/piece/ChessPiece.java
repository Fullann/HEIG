package chess.engine.piece;

import chess.ChessView;
import chess.PieceType;
import chess.PlayerColor;
import chess.engine.util.Assertions;
import chess.engine.util.Board;
import chess.engine.util.Direction;
import chess.engine.util.Point;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

/**
 * Une classe qui représente une pièce dans une partie d'échecs.
 */
public abstract class ChessPiece implements ChessView.UserChoice {

  private final PieceType pieceType;
  private final PlayerColor color;
  private final Direction[] possibleMoves;
  private Point pos;

  protected ChessPiece(
      PlayerColor color,
      int posX, int posY,
      PieceType pieceType,
      Direction... possibleMoves) {
    Assertions.assertNotNull(color, "La couleur de la pièce ne peut pas être nulle");
    Assertions.assertNotNull(possibleMoves, "Les directions ne peuvent pas être nulles");
    Assertions.assertNotNull(pieceType, "Le type de pièce ne peut pas être nul");
    Assertions.assertTrue(Board.isInBoard(posX, posY), "La position est hors du plateau");
    for (Direction direction : possibleMoves) {
      Assertions.assertTrue(Direction.exists(direction), "La direction doit exister");
    }

    this.color = color;
    this.pos = new Point(posX, posY);
    this.pieceType = pieceType;
    this.possibleMoves = Arrays.copyOf(possibleMoves, possibleMoves.length);
  }

  @Override
  public String textValue() {
    return getPieceType().name();
  }

 /**
  * Vérifie si la pièce peut atteindre une position donnée sur le plateau depuis sa position actuelle.
  * 
  * @param dest  la position de destination
  * @return true si la pièce peut atteindre la position de destination, false sinon
  */
  protected Direction availableMove(Point dest) {
    return availableMoveFrom(this, pos, dest);
  }

  /**
   * Méthode statique utilisée pour obtenir le mouvement que la pièce peut utiliser pour atteindre une position donnée depuis sa position actuelle. 
   * Le mouvement doit être un mouvement possible de la pièce pour avoir une chance d'atteindre la position de destination.
   * 
   * @param piece la pièce à vérifier
   * @param from  la position de départ
   * @param dest  la position de destination
   * @return le mouvement que la pièce peut utiliser pour atteindre la position de destination
   */
  protected static Direction availableMoveFrom(ChessPiece piece, Point from, Point dest) {
    Direction move = Direction.offSetOf(from, dest);
    for (Direction possibleMove : piece.possibleMoves) {
      if (possibleMove.equals(move)) {
        return move;
      }
    }

    return null;
  }

  /**
   * Vérifie si la pièce peut atteindre une position donnée sur le plateau avec un mouvement spécifique.
   * Le mouvement doit être un mouvement possible de la pièce pour avoir une chance d'atteindre la position de destination.
   * Cette méthode ne vérifie pas si la position est occupée par une pièce ou non.
   *
   * @param board le plateau de jeu
   * @param dest  la position de destination
   * @param move  le mouvement à utiliser
   * @return true si la pièce peut atteindre la position de destination, false sinon
   */
  protected boolean canReach(Board board, Point dest, Direction move) {
    return pieceCanReachFrom(board, this, getPos(), dest, move);
  }

  /**
   * Méthode statique utilisée pour vérifier si une pièce peut atteindre une position de destination à partir d'une position différente avec un mouvement spécifié.
   * Cette méthode ne vérifie pas si la position est occupée par une pièce ou non.
   * Utile pour vérifier si le roi est en échec après un mouvement. Il est recommandé d'utiliser la méthode availableMoveFromTo pour passer un mouvement valide pour la pièce si elle existe.
   *
   * @param board le plateau de jeu
   * @param piece la pièce à vérifier
   * @param from  la position de départ
   * @param dest  la position de destination
   * @param move  le mouvement à vérifier
   * @return true si la pièce peut atteindre la position de destination, false sinon
   */
  protected static boolean pieceCanReachFrom(
      Board board,
      ChessPiece piece,
      Point from,
      Point dest,
      Direction move) {
    return Direction.exists(move)
        && haveEnoughMoveLengthFrom(piece, from, dest)
        && pathIsClear(board, move, from, dest);
  }

  /**
   * Méthode utilisée pour vérifier si une pièce pourrait capturer une autre pièce si une pièce se trouvait à la position de destination.
   * Cette méthode est utile pour vérifier si la position est attaquée par une pièce ou non.
   *
   * @param board le plateau de jeu
   * @param dest  la position de destination
   * @param move  le mouvement à utiliser
   * @return true si la pièce pourrait capturer la pièce à la position de destination, false sinon
   */
  protected boolean isAttacking(Board board, Point dest, Direction move) {
    return canReach(board, dest, move);
  }

  /**
   * Méthode publique utilisée pour vérifier si une pièce attaque une pièce à une position donnée sur le plateau depuis sa position actuelle.
   *
   * @param board le plateau de jeu
   * @param dest  la position de destination
   * @return true si la pièce pourrait capturer la pièce à la position de destination, false sinon
   */
  public boolean isAttacking(Board board, Point dest) {
    Assertions.assertNotNull(board, "Le plateau de jeu ne peut pas être nul");
    Assertions.assertTrue(Board.isInBoard(dest), "La position est hors du plateau");
    return isAttacking(board, dest, availableMove(dest));
  }

  /**
   * Vérifie si la pièce peut se déplacer vers une position donnée sur le plateau.
   * Cette méthode vérifie si la position est occupée par une pièce ou non. Ne peut se déplacer que si la destination n'est pas occupée par une pièce de la même couleur.
   *
   * @param board le plateau de jeu
   * @param dest  la position de destination
   * @return true si la pièce peut atteindre la position de destination, false sinon
   */
  public boolean canMoveTo(Board board, Point dest) {
    Assertions.assertNotNull(board, "Le plateau de jeu ne peut pas être nul");
    return Board.isInBoard(dest) && canReach(board, dest, availableMove(dest))
        && (!board.isOccupied(dest) || !isSameColor(board.getPiece(dest)))
        && !moveImpliesKingInCheck(board, dest);
  }

  /**
   * Méthode utilisée pour obtenir toutes les directions que la pièce peut emprunter.
   *
   * @return la liste de toutes les directions que la pièce peut emprunter.
   */
  public final List<Direction> getDirections() {
    return Arrays.asList(possibleMoves);
  }

  /**
   * Méthode utilisée pour vérifier si le déplacement de la pièce mettrait son roi en échec. Dans ce cas, le déplacement n'est pas autorisé.
   *
   * @param board le plateau de jeu
   * @param dest  la position de destination
   * @return true si le déplacement mettrait le roi en échec, false sinon
   */
  private boolean moveImpliesKingInCheck(Board board, Point dest) {
    Point kingPos = board.getKing(getPlayerColor()).getPos();
    Direction defendingFromMove = Direction.offSetOf(getPos(), kingPos);
    Direction newDefendingMove = Direction.offSetOf(dest, kingPos);
    List<ChessPiece> enemies = board.getAllPieces(getPlayerColor().opposite());
    for (ChessPiece enemy : enemies) {
      if (enemy.equals(board.getPiece(dest))) {
        continue;
      }

      Direction possibleMoveAttack = enemy.availableMove(kingPos);
      boolean isPinned = isPinned(
          board,
          kingPos,
          enemy,
          possibleMoveAttack,
          defendingFromMove,
          newDefendingMove);

      if (isPinned) {
        return true;
      }
    }

    return false;
  }

  /**
   * Vérifie si une pièce est clouée par une autre pièce. Une pièce est clouée si elle ne peut se déplacer que dans une direction spécifique pour défendre le roi.
   * Si la pièce est clouée, elle ne peut pas se déplacer dans une autre direction.
   *
   * @param board                 le plateau de jeu
   * @param kingPos               la position du roi
   * @param enemy                 l'ennemi qui pourrait attaquer le roi
   * @param attackingDirection    le mouvement que l'ennemi pourrait effectuer pour attaquer le roi
   * @param defendingDirection    le mouvement contre lequel le roi est défendu
   * @param newDefendingDirection le nouveau mouvement contre lequel le roi est défendu une fois que la pièce est déplacée
   * @return true si le roi est attaqué par l'ennemi avec une attaque clouée, false sinon
   */
  private boolean isPinned(
      Board board,
      Point kingPos,
      ChessPiece enemy,
      Direction attackingDirection,
      Direction defendingDirection,
      Direction newDefendingDirection) {
    return null != attackingDirection
        && enemy.possibleLengthDistance() > 1
        && attackingDirection.equals(defendingDirection)
        && !attackingDirection.equals(newDefendingDirection)
        && enemy.isAttacking(board, pos)
        && pieceCanReachFrom(
            board, enemy, pos, kingPos,
            availableMoveFrom(enemy, pos, kingPos));
  }

  /**
   * Vérifie s'il n'y a pas de pièce entre la position de départ et la position de destination.
   * Cette méthode ne vérifie pas si la position de départ et la position de destination sont occupées par une pièce.
   *
   * @param board le plateau de jeu
   * @param dest  la position de destination
   * @return true si le chemin est dégagé, false sinon
   */
  protected static boolean pathIsClear(
      Board board,
      Direction direction,
      Point from,
      Point dest) {
    Point current = from.withAdded(direction);
    while (!current.equals(dest)) {
      if (board.isOccupied(current)) {
        return false;
      }

      current = current.withAdded(direction);
    }

    return true;
  }

  /**
   * Méthode statique utilisée pour vérifier si la pièce a une longueur de mouvement suffisante pour atteindre la destination à partir de la position donnée.
   *
   * @param piece la pièce à vérifier
   * @param from  la position de départ
   * @param to    la position de destination
   * @return true si la pièce a une longueur de mouvement suffisante, false sinon
   */
  private static boolean haveEnoughMoveLengthFrom(ChessPiece piece, Point from, Point to) {
    int lengthMove = Direction.moveDistance(from, to);
    return lengthMove <= piece.possibleLengthDistance();
  }

  /**
   * Méthode utilisée pour mettre à jour la position de la pièce.
   *
   * @param p la nouvelle position
   */
  public void move(Point p) {
    Assertions.assertTrue(Board.isInBoard(p), "La position est hors du plateau");
    pos = p;
  }

  /**
   * Méthode utilisée pour vérifier si la pièce est de la même couleur qu'une autre pièce donnée.
   *
   * @param piece la pièce à vérifier
   * @return true si la pièce est de la même couleur, false sinon
   */
  public final boolean isSameColor(ChessPiece piece) {
    return null != piece && color.equals(piece.color);
  }

  /**
   * Méthode utilisée pour obtenir la longueur maximale du mouvement de la pièce.
   *
   * @return la longueur maximale du mouvement de la pièce
   */
  protected abstract int possibleLengthDistance();

  /**
   * Méthode utilisée pour obtenir le type de la pièce.
   *
   * @return le type de la pièce
   */
  public final PieceType getPieceType() {
    return pieceType;
  }

  /**
   * Méthode utilisée pour obtenir la couleur de la pièce.
   *
   * @return la couleur de la pièce
   */
  public final PlayerColor getPlayerColor() {
    return color;
  }

  /**
   * Méthode utilisée pour obtenir la position de la pièce.
   *
   * @return la position de la pièce
   */
  public final Point getPos() {
    return pos;
  }

  /**
   * Méthode utilisée pour obtenir la position x de la pièce.
   *
   * @return la position x de la pièce
   */
  public final int getX() {
    return pos.x();
  }

  /**
   * Méthode utilisée pour obtenir la position y de la pièce.
   *
   * @return la position y de la pièce
   */
  public final int getY() {
    return pos.y();
  }

  @Override
  public String toString() {
    return textValue() + ":" + getPlayerColor();
  }

  @Override
  public boolean equals(Object o) {
    if (this == o)
      return true;
    if (o == null || getClass() != o.getClass())
      return false;
    ChessPiece that = (ChessPiece) o;
    if (pieceType != that.pieceType)
      return false;
    if (color != that.color)
      return false;
    return Objects.equals(pos, that.pos);
  }

  @Override
  public int hashCode() {
    int result = pieceType != null ? pieceType.hashCode() : 0;
    result = 31 * result + (color != null ? color.hashCode() : 0);
    result = 31 * result + (pos != null ? pos.hashCode() : 0);
    return result;
  }
}
