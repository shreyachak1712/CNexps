import java.io.*;
import java.net.*;

public class MyClient {
    public static void main(String[] args) {
        try (Socket socket = new Socket("localhost", 6666)) {
            System.out.println("Connected to the server");

            // Create input and output streams
            DataInputStream dis = new DataInputStream(socket.getInputStream());
            DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

            // Create threads for reading and writing messages
            Thread readThread = new Thread(() -> {
                try {
                    String msg;
                    while (true) {
                        msg = dis.readUTF();
                        System.out.println("Server: " + msg);
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
