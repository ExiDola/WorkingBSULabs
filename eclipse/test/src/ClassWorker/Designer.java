package ClassWorker;

import java.io.Serializable;

public class Designer extends ClassWorker implements Serializable
{
	protected String designArea;
	
	Designer()
	{
		super();
		this.designArea = "?";
	}
	
	public Designer(String name1,int workYears1, double weight1, WorkLevel worklvl1,String designArea )
	{
		super(name1, workYears1,weight1,worklvl1);
		this.designArea = designArea;
	}
	
	
	@Override
	public String toString() {
	    String str = super.toString(); 
	    str += this.designArea + ";";
	    return str;
	}
	
	public String getDesignArea() {
	    return designArea;
	}
	
	public void setDesignArea(String name) {
	    this.name = name;
	}
}
