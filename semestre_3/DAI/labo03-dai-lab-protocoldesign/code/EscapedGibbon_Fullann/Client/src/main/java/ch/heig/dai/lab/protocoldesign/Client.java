package ch.heig.dai.lab.protocoldesign;

import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Client {
    private final String SERVER_ADDRESS = "127.0.0.1";
    private final int SERVER_PORT = 1234;

    public static void main(String[] args) {
        // Create a new client and run it
        Client client = new Client();
        client.run();
    }

    private void run() {
        try (Socket socket = new Socket(SERVER_ADDRESS, SERVER_PORT);
             BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
             Scanner scanner = new Scanner(System.in)) {

            // Read and display the welcome message from the server
            String serverMessage = in.readLine();
            System.out.println("Server: " + serverMessage);

            // Optionally, request HELP information at startup
            out.println("HELP");
            printMultilineResponse(in);

            // Main loop for sending commands to the server
            while (true) {
                System.out.print("Enter command (or type 'EXIT' to quit): ");
                String userInput = scanner.nextLine();

                // Allow user to exit
                if (userInput.equalsIgnoreCase("exit")) {
                    System.out.println("Closing client connection.");
                    break;
                }

                // Send the user's input to the server
                out.println(userInput);

                // Read and display the server's response
                printMultilineResponse(in);
            }

        } catch (UnknownHostException e) {
            System.err.println("Unknown host: " + SERVER_ADDRESS);
        } catch (IOException e) {
            System.err.println("I/O error with server connection: " + e.getMessage());
        }
    }

    /**
     * Reads and prints multiline responses from the server until an <END> marker is received.
     * This handles cases where the server sends multiple lines, such as HELP command.
     */
    private void printMultilineResponse(BufferedReader in) throws IOException {
        String responseLine;
        while ((responseLine = in.readLine()) != null) {
            if (responseLine.equals("<END>")) {
                break;  // End of the multiline message
            }
            System.out.println("Server: " + responseLine);
        }
    }
}
