package email.client;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.nio.file.Paths;
import java.util.Scanner;
import java.util.TreeMap;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;


import email.*;

public class ClientMain {
	// arguments: userNic userFullName [host]
	public static void main(String[] args)  {
		if (args.length < 2 || args.length > 3) {
			System.err.println(	"Invalid number of arguments\n" + "Use: nic name [host]" );
			waitKeyToStop();
			return;
		}
		try ( Socket sock = ( args.length == 2 ?
				new Socket( InetAddress.getLocalHost(), Protocol.PORT ):
				new Socket( args[2], Protocol.PORT ) )) {
			System.err.println("initialized");
			session(sock, args[0], args[1] );
		} catch ( Exception e) {
			System.err.println(e);
		} finally {
			System.err.println("bye...");
		}
	}

	static void waitKeyToStop() {
		System.err.println("Press a key to stop...");
		try {
			System.in.read();
		} catch (IOException e) {
		}
	}

	static class Session {
		boolean connected = false;
		String userNic = null;
		String userName = null;
		Session( String nic, String name ) {
			userNic = nic;
			userName = name;
		}
	}
	static void session(Socket s, String nic, String name) {
		try ( Scanner in = new Scanner(System.in);
			  ObjectInputStream is = new ObjectInputStream(s.getInputStream());
			  ObjectOutputStream os = new ObjectOutputStream(s.getOutputStream())) {
			Session ses = new Session(nic, name);
			if ( openSession( ses, is, os, in )) {
				try {
					while (true) {
						Message msg = getCommand(ses, in);
						if (! processCommand(ses, msg, is, os,in)) {
							break;
						}
					}
				} finally {
					closeSession(ses, os);
				}
			}
		} catch ( Exception e) {
			System.err.println(e);
		}
	}

	static boolean openSession(Session ses, ObjectInputStream is, ObjectOutputStream os, Scanner in)
			throws IOException, ClassNotFoundException {
		os.writeObject( new MessageConnect(ses.userNic, ses.userName));
		MessageConnectResult msg = (MessageConnectResult) is.readObject();
		if (msg.Error()== false ) {
			System.err.println("connected");
			ses.connected = true;
			return true;
		}
		System.err.println("Unable to connect: "+ msg.getErrorMessage());
		System.err.println("Press <Enter> to continue...");
		if( in.hasNextLine())
			in.nextLine();
		return false;
	}

	static void closeSession(Session ses, ObjectOutputStream os) throws IOException {
		if ( ses.connected ) {
			ses.connected = false;
			os.writeObject(new MessageDisconnect());
		}
	}

	static Message getCommand(Session ses, Scanner in) {
		while (true) {
			printPrompt();
			if (in.hasNextLine()== false)
				break;
			String str = in.nextLine();
			byte cmd = translateCmd(str);
			switch ( cmd ) {
				case -1:
					return null;
				case Protocol.CMD_CHECK_MAIL:
					return new MessageCheckMail();
				case Protocol.CMD_USER:
					return new MessageUser();
				case Protocol.CMD_LETTER:
					return inputLetter(in);
				case Protocol.CMD_FILE:
					MessageFile msgF=  inputFileLetter(in);

					if(msgF==null){
						byte[] emptyArray = new byte[0];
						return new MessageFile("",emptyArray,"");
					}
					return msgF;

				case 0:
					continue;
				default:
					System.err.println("Unknow command!");
					continue;
			}
		}
		return null;
	}

	static MessageLetter inputLetter(Scanner in) {
		String usrNic, letter;
		System.out.print("Enter user NIC: ");
		usrNic = in.nextLine();
		System.out.print("Enter message: ");
		letter = in.nextLine();
		return new MessageLetter(usrNic, letter);
	}

	static MessageFile inputFileLetter(Scanner in) {
		String usrNic, filepath;
		System.out.print("Enter user NIC: ");
		usrNic = in.nextLine();
		System.out.print("Enter filepath : ");
		filepath = in.nextLine();
		File file = new File(filepath);
		if (!file.exists() || !file.isFile()) {
			return null;
		}
		return new MessageFile(usrNic, getFileBytes(file),file.getName());
	}

	private static byte[] getFileBytes(File file) {
		try {
			Path path = file.toPath();
			return Files.readAllBytes(path);
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
	}


	static TreeMap<String,Byte> commands = new TreeMap<String,Byte>();
	static {
		commands.put("q", new Byte((byte) -1));
		commands.put("quit", new Byte((byte) -1));
		commands.put("m", new Byte(Protocol.CMD_CHECK_MAIL));
		commands.put("mail", new Byte(Protocol.CMD_CHECK_MAIL));
		commands.put("u", new Byte(Protocol.CMD_USER));
		commands.put("users", new Byte(Protocol.CMD_USER));
		commands.put("l", new Byte(Protocol.CMD_LETTER));
		commands.put("letter", new Byte(Protocol.CMD_LETTER));
		commands.put("f", new Byte(Protocol.CMD_FILE));
		commands.put("file", new Byte(Protocol.CMD_FILE));
	}

	static byte translateCmd(String str) {
		// returns -1-quit, 0-invalid cmd, Protocol.CMD_XXX
		str = str.trim();
		Byte r = commands.get(str);
		return (r == null ? 0 : r.byteValue());
	}

	static void printPrompt() {
		System.out.println();
		System.out.print("(q)uit/(m)ail/(u)sers/(l)etter/(f)ile >");
		System.out.flush();
	}

	static boolean processCommand(Session ses, Message msg,
								  ObjectInputStream is, ObjectOutputStream os,Scanner in)
			throws IOException, ClassNotFoundException {
		if ( msg != null )
		{
			os.writeObject(msg);
			MessageResult res = (MessageResult) is.readObject();
			if ( res.Error()) {
				System.err.println(res.getErrorMessage());
			} else {
				switch (res.getID()) {
					case Protocol.CMD_CHECK_MAIL:
						printMail(( MessageCheckMailResult ) res,in);
						break;
					case Protocol.CMD_USER:
						printUsers(( MessageUserResult ) res);
						break;
					case Protocol.CMD_LETTER:
						System.out.println("OK...");
						break;
					case Protocol.CMD_FILE:
						System.out.println("OK...");
						break;
					default:
						assert(false);
						break;
				}
			}
			return true;
		}
		return false;
	}

	private static void printMail(MessageCheckMailResult m, Scanner in) {
		if ((m.letters != null && m.letters.length > 0) || (m.files != null && m.files.length > 0)) {
			System.out.println("Your mail {");
			for (String str : m.letters) {
				System.out.println(str);
			}
			int counter = 1;
			for (MessageFile msg : m.files) {
				System.out.println(msg.getFromUsrNic() + ":" + msg.filename);
				System.out.println("Do you want to download this file? (yes/no)");
				System.out.println(m.files.length - counter + " Files remaining");
				String userResponse = in.nextLine().toLowerCase();

				if (userResponse.equals("yes")) {
					System.out.println("Downloading file...");

					String userHome = System.getProperty("user.home");
					Path userDownloads = Path.of(userHome, "Downloads");

					Path targetPath = userDownloads.resolve(msg.filename);

					try {
						Files.write(targetPath, msg.fileBytes);
						System.out.println("File downloaded to: " + targetPath);
					} catch (Exception e) {
						System.err.println("Error downloading file: " + e.getMessage());
					}
				} else {
					System.out.println("File download canceled.");
				}
				counter++;
			}
			System.out.println("}");
		} else {
			System.out.println("No mail...");
		}
	}


	static void printUsers(MessageUserResult m) {
		if ( m.userNics != null ) {
			System.out.println("Users {");
			for (String str: m.userNics) {
				System.out.println("\t" + str);
			}
			System.out.println("}");
		}
	}
}
