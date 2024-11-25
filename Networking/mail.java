import java.io.*;
import javax.net.ssl.*;
import java.util.*;

public class mail {
    private static DataOutputStream dos;
    public static BufferedReader br;

    public static void main(String[] args) throws Exception {
        String user = "19125@gmail.com"; // Your Gmail address
        String pass = "Ambiaela321@";   // App Password or your actual password (if 2FA disabled)

        String username = Base64.getEncoder().encodeToString(user.getBytes());
        String password = Base64.getEncoder().encodeToString(pass.getBytes());

        SSLSocket socket = (SSLSocket) SSLSocketFactory.getDefault().createSocket("smtp.gmail.com", 465);
        dos = new DataOutputStream(socket.getOutputStream());
        br = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        send("EHLO smtp.gmail.com\r\n");
        readServerResponse();
        
        send("AUTH LOGIN\r\n");
        readServerResponse();

        send(username + "\r\n");
        readServerResponse();

        send(password + "\r\n");
        readServerResponse();

        send("MAIL FROM:<19125@gmail.com>\r\n");
        readServerResponse();

        send("RCPT TO:<ambiaela7275@gmail.com>\r\n");
        readServerResponse();

        send("DATA\r\n");
        readServerResponse();

        send("Subject: Test Email\r\n");
        send("This is a test email.\r\n.\r\n");
        readServerResponse();

        send("QUIT\r\n");
        readServerResponse();
    }

    private static void send(String data) throws IOException {
        dos.writeBytes(data);
        dos.flush();
        System.out.println("CLIENT: " + data.trim());
    }

    private static void readServerResponse() throws IOException {
        String response;
        while ((response = br.readLine()) != null) {
            System.out.println("SERVER: " + response);
            if (!response.startsWith("250-") && !response.startsWith("220-") && !response.startsWith("334")) {
                break;
            }
        }
    }
}
