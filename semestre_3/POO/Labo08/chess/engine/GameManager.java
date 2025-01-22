package chess.engine;

import chess.ChessController;
import chess.ChessView;
import chess.ChessView.UserChoice;
import chess.PlayerColor;
import chess.engine.piece.*;
import chess.engine.util.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Classe représentant le moteur de jeu utilisé pour contrôler une partie
 * d'échecs du début à la fin.
 */
public class GameManager implements ChessController {

    private Map<ChessPiece, List<Point>> mandatoryAdversaryMoves = new HashMap<>();
    protected final Board board = new Board();
    protected ChessView chessView;
    private int turn;

    /**
     * Constructeur pour un nouveau GameManager dans l'état initial d'une partie
     * d'échecs.
     */
    public GameManager() {
    }

    @Override
    public void newGame() {
        board.reset();
        mandatoryAdversaryMoves.clear();
        turn = 0;

        if (null != chessView) {
            insertPiecesInView();
        }
    }

    @Override
    public void start(ChessView view) {
        Assertions.assertNotNull(view, "View must not be null");
        chessView = view;

        insertPiecesInView();
        chessView.startView();
    }

    @Override
    public boolean move(int fromX, int fromY, int toX, int toY) {
        Assertions.assertTrue(
                Board.isInBoard(fromX, fromY) && Board.isInBoard(toX, toY),
                "Invalid move");

        Point from = new Point(fromX, fromY);
        Point to = new Point(toX, toY);
        ChessPiece piece = board.getPiece(from);

        if (!movePreconditions(piece, to)) {
            return false;
        }

        boolean specialMove = executeSpecialMoves(piece, to);
        movePiece(piece, to);
        promoteIfNeeded(piece);
        if (!specialMove) {
            board.setLastMove(from, piece.getPos());
        }

        postMoveActions();
        return true;
    }

    /**
     * Méthode utilisée pour vérifier les préconditions du déplacement souhaité
     * et retourne vrai si le déplacement est valide.
     *
     * @param piece La pièce à déplacer
     * @param to La destination
     * @return Vrai si le déplacement est valide, faux sinon
     */
    private boolean movePreconditions(ChessPiece piece, Point to) {
        return null != piece
                && !piece.getPos().equals(to)
                && piece.getPlayerColor().equals(playerTurn())
                && piece.canMoveTo(board, to)
                && (!board.getKing(piece.getPlayerColor()).isInCheck()
                || mandatoryAdversaryMoves.get(piece).contains(to));
    }

    /**
     * Méthode utilisée pour retirer une pièce de l'échiquier et de la vue des
     * échecs.
     *
     * @param p La pièce à retirer
     */
    protected void removePiece(ChessPiece p) {
        board.removePiece(p);
        chessView.removePiece(p.getX(), p.getY());
    }

    /**
     * Méthode utilisée pour insérer une pièce sur l'échiquier et dans la vue
     * des échecs.
     *
     * @param p La pièce à insérer
     */
    protected void insertPiece(ChessPiece p) {
        board.addPiece(p);
        chessView.putPiece(p.getPieceType(), p.getPlayerColor(), p.getX(), p.getY());
    }

    /**
     * Méthode utilisée pour effectuer des actions après un déplacement.
     */
    private void postMoveActions() {
        boolean check = checkIfAdversaryKingIsInCheck();
        boolean checkMate = !mandatoryAdversaryMoves.isEmpty()
                && mandatoryAdversaryMoves.values().stream().allMatch(List::isEmpty);
        boolean impossibleToCheckMate = isInsufficientMaterial();
        boolean stalemate = isStalemate();
        displayMessages(checkMate, check, stalemate, impossibleToCheckMate);

        if (!checkMate && !impossibleToCheckMate && !stalemate) {
            turn++;
        }

        postGameActions(checkMate, stalemate, impossibleToCheckMate);
    }

    /**
     * Méthode utilisée pour afficher des messages après le déplacement à l'aide
     * de la vue des échecs.
     *
     * @param checkMate indique si le roi adverse est en échec et mat
     * @param check indique si le roi adverse est en échec
     * @param stalemate indique s'il y a une situation de pat
     * @param impossibleToCheckMate indique s'il y a impossibilité de réaliser
     * un échec et mat
     */
    private void displayMessages(
            boolean checkMate,
            boolean check,
            boolean stalemate,
            boolean impossibleOfCheckMate) {
        if (checkMate) {
            chessView.displayMessage(ChessString.CHECKMATE);
            return;
        }

        if (check) {
            chessView.displayMessage(ChessString.CHECK);
            return;
        }

        if (stalemate) {
            chessView.displayMessage(ChessString.STALEMATE);
            return;
        }

        if (impossibleOfCheckMate) {
            chessView.displayMessage(ChessString.INSUFFICIENT_MATERIAL);
            return;
        }

        chessView.displayMessage(ChessString.playerToMove(playerTurn().opposite()));
    }

    /**
     * Méthode utilisée pour effectuer des actions après un échec et mat ou un
     * pat.
     *
     * @param checkMate indique si le roi adverse est en échec et mat
     * @param pat indique s'il y a une situation de pat
     * @param impossibleOfCheckMate indique s'il y a une impossibilité de
     * réaliser un échec et mat
     */
    private void postGameActions(boolean checkMate, boolean pat, boolean impossibleOfCheckMate) {
        if (!checkMate && !pat && !impossibleOfCheckMate) {
            return;
        }

        String header = checkMate
                ? ChessString.playerWins(playerTurn())
                : (pat ? ChessString.STALEMATE : ChessString.INSUFFICIENT_MATERIAL);
        String[] options = {ChessString.YES, ChessString.NO};
        UserChoice[] choices = new UserChoice[options.length];

        for (int i = 0; i < choices.length; i++) {
            int finalI = i;
            choices[finalI] = () -> options[finalI];
        }

        UserChoice choice = chessView.askUser(header, ChessString.PLAY_AGAIN_QUESTION, choices);
        if (null != choice && choice.equals(choices[0])) {
            clearView();
            newGame();
            chessView.displayMessage(ChessString.NEW_GAME);
        }
    }

    /**
     * Méthode utilisée pour vider la vue des échecs. Cette méthode est
     * uniquement utilisée lorsque la partie est terminée.
     */
    private void clearView() {
        for (int i = 0; i < Board.BOARD_SIZE; i++) {
            for (int j = 0; j < Board.BOARD_SIZE; j++) {
                chessView.removePiece(i, j);
            }
        }
    }

    /**
     * Méthode utilisée pour vérifier s'il y a une promotion et promouvoir la
     * pièce si nécessaire.
     *
     * @param piece La pièce qui a été déplacée
     */
    private void promoteIfNeeded(ChessPiece piece) {
        List<PromotablePiece> promotablePieces = board.getPromotablePieces();
        for (PromotablePiece promotablePiece : promotablePieces) {
            if (promotablePiece.equals(piece) && promotablePiece.canPromote()) {
                promote(piece);
            }
        }
    }

    /**
     * Vérifie si le roi adverse est en échec. Cela peut être un échec découvert
     * ou un échec positionnel, ou les deux. Si le roi est en échec, la méthode
     * met également à jour la carte des coups obligatoires adverses avec les
     * déplacements possibles pour éviter l'échec.
     *
     * @return Vrai si le roi est en échec, faux sinon
     */
    private boolean checkIfAdversaryKingIsInCheck() {
        ChessPiece movedPiece = board.getPiece(board.getLastMoveTo());
        King adversaryKing = board.getKing(movedPiece.getPlayerColor().opposite());
        if (isAPositionalCheck(adversaryKing, movedPiece)
                || isDiscoveredCheck(adversaryKing, board.getLastMoveFrom())) {
            mandatoryAdversaryMoves = getMovesToAvoidCheck(adversaryKing);
            return true;
        }

        return false;
    }

    /**
     * Vérifie si le roi adverse est en échec en raison de la pièce déplacée. Si
     * tel est le cas, la pièce est ajoutée à la liste inCheckBy du roi adverse.
     *
     * @param adversaryKing Le roi adverse
     * @param movedPiece La pièce qui a été déplacée
     * @return Vrai si le roi est en échec, faux sinon
     */
    private boolean isAPositionalCheck(King adversaryKing, ChessPiece movedPiece) {
        if (!movedPiece.isAttacking(board, adversaryKing.getPos())) {
            return false;
        }

        adversaryKing.addInCheckBy(movedPiece);
        return true;
    }

    /**
     * Vérifie si le roi adverse est en échec en raison d'un mouvement
     * découvert.
     *
     * @param adversaryKing Le roi adverse
     * @param oldPos L'ancienne position de la pièce déplacée
     * @return Vrai si le roi est en échec, sinon faux
     */
    private boolean isDiscoveredCheck(King adversaryKing, Point oldPos) {
        Direction attackDir = Direction.offSetOf(adversaryKing.getPos(), oldPos);
        if (attackDir == null) {
            return false;
        }

        Point attackerPos = oldPos.withAdded(attackDir);
        while (Board.isInBoard(attackerPos) && !board.isOccupied(attackerPos)) {
            attackerPos = attackerPos.withAdded(attackDir);
        }

        if (!Board.isInBoard(attackerPos)) {
            return false;
        }

        ChessPiece attacker = board.getPiece(attackerPos);
        if (attacker != null && !attacker.isSameColor(adversaryKing)
                && attacker.isAttacking(board, adversaryKing.getPos())) {
            adversaryKing.addInCheckBy(attacker);
            return true;
        }
        return false;
    }

    /**
     * Méthode utilisée pour créer une carte des pièces et de la liste des
     * déplacements pouvant éviter l'échec. Cette méthode est utilisée pour
     * trouver les déplacements obligatoires de l'adversaire pour éviter
     * l'échec.
     *
     * @param k Le roi qui est en échec
     * @return Une carte des pièces et de la liste des déplacements pouvant
     * éviter l'échec
     */
    private HashMap<ChessPiece, List<Point>> getMovesToAvoidCheck(King k) {
        List<ChessPiece> allies = board.getAllPieces(k.getPlayerColor());
        HashMap<ChessPiece, List<Point>> possibleMoves = new HashMap<>();
        allies.forEach(a -> possibleMoves.put(a, new ArrayList<>()));
        displacementMoves(k, possibleMoves);
        blockingMoves(k, possibleMoves, allies);
        capturingMoves(k, possibleMoves, allies);
        return possibleMoves;
    }

    /**
     * Méthode utilisée pour trouver les déplacements possibles que le roi peut
     * effectuer pour éviter l'échec.
     *
     * @param k Le roi qui est en échec
     * @param possibleMoves La carte des pièces et des déplacements pouvant
     * éviter l'échec
     */
    private void displacementMoves(King k, HashMap<ChessPiece, List<Point>> possibleMoves) {
        List<Direction> kingDirections = k.getDirections();
        for (Direction direction : kingDirections) {
            Point recheablePoint = k.getPos().withAdded(direction);
            if (k.canMoveTo(board, recheablePoint)) {
                possibleMoves.get(k).add(recheablePoint);
            }
        }
    }

    /**
     * Méthode utilisée pour vérifier s'il y a une situation de pat entre les
     * deux joueurs. Un pat se produit lorsque l'adversaire ne peut déplacer
     * aucune pièce et que le roi n'est pas en échec.
     *
     * @return True s'il y a une situation de pat, faux sinon
     */
    private boolean isStalemate() {
        King adversaryKing = board.getKing(playerTurn().opposite());
        if (!adversaryKing.isInCheck() && !canMove(adversaryKing)) {
            List<ChessPiece> allies = board.getAllPieces(adversaryKing.getPlayerColor());
            for (ChessPiece ally : allies) {
                if (canMove(ally)) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    /**
     * Méthode utilisée pour vérifier si les joueurs ne peuvent pas se faire
     * échec et mat entre eux. Cette méthode suit les règles de l'impossibilité
     * d'échec et mat.
     *
     * @return Vrai si les joueurs ne peuvent pas se faire échec et mat, faux
     * sinon
     */
    private boolean isInsufficientMaterial() {
        List<List<ChessPiece>> allPieces = board.getAllPieces();
        for (PlayerColor color : PlayerColor.values()) {
            if (allPieces.get(color.ordinal()).size() == 1) {
                if (allPieces.get(color.opposite().ordinal()).size() == 1) {
                    return true;
                }

                if (allPieces.get(color.opposite().ordinal()).size() > 1) {
                    return false;
                }

                long numberOfBishops = allPieces.get(color.opposite().ordinal()).stream()
                        .filter(piece -> piece instanceof Bishop)
                        .count();
                long numberOfKnights = allPieces.get(color.opposite().ordinal()).stream()
                        .filter(piece -> piece instanceof Knight)
                        .count();
                return numberOfBishops == 1 || numberOfKnights == 1;
            }

            if (allPieces.get(color.ordinal()).size() == 2
                    && allPieces.get(color.opposite().ordinal()).size() == 2) {
                Bishop b1 = (Bishop) allPieces.get(color.ordinal()).stream()
                        .filter(piece -> piece instanceof Bishop)
                        .findFirst().orElse(null);
                Bishop b2 = (Bishop) allPieces.get(color.opposite().ordinal()).stream()
                        .filter(piece -> piece instanceof Bishop)
                        .findFirst().orElse(null);
                return null != b1 && null != b2
                        && (((b1.getX() + b1.getY()) % 2) == ((b2.getX() + b2.getY()) % 2));
            }
        }

        return false;
    }

    /**
     * Méthode utilisée pour vérifier si une pièce peut effectuer un
     * déplacement.
     *
     * @param piece La pièce à vérifier
     * @return Vrai si la pièce peut effectuer un déplacement, faux sinon
     */
    private boolean canMove(ChessPiece piece) {
        List<Direction> pieceDirections = piece.getDirections();
        for (Direction direction : pieceDirections) {
            Point recheablePoint = piece.getPos().withAdded(direction);
            if (piece.canMoveTo(board, recheablePoint)) {
                return true;
            }
        }

        return false;
    }

    /**
     * Méthode utilisée pour trouver les déplacements possibles permettant de
     * capturer la pièce qui met le roi en échec.
     *
     * @param king Le roi qui est en échec
     * @param possibleMoves La carte des pièces et des déplacements pouvant
     * éviter l'échec
     * @param allies La liste des alliés du roi
     */
    private void capturingMoves(
            King king,
            HashMap<ChessPiece, List<Point>> possibleMoves,
            List<ChessPiece> allies) {
        // Impossible to avoid double check capturing two pieces at the same time
        if (king.getInCheckBy().size() != 1) {
            return;
        }

        for (ChessPiece ally : allies) {
            if (ally.canMoveTo(board, king.getInCheckBy().get(0).getPos())) {
                possibleMoves.get(ally).add(king.getInCheckBy().get(0).getPos());
            }
        }
    }

    /**
     * Méthode utilisée pour trouver les déplacements possibles permettant de
     * bloquer la pièce qui met le roi en échec.
     *
     * @param king Le roi qui est en échec
     * @param possibleMoves La carte des pièces et des déplacements pouvant
     * éviter l'échec
     * @param allies La liste des alliés du roi
     */
    private void blockingMoves(
            King king,
            HashMap<ChessPiece, List<Point>> possibleMoves,
            List<ChessPiece> allies) {

        // Si le roi n'est pas attaqué par une seule pièce, aucun mouvement de blocage n'est pertinent.
        if (king.getInCheckBy().size() != 1) {
            return;
        }

        ChessPiece attacker = king.getInCheckBy().get(0);
        Direction attackDir = Direction.offSetOf(king.getPos(), attacker.getPos());
        Point currentPos = king.getPos().withAdded(attackDir);

        // Parcours des positions sur la trajectoire de l'attaque.
        while (Board.isInBoard(currentPos) && !board.isOccupied(currentPos)) {
            for (ChessPiece ally : allies) {
                if (ally.canMoveTo(board, currentPos)) {
                    possibleMoves.computeIfAbsent(ally, k -> new ArrayList<>()).add(currentPos);
                }
            }
            currentPos = currentPos.withAdded(attackDir);
        }
    }

    /**
     * Met à jour la vue des échecs, l'échiquier et la position de la pièce. Si
     * le roi est en échec, cela efface les déplacements obligatoires puisque le
     * roi peut bouger pour éviter l'échec.
     *
     * @param p La pièce à déplacer
     * @param to La destination
     */
    private void movePiece(ChessPiece p, Point to) {
        removePiece(p);
        p.move(to);
        insertPiece(p);
        if (board.getKing(playerTurn()).isInCheck()) {
            mandatoryAdversaryMoves.clear();
            board.getKing(playerTurn()).clearInCheckBy();
        }
    }

    /**
     * Méthode utilisée pour promouvoir une pièce. L'échiquier et la vue des
     * échecs sont mis à jour.
     *
     * @param piece La pièce à promouvoir
     */
    private void promote(ChessPiece piece) {
        int posX = piece.getX(), posY = piece.getY();
        PlayerColor color = piece.getPlayerColor();
        ChessPiece[] options = {
            new Queen(color, posX, posY), new Rook(color, posX, posY),
            new Bishop(color, posX, posY), new Knight(color, posX, posY)
        };
        ChessPiece choice = chessView.askUser(
                ChessString.PROMOTION, ChessString.CHOOSE_PROMOTION, options);
        removePiece(piece);
        insertPiece(choice);
    }

    /**
     * Méthode utilisée pour insérer les pièces de l'échiquier dans la vue
     * actuelle.
     */
    protected void insertPiecesInView() {
        for (PlayerColor color : PlayerColor.values()) {
            board.getAllPieces(color).forEach(piece -> chessView.putPiece(
                    piece.getPieceType(),
                    piece.getPlayerColor(),
                    piece.getX(),
                    piece.getY()));
        }
    }

    /**
     * Méthode utilisée pour exécuter des mouvements spéciaux comme le roque ou
     * la prise en passant, si le mouvement est valide. Retourne faux si le
     * mouvement n'est pas valide.
     *
     * @param piece La pièce déplacée
     * @param to La destination
     * @return Vrai si un mouvement spécial a été exécuté, faux sinon
     */
    private boolean executeSpecialMoves(ChessPiece piece, Point to) {
        return castlingMove(piece, to.x(), to.y()) || enPassantMove(piece, to);
    }

    /**
     * Méthode utilisée pour effectuer un mouvement de roque pour le roi et la
     * tour impliqués dans le roque. Si la pièce n'est pas un roi ou si le roque
     * est invalide, la méthode ne fait rien et retourne faux.
     *
     * @param piece La pièce déplacée (devrait être le roi)
     * @param toX La coordonnée x cible du roi
     * @param toY La coordonnée y cible du roi
     * @return Vrai si le mouvement de roque a été effectué, faux sinon
     */
    private boolean castlingMove(ChessPiece piece, int toX, int toY) {
        //Valider que la pièce est un roi et que le roque est possible
        if (!(piece instanceof King king) || !king.isCastling(new Point(toX, toY))) {
            return false;
        }

        int rookInitialX = king.getX() < toX ? Board.BOARD_SIZE - 1 : 0;
        int rookInitialY = king.getY();
        ChessPiece rook = board.getPiece(rookInitialX, rookInitialY);

        // Valider que la pièce est une tour et qu'elle est de la même couleur que le roi
        if (!(rook instanceof Rook) || !rook.getPlayerColor().equals(king.getPlayerColor())) {
            return false;
        }

        int rookNewX = toX > king.getX() ? toX - 1 : toX + 1;
        int rookNewY = king.getY();

        movePiece(king, new Point(toX, toY));
        movePiece(rook, new Point(rookNewX, rookNewY));

        return true;
    }

    /**
     * Méthode utilisée pour vérifier si le mouvement est un mouvement en
     * passant. Le mouvement doit être diagonal, le dernier mouvement de
     * l'adversaire doit être un double déplacement d'un pion, et la destination
     * doit correspondre à la position où le pion adverse aurait avancé d'une
     * case.
     *
     * @param piece La pièce déplacée
     * @param to La destination
     * @return Vrai si c'est un mouvement en passant, faux sinon
     */
    private boolean enPassantMove(ChessPiece piece, Point to) {
        if (!(piece instanceof Pawn) || !((Pawn) piece).isEnPassant(board, to)) {
            return false;
        }

        Pawn adversaryPawn = (Pawn) board.getPiece(board.getLastMoveTo());
        if (adversaryPawn != null) {
            removePiece(adversaryPawn);
            board.setLastMove(adversaryPawn.getPos(), to);
        }
        return true;
    }

    /**
     * Méthode utilisée pour obtenir le tour actuel.
     *
     * @return La couleur du joueur dont c'est le tour
     */
    protected PlayerColor playerTurn() {
        return turn % 2 == 0 ? PlayerColor.WHITE : PlayerColor.BLACK;
    }
}
