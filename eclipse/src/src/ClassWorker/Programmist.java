package ClassWorker;

import java.io.Serializable;

public class Programmist extends ClassWorker implements Serializable {
	
    protected String programmingLanguage;

    public Programmist() {
        super(); 
        this.programmingLanguage = "?";
    }

    public Programmist(String name, int workYears, double weight, WorkLevel worklvl, String programmingLanguage) {
        super(name, workYears, weight, worklvl); 
        this.programmingLanguage = programmingLanguage;
    }
    
    
    @Override
	public String toString() {
	    String str = super.toString(); 
	    str += this.programmingLanguage + ";";
	    return str;
	}
    
    
    public String getProgrammingLanguage() {
	    return programmingLanguage;
	}
	
	public void setProgrammingLanguage(String programmingLanguage) {
	    this.programmingLanguage = programmingLanguage;
	}
}


