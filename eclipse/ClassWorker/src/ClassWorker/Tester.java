package ClassWorker;

import java.io.Serializable;

public class Tester extends ClassWorker implements Serializable{

	
	protected String testingType;

    public Tester() {
        super(); 
        this.testingType = "?";
    }

    public Tester(String name, int workYears, double weight, WorkLevel worklvl, String testingType) {
        super(name, workYears, weight, worklvl); 
        this.testingType = testingType;
    }
    
    
    @Override
	public String toString() {
	    String str = super.toString(); 
	    str += this.testingType + ";";
	    return str;
	}
    
    
    
    public String getTestingType() {
	    return testingType;
	}
	
	public void setTestingType(String testingType) {
	    this.testingType = testingType;
	}
}
