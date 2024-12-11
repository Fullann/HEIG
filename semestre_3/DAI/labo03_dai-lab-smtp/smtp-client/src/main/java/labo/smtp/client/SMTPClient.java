package labo.smtp.client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.Base64;

public class SMTPClient {

    private static final String CRLF = "\r\n";
    private String smtpServer;
    private int smtpPort;
    private Socket socket;
    private PrintWriter writer;
    private BufferedReader reader;

    public SMTPClient(String smtpServer, int smtpPort) {
        this.smtpServer = smtpServer;
        this.smtpPort = smtpPort;
    }

    public void connect() throws IOException {
        System.out.println("Connexion au serveur SMTP...");
        socket = new Socket(smtpServer, smtpPort);
        writer = new PrintWriter(new OutputStreamWriter(socket.getOutputStream(), StandardCharsets.UTF_8), true);
        reader = new BufferedReader(new InputStreamReader(socket.getInputStream(), StandardCharsets.UTF_8));
        System.out.println("Connecté au serveur SMTP.");
        readResponse(); // Lire la réponse initiale du serveur
    }

    public void disconnect() throws IOException {
        if (socket != null && !socket.isClosed()) {
            sendCommand("QUIT");
            System.out.println("Déconnexion du serveur SMTP...");
            socket.close();
            System.out.println("Déconnecté du serveur SMTP.");
        }
    }

    private String readResponse() throws IOException {
        String response = reader.readLine();
        System.out.println("SERVER: " + response);
        if (response.startsWith("4") || response.startsWith("5")) {
            throw new IOException("Erreur SMTP : " + response);
        }
        return response;
    }

    private void sendCommand(String command) throws IOException {
        writer.print(command + CRLF);
        writer.flush();
        System.out.println("CLIENT: " + command);
        readResponse();
    }

    public void sendEmail(Email email) throws IOException {
        sendCommand("EHLO localhost");

        sendCommand("MAIL FROM:<" + email.getSender() + ">");

        for (String recipient : email.getRecipients()) {
            sendCommand("RCPT TO:<" + recipient + ">");
        }

        sendCommand("DATA");

        // En-têtes MIME
        writer.print("Content-Type: text/plain; charset=utf-8" + CRLF);
        writer.print("From: " + email.getSender() + CRLF);
        writer.print("To: " + String.join(", ", email.getRecipients()) + CRLF);

        // Encodage Base64 pour l'objet
        String subjectEncoded = Base64.getEncoder().encodeToString(email.getSubject().getBytes(StandardCharsets.UTF_8));
        writer.print("Subject: =?utf-8?B?" + subjectEncoded + "?=" + CRLF);

        writer.print(CRLF); // Ligne vide entre les en-têtes et le corps
        writer.print(email.getBody() + CRLF);
        writer.print("." + CRLF); // Terminaison des données
        writer.flush();

        System.out.println("E-mail envoyé au serveur SMTP.");

        // Lire la réponse après l'envoi des données
        String response = readResponse();
        if (!response.startsWith("250")) {
            throw new IOException("Erreur lors de l'envoi du message : " + response);
        }
    }
}
