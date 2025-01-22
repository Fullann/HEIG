package chess;

import chess.engine.GameManager;
import chess.views.console.ConsoleView;
import chess.views.gui.GUIView;

public final class Main {

    public static void main(String[] args) {
        boolean useGUI = args.length > 0 && "-g".equals(args[0]);

        ChessController controller = new GameManager();
        ChessView view = useGUI ? new GUIView(controller) : new ConsoleView(controller);
        
        controller.start(view);
    }
}
