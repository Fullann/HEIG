package chess.engine.piece;

import chess.PieceType;
import chess.PlayerColor;
import chess.engine.util.Board;
import chess.engine.util.Direction;

/**
 * Classe représentant une pièce Tour dans un jeu d'échecs.
 */
public final class Rook extends SpecialFirstMovePiece implements CastlingPiece {

  private static final PieceType PIECE_TYPE = PieceType.ROOK;
  private static final int MAX_LENGTH_MOVE = Board.BOARD_SIZE - 1;
  private static final Direction[] POSSIBLE_MOVES = {
      Direction.NORTH, Direction.SOUTH, Direction.EAST, Direction.WEST
  };

  /**
   * Constructeur pour une Tour avec la couleur donnée et la position donnée.
   * @param color la couleur de la Tour
   * @param posX la position x de la Tour
   * @param posY la position y de la Tour
   * @return une Tour avec la couleur donnée et la position donnée
   */
  public Rook(PlayerColor color, int posX, int posY) {
    super(color, posX, posY, PIECE_TYPE, POSSIBLE_MOVES);
  }

  @Override
  protected int possibleLengthDistance() {
    return MAX_LENGTH_MOVE;
  }

  @Override
  public boolean canCastle() {
    return !hasMoved();
  }

}
