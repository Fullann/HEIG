import java.io.*;
import java.net.*;

public class Server {

    // Constantes pour les opérations supportées
    private static final String WELCOME_MESSAGE = "Welcome! Type 'HELP' to see available commands and usage.";
    private static final int SERVER_PORT = 1234;

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(SERVER_PORT)) {
            System.out.println("Server is listening on port " + SERVER_PORT);

            while (true) {
                try (Socket socket = serverSocket.accept();
                     BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                     PrintWriter out = new PrintWriter(socket.getOutputStream(), true)) {

                    // Envoyer un message de bienvenue au client
                    out.println(WELCOME_MESSAGE);

                    String clientMessage;
                    while ((clientMessage = in.readLine()) != null) {
                        // Vérifier la commande de terminaison
                        if (clientMessage.trim().equalsIgnoreCase("EXIT")) {
                            out.println("Goodbye!");
                            break;
                        }

                        // Traiter le message du client
                        String response = processRequest(clientMessage);
                        sendMultilineResponse(out, response);
                    }
                } catch (IOException e) {
                    System.out.println("Client disconnected or error occurred: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            System.out.println("Error starting server: " + e.getMessage());
        }
    }

    /**
     * Traite la requête du client et retourne la réponse appropriée.
     */
    private static String processRequest(String request) {
        String[] tokens = request.trim().split("\\s+");
        if (tokens.length == 1 && tokens[0].equalsIgnoreCase("HELP")) {
            return getHelpMessage();
        }

        if (tokens.length < 2 || tokens.length > 3) {
            return "Error: Invalid format. Use <OPERATION> <OPERAND1> [OPERAND2]. Type 'HELP' for a list of commands.";
        }

        String operation = tokens[0].toUpperCase();
        double a;

        try {
            a = Double.parseDouble(tokens[1]);
            if (tokens.length == 2) {
                // Opérations à un seul opérande
                return "Result: " + calculate(operation, a);
            } else if (tokens.length == 3) {
                // Opérations à deux opérandes
                double b = Double.parseDouble(tokens[2]);
                return "Result: " + calculate(operation, a, b);
            }
        } catch (NumberFormatException e) {
            return "Error: Operands must be numeric.";
        } catch (IllegalArgumentException | UnsupportedOperationException e) {
            return "Error: " + e.getMessage();
        }

        return "Error: Invalid request format.";
    }

    /**
     * Calcule les opérations binaires
     */
    private static double calculate(String operation, double a, double b) {
        switch (operation) {
            case "ADD": return a + b;
            case "SUB": return a - b;
            case "MUL": return a * b;
            case "DIV":
                if (b == 0) throw new IllegalArgumentException("Division by zero");
                return a / b;
            case "POW": return Math.pow(a, b);
            case "MOD": return a % b;
            case "MAX": return Math.max(a, b);
            case "MIN": return Math.min(a, b);
            default: throw new UnsupportedOperationException("Unsupported operation");
        }
    }

    /**
     * Calcule les opérations unaires
     */
    private static double calculate(String operation, double a) {
        switch (operation) {
            case "EXP": return Math.exp(a);
            case "LN":
                if (a <= 0) throw new IllegalArgumentException("Natural logarithm requires positive numbers");
                return Math.log(a);
            case "SQRT":
                if (a < 0) throw new IllegalArgumentException("Cannot calculate square root of a negative number");
                return Math.sqrt(a);
            case "SIN": return Math.sin(a);
            case "COS": return Math.cos(a);
            case "TAN": return Math.tan(a);
            case "CEIL": return Math.ceil(a);
            case "FLOOR": return Math.floor(a);
            case "ABS": return Math.abs(a);
            case "ROUND": return Math.round(a);
            default: throw new UnsupportedOperationException("Unsupported operation");
        }
    }

    /**
     * Fournit le message d'aide en plusieurs lignes.
     */
    private static String getHelpMessage() {
        return "Available commands:\n\n" +
                "- ADD a b     : Adds two numbers (a + b).\n" +
                "- SUB a b     : Subtracts the second number from the first (a - b).\n" +
                "- MUL a b     : Multiplies two numbers (a * b).\n" +
                "- DIV a b     : Divides the first number by the second (a / b). The second number must not be zero.\n" +
                "- POW a b     : Raises the first number to the power of the second (a^b).\n" +
                "- MOD a b     : Returns the remainder when the first number is divided by the second (a % b).\n\n" +
                "- SQRT a      : Returns the square root of a. Only positive numbers are allowed.\n" +
                "- EXP a       : Returns e raised to the power of a (e^a).\n" +
                "- LN a        : Returns the natural logarithm (base e) of a. Only positive numbers are allowed.\n" +
                "- SIN a       : Returns the sine of a (a in radians).\n" +
                "- COS a       : Returns the cosine of a (a in radians).\n" +
                "- TAN a       : Returns the tangent of a (a in radians).\n\n" +
                "- ABS a       : Returns the absolute value of a.\n" +
                "- MAX a b     : Returns the maximum of two numbers.\n" +
                "- MIN a b     : Returns the minimum of two numbers.\n" +
                "- CEIL a      : Returns the smallest integer greater than or equal to a.\n" +
                "- FLOOR a     : Returns the largest integer less than or equal to a.\n" +
                "- ROUND a     : Rounds a to the nearest integer.\n\n" +
                "- HELP        : Displays this help message with explanations for each command.\n" +
                "- EXIT        : Closes the connection to the server.\n";
    }

    /**
     * Envoie une réponse multi-lignes au client, en ajoutant un marqueur <END> à la fin.
     */
    private static void sendMultilineResponse(PrintWriter out, String response) {
        String[] lines = response.split("\n");
        for (String line : lines) {
            out.println(line);
        }
        out.println("<END>");  // Marqueur de fin
    }
}
