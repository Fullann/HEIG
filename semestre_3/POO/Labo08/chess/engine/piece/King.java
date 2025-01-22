package chess.engine.piece;

import chess.PieceType;
import chess.PlayerColor;
import chess.engine.util.Assertions;
import chess.engine.util.Board;
import chess.engine.util.Direction;
import chess.engine.util.Point;
import java.util.*;

/**
 * Classe représentant une pièce Roi dans un jeu d'échecs.
 */
public final class King extends SpecialFirstMovePiece implements CastlingPiece {

  private static final PieceType PIECE_TYPE = PieceType.KING;
  private static final int MAX_LENGTH_MOVE = 1;
  private static final int LENGTH_CASTLING = 2;
  private static final Direction[] POSSIBLE_MOVES = {
      Direction.NORTH, Direction.SOUTH, Direction.EAST, Direction.WEST,
      Direction.NORTH_EAST, Direction.NORTH_WEST, Direction.SOUTH_EAST, Direction.SOUTH_WEST
  };

  private final List<ChessPiece> inCheckBy = new LinkedList<>();
  private final List<CastlingPiece> castlingPieces = new LinkedList<>();

  /**
   * Constructeur pour un Roi avec la couleur donnée et la position donnée.
   *
   * @param color la couleur du Roi
   * @param posX  la position x du Roi
   * @param posY  la position y du Roi
   */
  public King(PlayerColor color, int posX, int posY) {
    super(color, posX, posY, PIECE_TYPE, POSSIBLE_MOVES);
  }

  /**
   * Constructeur pour un Roi avec la couleur donnée, la position donnée
   * et les pièces pouvant être utilisées pour le roque.
   *
   * @param color          la couleur du Roi
   * @param posX           la position x du Roi
   * @param posY           la position y du Roi
   * @param castlingPieces les pièces pouvant être utilisées pour le roque
   */
  public King(PlayerColor color, int posX, int posY, CastlingPiece... castlingPieces) {
    this(color, posX, posY);
    this.castlingPieces.addAll(Arrays.asList(castlingPieces));
  }

  /**
   * Vérifie si le déplacement est un mouvement de roque.
   * Ne vérifie que si la longueur du déplacement est égale à celle requise.
   *
   * @param to le point de destination
   * @return vrai si le déplacement est un roque, faux sinon
   */
  public boolean isCastling(Point to) {
    return (to.x() == getX() + LENGTH_CASTLING || to.x() == getX() - LENGTH_CASTLING);
  }

  /**
   * Vérifie si le roque est possible. Cette pièce doit pouvoir effectuer un
   * mouvement de roque et la pièce de roque doit également le permettre.
   *
   * @param board le plateau de jeu
   * @param to    le point de destination
   * @return vrai si le roque est possible, faux sinon
   */
  private boolean castlingCanBeDone(Board board, Point to) {
    ChessPiece p = board.getPiece(getCastlingPiecePos(to));
    Direction moveDirection = availableMove(to);
    boolean cannotCastle = null == p || null == moveDirection
        || p.availableMove(to) != moveDirection.opposite()
        || !isSameColor(p)
        || !canCastle()
        || !pathIsClear(board, availableMove(to), getPos(), p.getPos())
        || pathIsInCheck(board, to);

    if (cannotCastle) {
      return false;
    }

    CastlingPiece cPiece = pieceIsPossibleCastlingPiece(p);
    return null != cPiece && cPiece.canCastle();
  }

  /**
   * Obtient la position de la pièce de roque. Le roque peut être effectué
   * uniquement si la pièce de roque est sur la même ligne que la position
   * initiale du Roi et dans la première ou dernière colonne du plateau.
   *
   * @param to le point de destination
   * @return la position de la pièce de roque
   */
  public Point getCastlingPiecePos(Point to) {
    int castlingWithX = getX() - to.x() > 0 ? 0 : Board.BOARD_SIZE - 1;
    return new Point(castlingWithX, getY());
  }

  /**
   * Vérifie si une pièce est une pièce de roque valide.
   *
   * @param piece la pièce à vérifier
   * @return la pièce de roque si elle est valide, sinon null
   */
  private CastlingPiece pieceIsPossibleCastlingPiece(ChessPiece piece) {
    for (CastlingPiece castlingPiece : castlingPieces) {
      if (castlingPiece.equals(piece)) {
        return castlingPiece;
      }
    }
    return null;
  }

  /**
   * Récupère la liste des pièces mettant ce Roi en échec.
   *
   * @return la liste des pièces mettant ce Roi en échec. Une liste vide si ce n'est pas le cas.
   */
  public List<ChessPiece> getInCheckBy() {
    return Collections.unmodifiableList(inCheckBy);
  }

  /**
   * Ajoute une pièce à la liste des pièces mettant ce Roi en échec.
   *
   * @param piece la pièce à ajouter
   */
  public void addInCheckBy(ChessPiece piece) {
    Assertions.assertTrue(
        !isSameColor(piece),
        "La pièce doit être de couleur opposée");
    inCheckBy.add(piece);
  }

  /**
   * Vérifie si le Roi est en échec.
   *
   * @return vrai si le Roi est en échec, faux sinon
   */
  public boolean isInCheck() {
    return inCheckBy.size() != 0;
  }

  /**
   * Supprime toutes les pièces mettant ce Roi en échec.
   */
  public void clearInCheckBy() {
    inCheckBy.clear();
  }

  /**
   * Vérifie si la pièce peut atteindre une position donnée sur le plateau
   * depuis sa position actuelle avec un déplacement donné. Vérifie aussi
   * si le point de destination n'est pas en échec.
   *
   * @param board le plateau de jeu
   * @param dest  le point de destination
   * @param move  le déplacement à utiliser
   * @return vrai si la pièce peut atteindre la destination, faux sinon
   */
  @Override
  protected boolean canReach(Board board, Point dest, Direction move) {
    return super.canReach(board, dest, move) && !destIsInCheck(board, dest);
  }

  /**
   * Vérifie si le Roi peut se déplacer vers une position donnée sur le plateau.
   *
   * @param board le plateau de jeu
   * @param dest  le point de destination
   * @return vrai si le Roi peut se déplacer à la destination, faux sinon
   */
  @Override
  public boolean canMoveTo(Board board, Point dest) {
    return super.canMoveTo(board, dest)
        || (Board.isInBoard(dest) && isCastling(dest) && castlingCanBeDone(board, dest));
  }

  /**
   * Obtient la distance maximale de déplacement du Roi.
   *
   * @return la distance maximale de déplacement du Roi
   */
  @Override
  protected int possibleLengthDistance() {
    return MAX_LENGTH_MOVE;
  }

  /**
   * Vérifie si le Roi peut effectuer un roque.
   *
   * @return vrai si le Roi peut effectuer un roque, faux sinon
   */
  @Override
  public boolean canCastle() {
    return !hasMoved() && !isInCheck();
  }

  /**
   * Vérifie si le Roi attaque une position donnée sur le plateau.
   *
   * @param board le plateau de jeu
   * @param dest  le point de destination
   * @return vrai si le Roi attaque cette position, faux sinon
   */
  @Override
  public boolean isAttacking(Board board, Point dest) {
    return super.canReach(board, dest, availableMove(dest));
  }

  /**
   * Vérifie si une position donnée est en échec.
   *
   * @param board le plateau de jeu
   * @param to    le point de destination
   * @return vrai si la position est en échec, faux sinon
   */
  private boolean destIsInCheck(Board board, Point to) {
    List<ChessPiece> enemies = board.getAllPieces(getPlayerColor().opposite());
    Direction movingDirection = Direction.offSetOf(getPos(), to);
    for (ChessPiece e : enemies) {
      Direction attackingDirection = e.availableMove(to);
      if (e.isAttacking(board, to) || isInCheck() && inCheckBy.contains(e)
          && null != attackingDirection && attackingDirection.equals(movingDirection)) {
        return true;
      }
    }

    return false;
  }

  /**
   * Vérifie si une pièce attaque une position sur le chemin du déplacement.
   *
   * @param board le plateau de jeu
   * @param to    le point de destination
   * @return vrai si une pièce attaque une position sur le chemin, faux sinon
   */
  private boolean pathIsInCheck(Board board, Point to) {
    Direction movingDirection = Direction.offSetOf(getPos(), to);
    Point currentPos = getPos();

    do {
      currentPos = currentPos.withAdded(movingDirection);
      if (destIsInCheck(board, currentPos)) {
        return true;
      }
    } while (!currentPos.equals(to));

    return false;
  }
}
