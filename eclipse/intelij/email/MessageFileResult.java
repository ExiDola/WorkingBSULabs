package email;

import java.io.Serializable;

public class MessageFileResult extends MessageResult implements Serializable {

    private static final long serialVersionUID = 1L;

    public MessageFileResult( String errorMessage ) { //Error

        super( Protocol.CMD_FILE, errorMessage );
    }

    public MessageFileResult() { // No errors

        super( Protocol.CMD_FILE );
    }
}