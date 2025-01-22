package chess.engine.piece;

import chess.PieceType;
import chess.PlayerColor;
import chess.engine.util.Board;
import chess.engine.util.Direction;

/**
 * Classe représentant une pièce Reine dans un jeu d'échecs.
 */
public final class Queen extends ChessPiece {

  private static final PieceType PIECE_TYPE = PieceType.QUEEN;
  private static final int MAX_LENGTH_MOVE = Board.BOARD_SIZE - 1;
  private static final Direction[] POSSIBLE_MOVES = {
      Direction.NORTH, Direction.SOUTH, Direction.EAST, Direction.WEST,
      Direction.NORTH_EAST, Direction.NORTH_WEST, Direction.SOUTH_EAST, Direction.SOUTH_WEST
  };
  /**
   * Constructeur pour une Reine avec la couleur donnée et la position donnée.
   * @param color la couleur de la Reine
   * @param posX la position x de la Reine
   * @param posY la position y de la Reine
   * @return une Reine avec la couleur donnée et la position donnée
   */
  public Queen(PlayerColor color, int posX, int posY) {
    super(color, posX, posY, PIECE_TYPE, POSSIBLE_MOVES);
  }

  @Override
  protected int possibleLengthDistance() {
    return MAX_LENGTH_MOVE;
  }

}
