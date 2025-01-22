package chess.engine.piece;

import chess.PieceType;
import chess.PlayerColor;
import chess.engine.util.Direction;
import chess.engine.util.Point;

/**
 * Classe abstraite représentant une pièce qui peut effectuer un mouvement spécial lors de son
 */
public abstract class SpecialFirstMovePiece extends ChessPiece {

  private boolean hasMoved = false;

  protected SpecialFirstMovePiece(
      PlayerColor color,
      int posX,
      int posY,
      PieceType pieceType,
      Direction... possibleMoves) {
    super(color, posX, posY, pieceType, possibleMoves);
  }

  public boolean hasMoved() {
    return hasMoved;
  }
  
  @Override
  public void move(Point pos) {
    if (!hasMoved) {
      hasMoved = true;
    }

    super.move(pos);
  }

  @Override
  public boolean equals(Object o) {
    if (this == o)
      return true;
    if (o == null || getClass() != o.getClass())
      return false;
    if (!super.equals(o))
      return false;
    SpecialFirstMovePiece that = (SpecialFirstMovePiece) o;
    return hasMoved == that.hasMoved;
  }

  @Override
  public int hashCode() {
    int result = super.hashCode();
    result = 31 * result + (hasMoved ? 1 : 0);
    return result;
  }
}
