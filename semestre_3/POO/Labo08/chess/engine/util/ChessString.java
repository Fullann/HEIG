package chess.engine.util;

import chess.PlayerColor;

/**
 * Classe utilitaire pour les chaînes de caractères utilisées dans le jeu d'échecs.
 * 
 */
public final class ChessString {

  public static final String YES = "Yes";
  public static final String NO = "No";
  public static final String CHECK = "Check!";
  public static final String CHECKMATE = "Checkmate!";
  public static final String STALEMATE = "Stalemate!";
  public static final String INSUFFICIENT_MATERIAL = "Insufficient material!";
  public static final String PROMOTION = "Promote";
  public static final String PLAYER_MOVE = "to move";
  public static final String PLAYER_WINS = "wins";
  public static final String CHOOSE_PROMOTION = "To which piece do you want to promote?";
  public static final String PLAY_AGAIN_QUESTION = "Do you want to play again?";
  public static final String NEW_GAME = "New game";

  /**
   * Methode pour annoncer le joueur gagnant.
   * 
   * @param color La couleur du joueur gagnant.
   * @return Le message annonçant le joueur gagnant.
   */
  public static String playerWins(PlayerColor color) {
    return color.name() + " " + PLAYER_WINS;
  }

  /**
   * Methode pour annoncer le joueur qui doit jouer.
   * 
   * @param color La couleur du joueur qui doit jouer.
   * @return Le message annonçant le joueur qui doit jouer.
   */
  public static String playerToMove(PlayerColor color) {
    return color.name() + " " + PLAYER_MOVE;
  }

}
