package chess.engine.piece;

import chess.PieceType;
import chess.PlayerColor;
import chess.engine.util.Direction;

/**
 * Classe représentant une pièce Cavalier dans un jeu d'échecs.
 */
public final class Knight extends ChessPiece {

  private static final PieceType PIECE_TYPE = PieceType.KNIGHT;
  private static final int MAX_LENGTH_MOVE = 1;
  private static final Direction[] POSSIBLE_MOVES = {
      Direction.L_EAST_NORTH, Direction.L_NORTH_EAST,
      Direction.L_EAST_SOUTH, Direction.L_SOUTH_EAST,
      Direction.L_WEST_SOUTH, Direction.L_SOUTH_WEST,
      Direction.L_WEST_NORTH, Direction.L_NORTH_WEST
  };

 /**
  * Constructeur pour un Cavalier avec la couleur donnée et la position donnée.
  * @param color la couleur du Cavalier
  * @param posX la position x du Cavalier
  * @param posY la position y du Cavalier
  * @return un Cavalier avec la couleur donnée et la position donnée
  */
  public Knight(PlayerColor color, int posX, int posY) {
    super(color, posX, posY, PIECE_TYPE, POSSIBLE_MOVES);
  }

  /**
   * Méthode qui retourne la distance maximale possible pour un déplacement.
   * @return la distance maximale possible pour un déplacement
   */
  @Override
  protected int possibleLengthDistance() {
    return MAX_LENGTH_MOVE;
  }
}
