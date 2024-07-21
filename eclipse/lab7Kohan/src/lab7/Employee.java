package lab7;

import java.io.*;
import java.util.*;

public class Employee implements Serializable {
    // class release version:
    private static final long serialVersionUID = 1L;
    
    // New attributes for an employee
    String employeeId;
    static final String P_employeeId = "Employee ID";
    int departmentNumber;
    static final String P_departmentNumber = "Department Number";
    String fullName;
    static final String P_fullName = "Full Name";
    double salary;
    static final String P_salary = "Salary";
    Date hireDate;
    static final String P_hireDate = "Hire Date";
    double bonusPercentage;
    static final String P_bonusPercentage = "Bonus Percentage";
    double incomeTax;
    static final String P_incomeTax = "Income Tax";

    // validation methods:
    static Boolean validEmployeeId(String str) {
        return Integer.parseInt(str)>0;
    }

    static Boolean validDepartmentNumber(int number) {
        return number>0;
    }

    static Boolean validSalary(double salary) {
        return salary>0;
    }

    public static boolean nextRead(Scanner fin, PrintStream out) {
        return nextRead(P_employeeId, fin, out);
    }

    static boolean nextRead(final String prompt, Scanner fin, PrintStream out) {
        out.print(prompt);
        out.print(": ");
        return fin.hasNextLine();
    }

    public static Employee read(Scanner fin, PrintStream out) throws IOException, NumberFormatException {
        String str;
        Employee EmployeeElement = new Employee();
        EmployeeElement.employeeId = fin.nextLine().trim();
        if (Employee.validEmployeeId(EmployeeElement.employeeId) == false) {
            throw new IOException("Invalid Employee ID: " + EmployeeElement.employeeId);
        }
        if (!nextRead(P_departmentNumber, fin, out)) {
            return null;
        }
        str = fin.nextLine();
        EmployeeElement.departmentNumber = Integer.parseInt(str);
        if (Employee.validDepartmentNumber(EmployeeElement.departmentNumber) == false) {
            throw new IOException("Invalid Department Number: " + EmployeeElement.departmentNumber);
        }
        if (!nextRead(P_fullName, fin, out)) {
            return null;
        }
        EmployeeElement.fullName = fin.nextLine();
        if (!nextRead(P_salary, fin, out)) {
            return null;
        }
        str = fin.nextLine();
        EmployeeElement.salary = Double.parseDouble(str);
        if (Employee.validSalary(EmployeeElement.salary) == false) {
            throw new IOException("Invalid Salary: " + EmployeeElement.salary);
        }
        if (!nextRead(P_hireDate, fin, out)) {
            return null;
        }
        str = fin.nextLine();
        // Add logic to parse Date from the string
        if (!nextRead(P_bonusPercentage, fin, out)) {
            return null;
        }
        str = fin.nextLine();
        EmployeeElement.bonusPercentage = Double.parseDouble(str);
        if (!nextRead(P_incomeTax, fin, out)) {
            return null;
        }
        str = fin.nextLine();
        EmployeeElement.incomeTax = Double.parseDouble(str);
        return EmployeeElement;
    }

    // Existing methods with their original names
    public Employee() {
    }

    public String toString() {
        return new String(
            employeeId + "\n" +
            departmentNumber + "\n" +
            fullName + "\n" +
            salary + "\n" +
            hireDate + "\n" +
            bonusPercentage + "\n" +
            incomeTax
        );
    }
}
