package chess.engine.util;

import chess.PlayerColor;
import chess.engine.piece.*;
import java.util.*;

/**
 * Classe représentant un plateau de jeu.
 */
public class Board {

    public static final int BOARD_SIZE = 8;

    private final ChessPiece[][] pieces = new ChessPiece[BOARD_SIZE][BOARD_SIZE];
    private final List<PromotablePiece> promotablePieces = new LinkedList<>();
    private final King[] kings = new King[PlayerColor.values().length];
    private final Point[] lastMove = new Point[2];

    /**
     * Constructeur pour un plateau de jeu.
     */
    public Board() {
        fillBoard();
    }

    /**
     * Réinitialise le plateau de jeu.
     */
    public void reset() {
        for (ChessPiece[] row : pieces) {
            Arrays.fill(row, null);
        }

        Arrays.fill(kings, null);
        Arrays.fill(lastMove, null);
        promotablePieces.clear();
        fillBoard();
    }

    /**
     * Récupère une pièce à une position donnée.
     * 
     * @param pos La position de la pièce.
     * @return La pièce à la position donnée.
     */
    public ChessPiece getPiece(Point pos) {
        return getPiece(pos.x(), pos.y());
    }

    /**
     * Récupère une pièce à des coordonnées données.
     * 
     * @param x La coordonnée x.
     * @param y La coordonnée y.
     * @return La pièce aux coordonnées données.
     */
    public ChessPiece getPiece(int x, int y) {
        Assertions.assertTrue(isInBoard(x, y), "Position hors du plateau");
        return this.pieces[x][y];
    }

    /**
     * Définit le dernier déplacement effectué.
     * 
     * @param from La position de départ.
     * @param to   La position d'arrivée.
     */
    public void setLastMove(Point from, Point to) {
        Assertions.assertTrue(
            isInBoard(from) && isInBoard(to),
            "Position hors du plateau");
        this.lastMove[0] = from;
        this.lastMove[1] = to;
    }

    /**
     * Retourne la position de départ du dernier déplacement.
     * 
     * @return La position de départ, ou null si aucun déplacement n'a été effectué.
     */
    public Point getLastMoveFrom() {
        return this.lastMove[0];
    }

    /**
     * Retourne la position d'arrivée du dernier déplacement.
     * 
     * @return La position d'arrivée, ou null si aucun déplacement n'a été effectué.
     */
    public Point getLastMoveTo() {
        return this.lastMove[1];
    }

    /**
     * Vérifie si une position est occupée par une pièce.
     * 
     * @param p La position à vérifier.
     * @return True si la position est occupée, sinon false.
     */
    public boolean isOccupied(Point p) {
        return isInBoard(p) && null != getPiece(p);
    }

    /**
     * Vérifie si une position est dans les limites du plateau.
     * 
     * @param p La position à vérifier.
     * @return True si la position est dans les limites, sinon false.
     */
    public static boolean isInBoard(Point p) {
        return p.x() >= 0 && p.x() < BOARD_SIZE && p.y() >= 0 && p.y() < BOARD_SIZE;
    }

    /**
     * Vérifie si des coordonnées sont dans les limites du plateau.
     * 
     * @param x La coordonnée x.
     * @param y La coordonnée y.
     * @return True si les coordonnées sont dans les limites, sinon false.
     */
    public static boolean isInBoard(int x, int y) {
        return isInBoard(new Point(x, y));
    }

    /**
     * Ajoute une pièce au plateau. Remplace toute pièce existante à la position.
     * 
     * @param piece La pièce à ajouter.
     */
    public void addPiece(ChessPiece piece) {
        Assertions.assertNotNull(piece, "La pièce ne peut pas être nulle");
        Assertions.assertTrue(isInBoard(piece.getPos()), "Position invalide");
        this.pieces[piece.getX()][piece.getY()] = piece;
    }

    /**
     * Supprime une pièce du plateau.
     * 
     * @param piece La pièce à supprimer.
     */
    public void removePiece(ChessPiece piece) {
        Assertions.assertTrue(
            getPiece(piece.getPos()).equals(piece),
            "La pièce n'est pas sur le plateau");

        this.pieces[piece.getX()][piece.getY()] = null;
    }

    /**
     * Retourne le roi d'une couleur donnée.
     * 
     * @param color La couleur du roi.
     * @return Le roi de la couleur donnée.
     */
    public King getKing(PlayerColor color) {
        for (King king : kings) {
            if (king.getPlayerColor() == color) {
                return king;
            }
        }

        return null;
    }

    /**
     * Remplit le plateau avec les pièces initiales.
     */
    private void fillBoard() {
        for (PlayerColor color : PlayerColor.values()) {
            int line = color == PlayerColor.WHITE ? 0 : BOARD_SIZE - 1;
            int pawnLine = color == PlayerColor.WHITE ? line + 1 : line - 1;

            addPiece(new Rook(color, 0, line));
            addPiece(new Rook(color, 7, line));
            addPiece(new Knight(color, 1, line));
            addPiece(new Knight(color, 6, line));
            addPiece(new Bishop(color, 2, line));
            addPiece(new Bishop(color, 5, line));
            addPiece(new Queen(color, 3, line));

            King king = new King(color, 4, line);
            addPiece(king);

            for (int j = 0; j < BOARD_SIZE; j++) {
                Pawn pawn = new Pawn(color, j, pawnLine);
                addPiece(pawn);
                promotablePieces.add(pawn);
            }

            kings[color.ordinal()] = king;
        }
    }

    /**
     * Retourne toutes les pièces d'une couleur donnée.
     * 
     * @param playerTurn La couleur des pièces à retourner.
     * @return La liste des pièces de la couleur donnée.
     */
    public List<ChessPiece> getAllPieces(PlayerColor playerTurn) {
        ArrayList<ChessPiece> playerPieces = new ArrayList<>();
        for (ChessPiece[] row : pieces) {
            for (ChessPiece piece : row) {
                if (piece != null && piece.getPlayerColor() == playerTurn) {
                    playerPieces.add(piece);
                }
            }
        }

        return playerPieces;
    }

    /**
     * Retourne la liste des pièces pouvant être promues.
     * 
     * @return Une liste non modifiable des pièces pouvant être promues.
     */
    public List<PromotablePiece> getPromotablePieces() {
        return Collections.unmodifiableList(promotablePieces);
    }

    /**
     * Retourne toutes les pièces de toutes les couleurs.
     * 
     * @return Une liste de listes contenant toutes les pièces de toutes les couleurs.
     */
    public List<List<ChessPiece>> getAllPieces() {
        List<List<ChessPiece>> allPieces = new ArrayList<>();
        for (PlayerColor color : PlayerColor.values()) {
            allPieces.add(getAllPieces(color));
        }
        return allPieces;
    }
}
