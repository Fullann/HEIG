package chess.engine.piece;

import chess.PieceType;
import chess.PlayerColor;
import chess.engine.util.Board;
import chess.engine.util.Direction;

/**
 * Classe représentant une pièce Fou dans un jeu d'échecs.
 */
public final class Bishop extends ChessPiece {

  private static final PieceType PIECE_TYPE = PieceType.BISHOP;
  private static final int MAX_LENGTH_MOVE = Board.BOARD_SIZE - 1;
  private static final Direction[] POSSIBLE_MOVES = {
      Direction.NORTH_EAST, Direction.NORTH_WEST,
      Direction.SOUTH_EAST, Direction.SOUTH_WEST
  };
  /**
   * Constructeur pour un Fou avec la couleur donnée et la position donnée.
   * @param color la couleur du Fou
   * @param posX la position x du Fou
   * @param posY la position y du Fou
   * @return un Fou avec la couleur donnée et la position donnée
   */
  public Bishop(PlayerColor color, int posX, int posY) {
    super(color, posX, posY, PIECE_TYPE, POSSIBLE_MOVES);
  }

  @Override
  protected int possibleLengthDistance() {
    return MAX_LENGTH_MOVE;
  }
}
