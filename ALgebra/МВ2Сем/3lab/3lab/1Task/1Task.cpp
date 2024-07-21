#include<vector>
#include<cmath>
#include <iostream>
using namespace std;

const double M_PI = 3.14159265358979323846;
int SIZE = 4;
const double a = 6;
const double b = 9;
double h = (b - a) / SIZE;

//вывод вектора
void printVector(vector<double> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

//функция вычисления узлов Средних прямоугольников
vector<double> getPoints(double a, double b)
{
	vector<double> points;
	
	for (int i = 0; i < SIZE; i++)
	{
		points.push_back(a + h * (i + 0.5));
	}
	return points;
}


//функция получения узлов Симпсона четных
vector<double> getPointsSimpson(double a, double b)
{
	std::vector<double> points(SIZE+1);
	for (int i = 0; i <= SIZE; ++i) {
		points[i] = a + i * h;
	}
	return points;
}

 double f(double x)
{
    return sqrt((9 - 2 * x) / (2 * x - 21));
}

//I culculation 
double Iculc1(vector<double>& vec)
{
	double I = 0;
	for (int i = 0; i < SIZE;i++)
	{
		I+=f(vec[i]);
	}
	return I;
}

//оценка погрешности составных квадратных формул
double errorMark(double I1, double I2, int p)
{
	return abs(I1 - I2) / (pow(2, p) - 1);
}

double Iculc2(vector<double>& vec)
{
	double I = 0;
	for (int i = 0; i < SIZE; i++)
	{
		I += (f(vec[i]) + 4*f(vec[i]+h/2) + f(vec[i+1]));
	}
	return I;
}


int main()
{
    //вычисление интегралов методом Квадратурных формул(КФ средних прямоугольников,КФ Симпсона)
	setlocale(LC_ALL, "rus");
	vector<double> points = getPoints(a, b);
	double I = Iculc1(points);
	I = I * h;
	cout << h << endl;
	cout << "I = " << I << endl;
	cout << "I точное = " << M_PI << endl;
	SIZE /= 2;
	h = (b - a) / SIZE;
	vector<double> points1_ = getPoints(a, b);
	double I1_ = Iculc1(points1_);
	I1_ = I1_ * h;
	cout << "Error оценка = " << errorMark(I1_, I, 2) << endl;
	cout << "Error = " << abs(M_PI - I) << endl;
	cout<< endl;

	SIZE *= 2;
	h = (b - a) / SIZE;

	vector<double> points2 = getPointsSimpson(a, b);
	double I2 = Iculc2(points2);
	I2 = I2 * h / 6;
	cout << h << endl;
	cout << "I2 = " << I2 << endl;
	cout << "I2 точное = " << M_PI << endl;
	SIZE /= 2;
	h = (b - a) / SIZE;
	vector<double> points2_ = getPointsSimpson(a, b);
	double I2_ = Iculc2(points2_);
	I2_ = I2_ * h / 6;
	cout << "Error оценка = " << errorMark(I2, I2_, 4) << endl;
	cout << "Error2 = " << abs(M_PI - I2) << endl;

	return 0;
}

