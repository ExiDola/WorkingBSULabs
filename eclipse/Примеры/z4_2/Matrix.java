package z4_2;

/*Определить класс Matrix размерности (n x n). Объявить массив из m объектов.
 Написать методы, вычисляющие первую и вторую нормы матрицы. Определить, какая
 из матриц имеет наименьшую первую и вторую нормы*/

import java.util.Random;
import java.util.Date;

public class Matrix {
	public static Random rand = new Random((new Date()).getTime());
	static final int MAX_A = 10;

	private int N = 0;
	private int[][] matx = null;

	public Matrix() {
		N = 0;
		matx = null;
	}

	public Matrix(int n) {
		this(n, MAX_A);
	}

	public Matrix(int n, int max_val) {
		assert (n > 0);
		assert (max_val > 0);
		matx = new int[n][n];
		N = n;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				matx[i][j] = rand.nextInt(max_val);
			}
		}
	}

	public int Norm_1() {
		assert (N > 0);
		int norm = 0;
		for (int i = 0; i < N; i++) {
			int temp = 0;
			for (int j = 0; j < N; j++) {
				temp += Math.abs(matx[i][j]);
			}
			if (temp > norm) {
				norm = temp;
			}
		}
		return norm;
	}

	public int Norm_2() {
		assert (N > 0);
		int norm = 0;
		for (int j = 0; j < N; j++) {
			int temp = 0;
			for (int i = 0; i < N; i++) {
				temp += Math.abs(matx[i][j]);
			}
			if (temp > norm) {
				norm = temp;
			}
		}
		return norm;
	}

	public String toString() {
		assert (N > 0);
		StringBuilder res = new StringBuilder();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				res.append(" " + matx[i][j]);
			}
			res.append("\n");
		}
		res.append("\n");
		return res.toString();
	}
	
	public int get(int i, int j) {
		assert (N > 0);
		int n = matx.length;
		if (i < 0 || i >= n || j < 0 || j >= n) {
			throw new IndexOutOfBoundsException();
		}
		return matx[i][j];
	}

	public void set(int i, int j, int value) {
		assert (N > 0);
		int n = matx.length;
		if (i < 0 || i >= n || j < 0 || j >= n) {
			throw new IndexOutOfBoundsException();
		}
		matx[i][j] = value;
	}
}
