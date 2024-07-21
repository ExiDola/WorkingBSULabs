package email;

import java.io.Serializable;

public class MessageCheckMailResult extends MessageResult implements
		Serializable {

	private static final long serialVersionUID = 1L;

	public String[] letters = null;
	public MessageFile[] files = null;

	public MessageCheckMailResult( String errorMessage ) { //Error
		super( Protocol.CMD_CHECK_MAIL, errorMessage );
	}

	public MessageCheckMailResult( String[] letters,MessageFile[] files ) { // No errors
		super( Protocol.CMD_CHECK_MAIL );
		this.letters = letters;
		this.files = files;
	}

}