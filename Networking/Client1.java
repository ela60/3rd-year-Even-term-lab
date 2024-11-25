import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class Client1 {
    public static void main(String[] args) throws Exception {
        Socket s = new Socket("localhost", 7777);
        System.out.println("Connected to the server.");

        DataInputStream dis = new DataInputStream(s.getInputStream());
        DataOutputStream dos = new DataOutputStream(s.getOutputStream());
        Scanner sc = new Scanner(System.in);

        String msg;

        do {
            System.out.print("Enter a command (hi, date, time, ip, quit): ");
            msg = sc.nextLine().trim(); 
            dos.writeUTF(msg); 
            dos.flush(); 

            String serverResponse = dis.readUTF(); 
            System.out.println("Server: " + serverResponse);

        } while (!msg.equalsIgnoreCase("quit")); 

        System.out.println("Disconnected from server.");
        dis.close();
        dos.close();
        s.close();
        sc.close();
    }
}
