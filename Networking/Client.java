import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) throws IOException {
        Socket socket = new Socket("localhost", 7777);
        System.out.println("Connected to server.");

        DataInputStream dis = new DataInputStream(socket.getInputStream());
        DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
        Scanner sc = new Scanner(System.in);

        String message;
        while (true) {
            System.out.print("Enter command (Hi, Date, Time, IP, quit): ");
            message = sc.nextLine();
            dos.writeUTF(message);
            dos.flush();

            if (message.equalsIgnoreCase("quit")) break;

            String serverResponse = dis.readUTF();
            System.out.println("Server: " + serverResponse);
        }
        sc.close();
        dis.close();
        dos.close();
        socket.close();
    }
}
