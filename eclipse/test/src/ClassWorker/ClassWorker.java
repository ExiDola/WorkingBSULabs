package ClassWorker;
import java.io.Serializable;
import java.util.Date;
import java.text.SimpleDateFormat;
import java.text.DateFormat;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.Locale;

public class ClassWorker implements Serializable
{
	protected String name;
	protected int workYears;
	protected double weight;
	protected WorkLevel worklvl;
	protected Date creationDate = new Date();

	public ClassWorker() {
		this.name = "?";
	    this.workYears = 0;
	    this.weight = 0;
	    this.worklvl = WorkLevel.unknown;
	    this.creationDate = new Date();
	}
	
	public ClassWorker(String name1,int workYears1, double weight1, WorkLevel worklvl1) 
	{
		this.name = name1;
	    this.workYears = workYears1;
	    this.weight = weight1;
	    this.worklvl = worklvl1;
	    this.creationDate = new Date();
	}
	
	public String getCreationDate() {
        DateFormat dateFormatter = DateFormat.getDateTimeInstance(DateFormat.LONG, DateFormat.DEFAULT, AppLocale.getLocale());
        String dateOut = dateFormatter.format(creationDate);
        return dateOut;
    }

	
	public String toString() {
	    String str = "";
	    str +=getCreationDate()+";"+ this.name + ";" + this.workYears + ";" + this.weight + ";" + this.worklvl + ";";
	    return str;
	}

public int getWorkYears() {
    return workYears;
}

public double getWeight() {
    return weight;
}

public WorkLevel getWorkLevel() {
    return worklvl;
}

public void setName(String name) {
    this.name = name;
}

public void setWorkYears(int workYears) {
    this.workYears = workYears;
}

public void setWeight(double weight) {
    this.weight = weight;
}

public void setWorkLevel(WorkLevel worklvl) {
    this.worklvl = worklvl;
}	

private String info = "";

public String getInfo() {
	return info;
}

public void setInfo(String info) {
	this.info = info;
}


public void setData() {
    this.creationDate = new Date();
}
}
