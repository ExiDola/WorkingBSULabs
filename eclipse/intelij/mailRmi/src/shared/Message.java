package shared;

import java.io.File;
import java.io.Serializable;

public class Message implements Serializable {
    public boolean isFile;
    public String msg;
    public String nameFrom;
    public String nameTo;
    public byte[] fileMsg;
    public String filename;

    public Message(String nameFrom,String nameTo,String msg,boolean isFile,byte[] fileMsg,String filename){
        this.fileMsg = fileMsg;
        this.isFile = isFile;
        this.msg = msg;
        this.nameTo = nameTo;
        this.nameFrom = nameFrom;
        this.filename = filename;
    }
}
