package client;

import shared.Message;
import shared.Server;

import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Client
{
    String nickname;
    Server s;

    Scanner com;


    public Client(String nickname,String localhost)
    {
        this.nickname = nickname;
        com = new Scanner(System.in);
        try {
            Registry registry = LocateRegistry.getRegistry(localhost, 8080);
            String url = "Server";

            s = (Server) registry.lookup(url);

            if(s.addUser(nickname)){
                System.out.println("You authorized");
                System.out.println("Your nickName is:"+ this.nickname);
            }else{
                System.out.println("This nickname is already taken");
                System.exit(1);
            }
            processCommands();

        }catch (RemoteException e) {
            e.printStackTrace();
            System.exit(3);
        } catch (NotBoundException e) {
            System.err.println("NotBoundException : " +
                    e.getMessage());
            System.exit(4);
        }
    }
    private void printPrompt() {
        System.out.println();
        System.out.print("(q)uit/(m)ail/(u)sers/(l)etter/(f)ile >");
        System.out.flush();
    }

    private void processCommands() {
        String nameTo = "";

        printPrompt();
        while (true) {
            if (!com.hasNextLine()) {
                continue;
            }
            String command = com.nextLine();
            try {
                switch (command) {
                    case "q", "quit":
                        s.deleteUser(nickname);
                        System.out.println("Thank you for this session.See you soon");
                        System.exit(5);
                        break;
                    case "u","users":
                        System.out.println("Users:{");
                        for (String user:s.getListOfUsers()){
                            System.out.println(user);
                        }
                        System.out.println("}");
                        break;
                    case "l","letter":
                        System.out.println("Enter user nickname");
                        nameTo = com.nextLine();
                        if(s.checkUser(nameTo)){
                            if(s.getMessagesCount(nameTo)<10)
                            {
                                System.out.println("Enter message:");
                                String text = com.nextLine();
                                s.sendMessage(new Message(nickname,nameTo,text,false,null,""));
                                System.out.println("Message to user " + nameTo + "successfully send");
                            }
                            else
                            {
                                System.err.println("The user's mail is full, he should clean it up");
                            }
                        }else{
                            System.err.println("Incorrect username");
                        }
                        break;
                    case "f","file":
                        System.out.println("Enter user nickname");
                        nameTo = com.nextLine();
                        if(s.checkUser(nameTo)){
                            if(s.getMessagesCount(nameTo)<10) {
                                System.out.println("Enter filepath:");
                                String filePath = com.nextLine();
                                if (doesFileExist(filePath)) {
                                    s.sendMessage(new Message(nickname, nameTo, "", true, getFileBytes(new File(filePath)), (new File(filePath).getName())));
                                    System.out.println("Message to user " + nameTo + "successfully send");
                                } else {
                                    System.err.println("Incorrect filepath:");
                                }
                            }
                            else{
                                System.err.println("The user's mail is full, he should clean it up");
                            }

                        }else{
                            System.err.println("Incorrect username");
                        }
                        break;
                    case "m","mail":
                        ArrayList<Message> messages = s.showMail(nickname);
                        if(messages.isEmpty()){
                            System.out.println("No new messages");
                        }else{
                            System.out.println("New text/file messages{");
                            for(Message msg : messages){
                                if(!msg.isFile)
                                {
                                    System.out.println("From:" + msg.nameFrom);
                                    System.out.println("Text: " + msg.msg + "\n");
                                }else{
                                    System.out.println("From:" + msg.nameFrom);
                                    System.out.println("Filename: " + msg.filename + "\n");
                                    System.out.println("Do you want to download this file (y/n)?");
                                    if(com.nextLine().equals("y")){
                                        String userHome = System.getProperty("user.home");
                                        Path userDownloads = Path.of(userHome, "Downloads");

                                        Path targetPath = userDownloads.resolve(msg.filename);

                                        try {
                                            Files.write(targetPath, msg.fileMsg);
                                            System.out.println("File downloaded to: " + targetPath);
                                        } catch (Exception e) {
                                            System.err.println("Error downloading file: " + e.getMessage());
                                        }
                                    }
                                    else
                                    {
                                        System.out.println("File deleted");
                                    }
                                }
                            }
                            System.out.println("}\n");
                        }
                        break;
                    default:
                        System.out.println("Incorrect command");
                }
            }catch (RemoteException e){
                System.err.println(e);
                System.exit(6);
            }
            printPrompt();
        }
    }

    static boolean doesFileExist(String filePath) {
        File file = new File(filePath);
        if (!file.exists() || !file.isFile()) {
            return false;
        }
        return true;
    }

    static byte[] getFileBytes(File file) {
        try {
            Path path = file.toPath();
            return Files.readAllBytes(path);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void main(String[] args)
    {
        if(args.length != 2){
            System.err.println("Please check your input parameters");
            System.exit(0);
        }
        new Client(args[0],args[1]);
    }
}