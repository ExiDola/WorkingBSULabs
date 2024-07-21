package ClassWorker;
import java.util.Date;
import java.util.*;

public class AppLocale {
	private static final String strMsg = "Msg";
	private static Locale loc = Locale.getDefault();
	private static ResourceBundle res = ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.loc );
	
	static Locale get() {
		return AppLocale.loc;
	}
	
	public static void set( Locale loc ) {
		AppLocale.loc = loc;
		res = ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.loc );
	}
	
	static ResourceBundle getBundle() {
		return AppLocale.res;
	}
	
	public static String getString( String key ) {
		return AppLocale.res.getString(key);
	}
	
	  static Locale getLocale() {
	        return AppLocale.loc;
	    }
	
	public static final String arthur="arthur";
	public static final String den="den";
	public static final String goward="goward";
	public static final String arr="arr";
	public static final String data="data";
	
}
