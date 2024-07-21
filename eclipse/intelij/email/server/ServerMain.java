package email.server;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.Vector;
import java.io.FileOutputStream;

import email.*;

public class ServerMain {

	private static int MAX_USERS = 100;

	public static void main(String[] args) {
		try (ServerSocket serverSocket = new ServerSocket(Protocol.PORT)) {
			System.err.println("Server initialized");
			ServerStopThread stopThread = new ServerStopThread();
			stopThread.start();

			while (!ServerMain.getStopFlag()) {
				Socket clientSocket = accept(serverSocket);
				if (clientSocket != null) {
					if (ServerMain.getNumUsers() < ServerMain.MAX_USERS) {
						System.err.println(clientSocket.getInetAddress().getHostName() + " connected");
						ServerThread serverThread = new ServerThread(clientSocket);
						serverThread.start();
					} else {
						System.err.println(clientSocket.getInetAddress().getHostName() + " connection rejected");
						clientSocket.close();
					}
				}
			}
		} catch (IOException e) {
			System.err.println(e);
		} finally {
			stopAllUsers();
			System.err.println("Server stopped");
		}
	}

	private static Socket accept(ServerSocket serverSocket) {
		assert (serverSocket != null);
		try {
			serverSocket.setSoTimeout(1000);
			return serverSocket.accept();
		} catch (IOException e) {
			return null;
		}
	}

	private static void stopAllUsers() {
		String[] users = getUsers();
		for (String user : users) {
			ServerThread userThread = getUser(user);
			if (userThread != null) {
				userThread.disconnect();
			}
		}
	}

	private static Object syncFlags = new Object();
	private static boolean stopFlag = false;
	public static boolean getStopFlag() {
		synchronized ( ServerMain.syncFlags ) {
			return stopFlag;
		}
	}
	public static void setStopFlag( boolean value ) {
		synchronized ( ServerMain.syncFlags ) {
			stopFlag = value;
		}
	}

	private static Object syncUsers = new Object();
	private static TreeMap<String, ServerThread> users =
			new TreeMap<String, ServerThread> ();

	public static ServerThread getUser( String userNic ) {
		synchronized (ServerMain.syncUsers) {
			return ServerMain.users.get( userNic );
		}
	}

	public static ServerThread registerUser( String userNic, ServerThread user )
	{
		synchronized (ServerMain.syncUsers) {
			ServerThread old = ServerMain.users.get( userNic );
			if ( old == null ) {
				ServerMain.users.put( userNic, user );
			}
			return old;
		}
	}

	public static ServerThread setUser( String userNic, ServerThread user ) {
		synchronized (ServerMain.syncUsers) {
			ServerThread res = ServerMain.users.put( userNic, user );
			if ( user == null ) {
				ServerMain.users.remove(userNic);
			}
			return res;
		}
	}

	public static String[] getUsers() {
		synchronized (ServerMain.syncUsers) {
			return ServerMain.users.keySet().toArray( new String[0] );
		}
	}

	public static int getNumUsers() {
		synchronized (ServerMain.syncUsers) {
			return ServerMain.users.keySet().size();
		}
	}
}

class ServerStopThread extends CommandThread {

	static final String cmd  = "q";
	static final String cmdL = "quit";

	Scanner fin;

	public ServerStopThread() {
		fin = new Scanner( System.in );
		ServerMain.setStopFlag( false );
		putHandler( cmd, cmdL, new CmdHandler() {
			@Override
			public boolean onCommand(int[] errorCode) {	return onCmdQuit(); }
		});
		this.setDaemon(true);
		System.err.println( "Enter \'" + cmd + "\' or \'" + cmdL + "\' to stop server\n" );
	}

	public void run() {

		while (true) {
			try {
				Thread.sleep( 1000 );
			} catch (InterruptedException e) {
				break;
			}
			if ( fin.hasNextLine()== false )
				continue;
			String str = fin.nextLine();
			if ( command( str )) {
				break;
			}
		}
	}

	public boolean onCmdQuit() {
		System.err.print("stop server...");
		fin.close();
		ServerMain.setStopFlag( true );
		return true;
	}
}

class ServerThread extends Thread {

	private Socket              sock;
	private ObjectOutputStream 	os;
	private ObjectInputStream 	is;
	private InetAddress 		addr;

	private String userNic = null;
	private String userFullName;

	private Object syncLetters = new Object();
	private Vector<String> letters = null;
	private Vector<MessageFile> files = null;
	private Object syncFiles = new Object();


	public void addLetter( String letter ) {
		synchronized ( syncLetters ) {
			if ( letters == null ) {
				letters = new Vector<String> ();
			}
			letters.add( letter );
		}
	}

	public void addFile(MessageFile file) {
		synchronized (syncFiles) {
			if (files == null) {
				files = new Vector<MessageFile>();
			}
			files.add(file);
		}
	}
	public String[] getLetters() {
		synchronized ( syncLetters ) {
			String[] lts = new String[0];
			synchronized ( syncLetters ) {
				if ( letters != null ) {
					lts = letters.toArray( lts );
					letters = null;
				}
			}
			return lts;
		}
	}

	public ServerThread(Socket s) throws IOException {
		sock = s;
		s.setSoTimeout(1000);
		os = new ObjectOutputStream( s.getOutputStream() );
		is = new ObjectInputStream( s.getInputStream());
		addr = s.getInetAddress();
		this.setDaemon(true);
	}

	public void run() {
		try {
			while ( true ) {
				Message msg = null;
				try {
					msg = ( Message ) is.readObject();
				} catch (IOException e) {
				} catch (ClassNotFoundException e) {
				}
				if (msg != null) switch ( msg.getID() ) {

					case Protocol.CMD_CONNECT:
						if ( !connect( (MessageConnect) msg ))
							return;
						break;

					case Protocol.CMD_DISCONNECT:
						return;

					case Protocol.CMD_USER:
						user(( MessageUser ) msg);
						break;

					case Protocol.CMD_CHECK_MAIL:
						checkMail(( MessageCheckMail ) msg );
						break;

					case Protocol.CMD_LETTER:
						letter(( MessageLetter ) msg );
						break;
					case Protocol.CMD_FILE:
						file(( MessageFile ) msg );
						break;
				}
			}
		} catch (IOException e) {
			System.err.print("Disconnect...");
		} finally {
			disconnect();
		}
	}

	boolean connect( MessageConnect msg ) throws IOException {

		ServerThread old = register( msg.userNic, msg.userFullName );
		if ( old == null )
		{
			os.writeObject( new MessageConnectResult());
			return true;
		} else {
			os.writeObject( new MessageConnectResult(
					"User " + old.userFullName + " already connected as " + userNic ));
			return false;
		}
	}

	void file(MessageFile msg) throws IOException {
		ServerThread user = ServerMain.getUser(msg.usrNic);
		System.out.println(msg.filename);
		if (msg.filename.isEmpty()) {
			os.writeObject(new MessageFileResult("Please, check your input filepath"));
		} else {
			if (user == null) {
				os.writeObject(new MessageFileResult("User " + msg.usrNic + " is not found"));
			} else {
				synchronized (user.syncFiles) {
					if (user.files == null || user.files.size()  < 10) {
						msg.setFromUsrNic(userNic);
						user.addFile(msg);
						os.writeObject(new MessageFileResult());
					} else {
						os.writeObject(new MessageFileResult("Mailbox is full. Unable to add more files."));
					}
				}
			}
		}
	}

	void letter(MessageLetter msg) throws IOException {
		ServerThread user = ServerMain.getUser(msg.usrNic);
		if (user == null) {
			os.writeObject(new MessageLetterResult("User " + msg.usrNic + " is not found"));
		} else {
			synchronized (user.syncLetters) {
				if (user.letters == null || user.letters.size() < 10) {
					user.addLetter(userNic + ": " + msg.txt);
					os.writeObject(new MessageLetterResult());
				} else {
					os.writeObject(new MessageLetterResult("Mailbox is full. Unable to add more messages."));
				}
			}
		}
	}


	void user( MessageUser msg ) throws IOException {

		String[] nics = ServerMain.getUsers();
		if ( nics != null )
			os.writeObject( new MessageUserResult( nics ));
		else
			os.writeObject( new MessageUserResult( "Unable to get users list" ));
	}

	public MessageFile[] getFiles() {
		synchronized (syncFiles) {
			MessageFile[] filesArray = new MessageFile[0];
			synchronized (syncFiles) {
				if (files != null) {
					filesArray = files.toArray(filesArray);
					files = null;
				}
			}
			return filesArray;
		}
	}

	void checkMail( MessageCheckMail msg ) throws IOException {

		String[] lts = getLetters();
		MessageFile[] msgs = getFiles();
		if ( lts != null || msgs !=null)
			os.writeObject( new MessageCheckMailResult( lts,msgs));
		else
			os.writeObject( new MessageCheckMailResult( "Unable to get mail" ));
	}

	private boolean disconnected = false;
	public void disconnect() {
		if ( ! disconnected )
			try {
				System.err.println( addr.getHostName() + " disconnected" );
				unregister();
				os.close();
				is.close();
				sock.close();
			} catch (IOException e) {
				e.printStackTrace();
			} finally {
				this.interrupt();
				disconnected = true;
			}
	}

	private void unregister() {
		if ( userNic != null ) {
			ServerMain.setUser( userNic, null );
			userNic = null;
		}
	}

	private ServerThread register( String nic, String name ) {
		ServerThread old = ServerMain.registerUser( nic, this );
		if ( old == null ) {
			if ( userNic == null ) {
				userNic = nic;
				userFullName = name;
				System.err.println("User \'"+ name+ "\' registered as \'"+ nic + "\'");
			}
		}
		return old;
	}
}