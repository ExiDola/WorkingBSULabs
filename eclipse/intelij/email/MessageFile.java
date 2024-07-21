package email;

import java.io.File;
import java.io.Serializable;

public class MessageFile extends Message implements Serializable {

    private static final long serialVersionUID = 1L;

    public String usrNic;
    public byte[] fileBytes;
    public String filename;

    private String fromUsrNic = "";

    public MessageFile(String usrNick,byte[] fileBytes, String filename) {
        super(Protocol.CMD_FILE);
        this.usrNic = usrNick;
        this.fileBytes = fileBytes;
        this.filename = filename;
    }

    public void setFromUsrNic(String fromUsrNic) {
        this.fromUsrNic = fromUsrNic;
    }
    public String getFromUsrNic(){
        return fromUsrNic;
    }
}