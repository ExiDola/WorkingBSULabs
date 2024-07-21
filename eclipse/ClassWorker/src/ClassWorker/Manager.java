package ClassWorker;

import java.io.Serializable;

public class Manager extends ClassWorker implements Serializable
{
	protected String department;
	protected String nativeLanguage;
	
	Manager()
	{
		super();
		this.department = "?";
		this.nativeLanguage = "?";
	}
	
	public Manager(String name1,int workYears1, double weight1, WorkLevel worklvl1,String department1,String nativeLenguage1 )
	{
		super(name1, workYears1,weight1,worklvl1);
		this.department = department1;
		this.nativeLanguage = nativeLenguage1;
	}
	
	@Override
	public String toString() {
	    String str = super.toString(); 
	    str += this.department + ";" + this.nativeLanguage + ";";
	    return str;
	}
	
	
	public String getDepartment() {
	    return department;
	}
	
	public void setdepartment(String department) {
	    this.department = department;
	}
	
	public String getNativeLanguage() {
	    return nativeLanguage;
	}
	
	public void setDepartment(String nativeLanguage) {
	    this.nativeLanguage = nativeLanguage;
	}

}
