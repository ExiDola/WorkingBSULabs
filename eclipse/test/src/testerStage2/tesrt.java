package testerStage2;

import ClassWorker.*;

import java.util.*;
import java.io.*;

public class tesrt {

	public static ClassWorker[] createArr() {
		ClassWorker[] workers = new ClassWorker[3];
		
		workers[0] = new ClassWorker("Arthur", 2, 75.0, WorkLevel.medium);
		workers[0].setName(AppLocale.getString(AppLocale.arthur));
        workers[1] = new ClassWorker("Den", 3, 80.0, WorkLevel.high);
        workers[1].setName(AppLocale.getString(AppLocale.den));
        workers[2] = new ClassWorker("Goward", 2, 75.0, WorkLevel.medium);
        workers[2].setName(AppLocale.getString(AppLocale.goward));

		return workers;
	}

	static Locale createLocale(String[] args) {
		if (args.length == 2) {
			return new Locale(args[0], args[1]);
		} else if (args.length == 4) {
			return new Locale(args[2], args[3]);
		}
		return null;
	}

	static void setupConsole(String[] args) {
		if (args.length >= 2) {
			if (args[0].equals("-encoding")) {
				try {
					System.setOut(new PrintStream(System.out, true, args[1]));
				} catch (UnsupportedEncodingException ex) {
					System.err.println("Unsupported encoding: " + args[1]);
					System.exit(1);
				}
			}
		}
	}

	public static void main(String[] args) {

		try {
			setupConsole(args);
			Locale loc = createLocale(args);
			if (loc == null) {
				System.err.println("Invalid argument(s)\n"
						+ "Syntax: [-encoding ENCODING_ID] language country\n"
						+ "Example: -encoding Cp855 be BY");
				System.exit(1);
			}
			AppLocale.set(loc);
			Connector con = new Connector(new File("myFile.dat"));
			con.write(createArr());
			ClassWorker[] Arr = con.read();
			System.out.println(AppLocale.getString(AppLocale.arr) + ":");
			for (ClassWorker n : Arr) {
				System.out.println(n);
			}
		} catch (Exception e) {
			System.err.println(e);
		}
	}
}
