package ClassWorker;
import java.io.*;

public class Connector {

	private File file;

	public File getFile() {
		return file;
	}

	public Connector(String filename) {
		this.file = new File(filename);
	}

	public Connector(File file) {
		this.file = file;
	}

	public void write(ClassWorker[] Arr) throws IOException {
		FileOutputStream fos = new FileOutputStream(file);
		try (ObjectOutputStream oos = new ObjectOutputStream(fos)) {
			oos.writeInt(Arr.length);
			for (int i = 0; i < Arr.length; i++) {
				oos.writeObject(Arr[i]);
			}
			oos.flush();
		}
	}

	public ClassWorker[] read() throws IOException, ClassNotFoundException {
		FileInputStream fis = new FileInputStream(file);
		try (ObjectInputStream oin = new ObjectInputStream(fis)) {
			int length = oin.readInt();
			ClassWorker[] result = new ClassWorker[length];
			for (int i = 0; i < length; i++) {
				result[i] = (ClassWorker) oin.readObject();
			}
			return result;
		}
	}
}

