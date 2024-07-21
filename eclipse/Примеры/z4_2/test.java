package z4_2;

/* test.java:
Определить класс Matrix размерности (n x n). Объявить массив из m объектов.
Написать методы, вычисляющие первую и вторую нормы матрицы. Определить, какая
из матриц имеет наименьшую первую и вторую нормы*/

public class test {
    static final int NUM = 10;

    public static void main(String[] args) {
        Matrix [] array = new Matrix[NUM];
        for ( int i = 0; i < NUM; i++ ) {
            System.out.println("#" + (i + 1) + ":");
            array[i] = new Matrix( Matrix.rand.nextInt(4)+ 2 );
            System.out.println(array[i]);
        }
        int min = Integer.MAX_VALUE, k = NUM + 1;
        for ( int i = 0; i < NUM; i++ )	{
            int norm = array[i].Norm_1() + array[i].Norm_2();
            if ( norm < min ) {
                min = norm;
                k = i + 1;
            }
        }
        System.out.println(
            "matrix #" + k +
            " has minimal norm-1 (" + array[k - 1].Norm_1() +
            ") and norm-2 (" + array[k - 1].Norm_2()+")");
        for ( int i = 0; i < NUM; i++ ) {
            int norm = array[i].Norm_1();
            if ( norm < min ) {
                min = norm;
                k = i + 1;
            }
        }
        System.out.println(
            "matrix #" + k +
            " has minimal norm-1 (" + min + ")" );
        min=Integer.MAX_VALUE;
        for ( int i = 0; i < NUM; i++) {
            int norm = array[i].Norm_2();
            if ( norm < min ) {
                min = norm;
                k = i + 1;
            }
        }
        System.out.println(
            "matrix #" + k +
            " has minimal norm-2 (" + min + ")" );

        System.out.println("---test assert---");
        System.out.println(new Matrix());
    }
}
