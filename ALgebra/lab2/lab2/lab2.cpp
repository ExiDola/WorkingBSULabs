#include<cmath>
#include<vector>
#include <iostream>
#include<iomanip>
using namespace std;

int n = 0;
double E = 0;
int K = 0;
vector<double> Bline;
vector<double>Xline;

void PrintLine(vector<double>line, const string str)
{
	cout << str << endl;
	for(int i=0;i<n;i++)
	{
		cout << setw(10) << line[i] << endl;
	}
	cout << endl;
}

void ChekChekerOfDiag(vector<vector<double>> MyVec)
{
	double subSum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			if (i != k)
			{
				subSum += MyVec[i][k];
			}
		}
		if (MyVec[i][i] <= subSum)
		{
			cerr << "Не выполнено строго диагональное преобладание. Работа окончена" << endl;
		}
		subSum = 0;
	}
}

void BCulc(vector<vector<double>> MyVec)
{
	Bline.resize(n);
	Xline.resize(n);
	for (int i = 0; i < n; i++)
	{
		Xline[i] = 6 + i;
	}
	cout << endl;

	double Belement = 0;
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			Belement += MyVec[i][k] * Xline[k];
		}
		Bline[i] = Belement;
		Belement = 0;
	}
}

void PrintMatrix(vector<vector<double>> MyVec,const string& str, bool flag)
{
	cout << " Матрица: " << str << endl;
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			cout << setw(10) << MyVec[i][k];
		}
		if (flag)
		{
			cout << setw(10) << Xline[i] << setw(15) << Bline[i];
		}
		cout << endl;
	}

}

vector<double> YakobiMethod(vector<vector<double>> MyVec)
{
	vector<double> XlineYakobi(n, 0);
	int k = 0;
	double prevElem = 0;
	double AimCurrent = 0;
	int i = 0;
	do
	{
		prevElem = XlineYakobi[i];
		double NewX = 0;
		for (int j = 0; j < n; j++)
		{
			if (i != j)
				NewX += (-1) * (MyVec[i][j] * XlineYakobi[j]);
		}
		NewX += Bline[i];
		NewX /= MyVec[i][i];
		XlineYakobi[i] = NewX;
		NewX = 0;

		AimCurrent = fabs(XlineYakobi[i] - prevElem);
		i++;
		if (i % n == 0)
		{
			i = 0;
		}
		k++;
	} while (k <=K || AimCurrent > E);
	if (k >= K)
	{
		cout << "Остановка произошла из-за превышения k количества допустимых итераций. K: " << k << endl;
	}
	return XlineYakobi;
}

vector<double> ZeidelAndRelax(vector<vector<double>> MyVec,double w)
{
	vector<double> XlineZeidelAndRelax(n,0);
	int k = 0;
	double AimCurrent = 0;
	double prevElem = 0;
	int i = 0;
	do
	{
		double NewX = 0;
		
			prevElem = XlineZeidelAndRelax[i];
			for (int j = 0; j < n; j++)
			{
				if (i != j)
					if (j > 0)
						NewX += (-1) * (MyVec[i][j] * XlineZeidelAndRelax[j - 1]);
					else
					{
						NewX += (-1) * (MyVec[i][j] * XlineZeidelAndRelax[j]);
					}
			}
			NewX += Bline[i];
			NewX /= MyVec[i][i];
			XlineZeidelAndRelax[i] = NewX;
			NewX = 0;
			if (w != 1)
			{
				if (i > 0)
					XlineZeidelAndRelax[i] = w * XlineZeidelAndRelax[i] + (1 - w) * prevElem;
				else
				{
					XlineZeidelAndRelax[i] = w * XlineZeidelAndRelax[i] + (1 - w) * prevElem;
				}

			}
		AimCurrent = fabs(XlineZeidelAndRelax[i] - prevElem);
		i++;
		if (i % n == 0)
		{
			i = 0;
		}
		k++;
	} while (k <= K || AimCurrent > E);
	if (k >= K)
	{
		cout << "Остановка произошла из-за превышения k количества допустимых итераций. K: "<< k << endl;
	}
	return XlineZeidelAndRelax;
}

void TepletNorm(vector<double>orig, vector<double>MyX)
{
	vector<double> test(n,0);
	double norm = 0;
	double norm2 = 0;
	for (int i = 0; i < n; i++)
	{
		norm += fabs(orig[i] - MyX[i]);
		norm2 += fabs(MyX[i]);
	}
	cout << "Равномерная норма вычисления: " << norm << endl;
	cout << "Погрешность вычислений: " << norm / norm2 << endl;
	cout << endl << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Введите n" << endl;
	n = 3;
	E = 0.000000001;
	K = 100;
	double test = 0;
	vector<vector<double>> MyVec(n, vector<double>(n,0));
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			if (i != k)
			{
				MyVec[i][k] = 0.01 * (double)((i+1)+(k+1));
				test = MyVec[i][k];
			}
			else
			{
				MyVec[i][i] = 6 * (double)sqrt(i+1);	
				test = MyVec[i][k];
			}
		}
	}
	BCulc(MyVec);
	PrintMatrix(MyVec,"Исходная матрица(A, x, b)",true);
	ChekChekerOfDiag(MyVec);
	vector<double> XlineYakobi = YakobiMethod(MyVec);
	PrintLine(XlineYakobi,"X методом Якоби: ");
	TepletNorm(Xline, XlineYakobi);
	vector<double> XlineZeidel = ZeidelAndRelax(MyVec,1);
	PrintLine(XlineZeidel, "X методом Зейделя: ");
	TepletNorm(Xline, XlineZeidel);
	vector<double> XlineRelax1 = ZeidelAndRelax(MyVec, 0.5);
	PrintLine(XlineRelax1, "X методом Релаксации(w = 0.5): ");
	TepletNorm(Xline, XlineRelax1);
	vector<double> XlineRelax2 = ZeidelAndRelax(MyVec, 1.5);
	PrintLine(XlineRelax2, "X методом Релаксации(w = 1.5): ");
	TepletNorm(Xline, XlineRelax2);

	double sum = 0.0;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i != j)
				sum += MyVec[i][j];
		}
		MyVec[i][i] = sum;
		sum = 0;
	}
	BCulc(MyVec);
	PrintMatrix(MyVec, "Исходная матрица(A, x, b)", true);
	ChekChekerOfDiag(MyVec);
	vector<double> XlineYakobi_2 = YakobiMethod(MyVec);
	PrintLine(XlineYakobi_2, "X методом Якоби: ");
	TepletNorm(Xline, XlineYakobi);
	vector<double> XlineZeidel_2 = ZeidelAndRelax(MyVec, 1);
	PrintLine(XlineZeidel_2, "X методом Зейделя: ");
	TepletNorm(Xline, XlineZeidel_2);
	vector<double> XlineRelax1_2 = ZeidelAndRelax(MyVec, 0.5);
	PrintLine(XlineRelax1_2, "X методом Релаксации(w = 0.5): ");
	TepletNorm(Xline, XlineRelax1_2);
	vector<double> XlineRelax2_2 = ZeidelAndRelax(MyVec, 1.5);
	PrintLine(XlineRelax2_2, "X методом Релаксации(w = 1.5): ");
	TepletNorm(Xline, XlineRelax2_2);

	return 0;
}

