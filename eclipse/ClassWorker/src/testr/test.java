package testr;
import ClassWorker.*;
import java.io.File;

public class test {
	public static void main(String[] args) {
		
		 ClassWorker[] workers = new ClassWorker[7]; 

	        workers[0] = new Analyst("Analyst1", 1, 70.0, WorkLevel.low, "Specialization1");
	        workers[1] = new Manager("Manager1", 3, 80.0, WorkLevel.high, "department1","null");
	        workers[2] = new Designer("Designer1", 2, 75.0, WorkLevel.medium, "Graphic Design");
	        
	        workers[3] = new ClassWorker();
	        workers[4] = new Programmist("Programmist1", 3, 80.0, WorkLevel.high,"C#");
	        workers[5] = new Tester("Tester1", 2, 75.0, WorkLevel.medium, "Graphic Design");
	        workers[6] = new ClassWorker("ClassWorker2", 2, 75.0, WorkLevel.medium);
		 
	        for(int i=0;i<7;i++)
	        {
	        	System.out.println(workers[i].toString());
	        }
	        
	        System.out.println("-------");
	        
	        
	        try {
	            Connector con = new Connector(new File("myFile.txt"));
	            con.write(workers);
	        	ClassWorker[] Arr = con.read();
	        	System.out.println("The Arr: ");
	        	for (ClassWorker n : Arr) {
	        		System.out.println(n);
	        	}
	        } catch (Exception e) {
	        	System.err.println(e);
	        }
	        
		 }
}
//String name1,int workYears1, double weight1, WorkLevel worklvl1,String specialization1
//Designer(String name1,int workYears1, double weight1, WorkLevel worklvl1,String designArea )
//Manager(String name1,int workYears1, double weight1, WorkLevel worklvl1,String department1,String nativeLenguage1 )
//public Programmist(String name, int workYears, double weight, WorkLevel worklvl, String programmingLanguage)