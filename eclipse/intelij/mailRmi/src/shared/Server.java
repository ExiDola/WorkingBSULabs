package shared;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.List;

public interface Server extends Remote {
    public boolean addUser(String nickname) throws RemoteException;
    public void deleteUser(String nickname) throws RemoteException;

    public List<String> getListOfUsers() throws RemoteException;

    public boolean checkUser(String username) throws RemoteException;

    public int getMessagesCount(String nickname) throws RemoteException;
    public void sendMessage(Message msg) throws RemoteException;

    public ArrayList<Message> showMail(String nickname) throws RemoteException;
}