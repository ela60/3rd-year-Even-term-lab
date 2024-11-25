import java.io.*;
import java.net.*;
import java.time.LocalDate;
import java.time.LocalTime;

public class Server {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(7777);
        System.out.println("Server is waiting for a connection...");
        Socket socket = serverSocket.accept();
        System.out.println("Client connected.");

        DataInputStream dis = new DataInputStream(socket.getInputStream());
        DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

        String clientMessage;
        while (true) {
            clientMessage = dis.readUTF();
            System.out.println("Client: " + clientMessage);

            if (clientMessage.equalsIgnoreCase("Hi")) {
                dos.writeUTF("Hello");
            } else if (clientMessage.equalsIgnoreCase("Date")) {
                dos.writeUTF("Server Date: " + LocalDate.now());
            } else if (clientMessage.equalsIgnoreCase("Time")) {
                dos.writeUTF("Server Time: " + LocalTime.now());
            } else if (clientMessage.equalsIgnoreCase("IP")) {
                dos.writeUTF("Server IP: " + InetAddress.getLocalHost().getHostAddress());
            } else if (clientMessage.equalsIgnoreCase("quit")) {
                dos.writeUTF("Goodbye!");
                break;
            } else {
                dos.writeUTF("Unknown command.");
            }
        }
        dis.close();
        dos.close();
        socket.close();
        serverSocket.close();
    }
}
