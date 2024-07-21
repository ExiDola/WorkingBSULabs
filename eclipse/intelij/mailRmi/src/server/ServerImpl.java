package server;

import shared.Message;
import shared.Server;
import java.util.Scanner;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class ServerImpl extends UnicastRemoteObject implements Server {
    private HashMap<String, ArrayList<Message>> messagesToUser;

    public boolean work = true;
    public ServerImpl() throws RemoteException{
        super();
        messagesToUser = new HashMap<>();
    }

    @Override
    public synchronized boolean addUser(String nickname) throws RemoteException{
        if(messagesToUser.containsKey(nickname)){
            return false;
        }
        messagesToUser.put(nickname,new ArrayList<>());
        System.out.println("User " + nickname + " successfully added");
        return true;
    }
    @Override
    public synchronized void deleteUser(String nickname) throws RemoteException{
        messagesToUser.remove(nickname);
        System.out.println("User " + nickname + " successfully deleted");
    }
    @Override
    public synchronized List<String> getListOfUsers() throws RemoteException{
        List<String> keyList = new ArrayList<>(messagesToUser.keySet());
        return keyList;
    }

    @Override
    public synchronized boolean checkUser(String username) throws RemoteException{
        return messagesToUser.containsKey(username);
    }
    @Override
    public synchronized int  getMessagesCount(String nickname) throws RemoteException  {
        ArrayList<Message> messages = messagesToUser.get(nickname);
        if (messages != null) {
            return messages.size();
        } else {
            return 0;
        }
    }
    @Override
    public synchronized void sendMessage(Message msg) throws RemoteException{
        ArrayList<Message> userMessages = messagesToUser.get(msg.nameTo);
        userMessages.add(msg);
        messagesToUser.put(msg.nameTo,userMessages);
    }

    @Override
    public synchronized ArrayList<Message> showMail(String nickname) throws RemoteException{
        ArrayList<Message> messages = messagesToUser.get(nickname);
        messagesToUser.put(nickname,new ArrayList<>());
        return messages;
    }

    public static void main(String[] args) throws Exception {
        if(args.length!=1){
            System.err.println("Please check your input parameters");
            System.exit(0);
        }
        String localhost = args[0];
        String RMI_HOSTNAME = "java.rmi.server.hostname";

        try {
            System.setProperty(RMI_HOSTNAME, localhost);

            ServerImpl service = new ServerImpl();

            String serviceName = "Server";

            System.out.println("Initializing " + serviceName);

            Registry registry = LocateRegistry.createRegistry(8080);
            registry.rebind(serviceName, service);

            System.out.println("Start " + serviceName);
            System.out.println("Write 'q' to stop the server");

            Scanner scanner = new Scanner(System.in);
            String userInput;
            do {
                userInput = scanner.nextLine().trim().toLowerCase();

                if ("q".equals(userInput)) {
                    System.out.println("Stopping the server...");
                    registry.unbind(serviceName);
                    UnicastRemoteObject.unexportObject(service, true);
                    System.out.println("Server stopped.");
                } else {
                    System.out.println("Unknown command: " + userInput);
                }
            } while (!"q".equals(userInput));
        } catch (RemoteException e) {
            System.err.println("RemoteException: " + e.getMessage());
            System.exit(1);
        } catch (Exception e) {
            System.err.println("Exception: " + e.getMessage());
            System.exit(2);
        }
    }
}