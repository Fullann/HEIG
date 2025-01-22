package chess.engine.piece;

import chess.PieceType;
import chess.PlayerColor;
import chess.engine.util.Board;
import chess.engine.util.Direction;
import chess.engine.util.Point;

/**
 * Classe représentant une pièce Pion dans un jeu d'échecs.
 */
public final class Pawn extends SpecialFirstMovePiece implements PromotablePiece {

  private static final PieceType PIECE_TYPE = PieceType.PAWN;
  private static final int INITIAL_DISPLACEMENT_LENGTH = 2;
  private static final int LENGTH_NORMAL_DISPLACEMENT = 1;
  private static final Direction[] DISPLACE_POSSIBLES_NORD = {
      Direction.NORTH, Direction.NORTH_EAST, Direction.NORTH_WEST
  };
  private static final Direction[] DISPLACE_POSSIBLES_SUD = {
      Direction.SOUTH, Direction.SOUTH_EAST, Direction.SOUTH_WEST
  };

  /**
   * Crée un nouveau Pion avec la couleur et la position données.
   *
   * @param couleur la couleur du Pion
   * @param posX    la position x du Pion
   * @param posY    la position y du Pion
   */
  public Pawn(PlayerColor couleur, int posX, int posY) {
    super(couleur, posX, posY, PIECE_TYPE, getPossibleDisplacements(couleur));
  }

  /**
   * Méthode utilisée pour déterminer les déplacements possibles du Pion.
   * Les déplacements vers le nord sont possibles si le Pion est blanc,
   * les déplacements vers le sud sont possibles si le Pion est noir.
   *
   * @param couleur la couleur du Pion
   * @return les déplacements possibles du Pion
   */
  private static Direction[] getPossibleDisplacements(PlayerColor couleur) {
    return couleur == PlayerColor.WHITE ? DISPLACE_POSSIBLES_NORD : DISPLACE_POSSIBLES_SUD;
  }

  @Override
  protected boolean isAttacking(Board plateau, Point destination, Direction travel) {
    return Direction.exists(travel)
        && travel.isDiagonal()
        && Direction.moveDistance(getPos(), destination) == LENGTH_NORMAL_DISPLACEMENT;
  }

  @Override
  protected boolean canReach(Board plateau, Point destination, Direction travel) {
    if (!Direction.exists(travel)
        || (travel.isDiagonal()
            && Direction.moveDistance(getPos(), destination) != LENGTH_NORMAL_DISPLACEMENT)) {
      return false;
    }

    return super.canReach(plateau, destination, travel)
        && (travel.isDiagonal() == plateau.isOccupied(destination) || isEnPassant(plateau, destination, travel));
  }

  /**
   * Vérifie si le déplacement est un mouvement en passant.
   * Le déplacement doit être diagonal, le dernier mouvement de l'adversaire
   * doit être un double déplacement d'un Pion, et la destination doit
   * correspondre à la position où le Pion adverse aurait avancé d'une case.
   *
   * @param plateau le plateau de jeu
   * @param destination la destination du mouvement
   * @param travel la direction du mouvement
   * @return vrai si c'est un mouvement en passant, faux sinon
   */
  private boolean isEnPassant(Board plateau, Point destination, Direction travel) {
    Point lastMoveTo = plateau.getLastMoveTo();
    if (lastMoveTo == null) {
      return false;
    }
    ChessPiece partMovedPreviously = plateau.getPiece(lastMoveTo);
    return travel.isDiagonal()
        && partMovedPreviously instanceof Pawn pion
        && Direction.moveDistance(plateau.getLastMoveFrom(), lastMoveTo) == INITIAL_DISPLACEMENT_LENGTH
        && isNextTo(pion)
        && destination.x() == lastMoveTo.x();
  }

  /**
   * Vérifie si une pièce est située à côté de la pièce actuelle sur l'axe x
   * et sur le même axe y.
   *
   * @param pièce la pièce à vérifier
   * @return vrai si la pièce est à côté, faux sinon
   */
  private boolean isNextTo(ChessPiece pièce) {
    return Math.abs(pièce.getX() - getX()) == 1 && pièce.getY() == getY();
  }

  @Override
  protected int possibleLengthDistance() {
    return hasMoved() ? LENGTH_NORMAL_DISPLACEMENT : INITIAL_DISPLACEMENT_LENGTH;
  }

  @Override
  public boolean canPromote() {
    return getY() == (getPossibleDisplacements(getPlayerColor()) == DISPLACE_POSSIBLES_NORD
        ? Board.BOARD_SIZE - 1
        : 0);
  }

  /**
   * Vérifie si le déplacement est un mouvement en passant (surchargé sans direction).
   *
   * @param plateau le plateau de jeu
   * @param destination la destination du mouvement
   * @return vrai si c'est un mouvement en passant, faux sinon
   */
  public boolean isEnPassant(Board plateau, Point destination) {
    return isEnPassant(plateau, destination, availableMove(destination));
  }
}
