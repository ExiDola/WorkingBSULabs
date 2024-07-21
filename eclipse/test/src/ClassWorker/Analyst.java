package ClassWorker;

import java.io.Serializable;

public class Analyst extends ClassWorker implements Serializable {
    protected String specialization;

    public Analyst() {
        super(); 
        this.specialization = "?";
    }

    public Analyst(String name, int workYears, double weight, WorkLevel worklvl, String specialization1) {
        super(name, workYears, weight, worklvl); 
        this.specialization = specialization1;
    }
    
	@Override
	public String toString() {
	    String str = super.toString(); 
	    str += this.specialization + ";";
	    return str;
	}
	
	
	public String getSpecialization() {
	    return specialization;
	}
	
	public void setSpecialization(String name) {
	    this.name = name;
	}
}

