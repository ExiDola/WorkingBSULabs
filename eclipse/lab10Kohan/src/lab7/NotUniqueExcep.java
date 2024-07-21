package lab7;

public class NotUniqueExcep extends Exception {
    // class release version:
    private static final long serialVersionUID = 1L;

    public NotUniqueExcep(String key) {
        super("Key is not unique: " + key);
    }
}
	