import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

public class Server1 {
    public static void main(String[] args) throws Exception {
        ServerSocket ss = new ServerSocket(7777);
        System.out.println("Server is waiting for a connection...");
        Socket s = ss.accept();
        System.out.println("Client connected.");

        DataInputStream dis = new DataInputStream(s.getInputStream());
        DataOutputStream dos = new DataOutputStream(s.getOutputStream());

        String msg;

        do {
            msg = dis.readUTF().trim().toLowerCase(); 
            System.out.println("Client: " + msg);

            switch (msg) {
                case "hi":
                    dos.writeUTF("Hello! ");
                    break;
                case "date":
                    dos.writeUTF("Server Date: " + LocalDate.now());
                    break;
                case "time":
                    DateTimeFormatter dt = DateTimeFormatter.ofPattern("HH:mm");
                    String time = LocalTime.now().format(dt);
                    dos.writeUTF("Current time is: " + time);
                    break;
                case "ip":
                    dos.writeUTF("Server IP: " + InetAddress.getLocalHost().getHostAddress());
                    break;
                case "quit":
                    dos.writeUTF("Goodbye!");
                    break;
                default:
                    dos.writeUTF("Unknown command. Try 'hi', 'date', 'time', 'ip', or 'quit'.");
                    break;
            }
        } while (!msg.equals("quit")); 

        System.out.println("Server disconnected.");
        dis.close();
        dos.close();
        s.close();
        ss.close();
    }
}
