import java.io.*;
import java.net.*;

public class MyServer {
    public static void main(String[] args) {
        try (ServerSocket ss = new ServerSocket(6666)) {
            System.out.println("Server is listening on port 6666");
            Socket socket = ss.accept(); // Establish connection
            System.out.println("Client connected");

            // Create input and output streams
            DataInputStream dis = new DataInputStream(socket.getInputStream());
            DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

            // Create threads for reading and writing messages
            Thread readThread = new Thread(() -> {
                try {
                    String msg;
                    while (true) {
                        msg = dis.readUTF();
                        System.out.println("Client: " + msg);
                        if (msg.equalsIgnoreCase("bye")) {
                            break;
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });

            Thread writeThread = new Thread(() -> {
                try {
                    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
                    String msg;
                    while (true) {
                        msg = reader.readLine();
                        dos.writeUTF(msg);
                        dos.flush();
                        if (msg.equalsIgnoreCase("bye")) {
                            break;
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });

            // Start both threads
            readThread.start();
            writeThread.start();

            // Wait for both threads to finish
            readThread.join();
            writeThread.join();

            // Close resources
            dis.close();
            dos.close();
            socket.close();
            System.out.println("Chat ended.");
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}
