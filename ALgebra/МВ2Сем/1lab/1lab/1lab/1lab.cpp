#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <cfloat>
#include <vector>

const double PI = 3.14159265358979323846;

std::ofstream fout1("output1.txt");
std::ofstream fout2("output2.txt");
std::ofstream fout3("maxError.txt");



using namespace std;

double f1(double x) {
    return x * x * cos(2 * x);
}

double f2(double x) {
    return 1.0 / (1.0 + 5.0 * x * x);
}

double calculateFiniteDifference(double x0, double x1, double f_x0, double f_x1) {
    return (f_x1 - f_x0) / (x1 - x0);
}

void vecFiller(vector<vector<double>>& vec, int n, double a, double h, double (*f)(double))
{
    for (int i = 0; i < n + 1; i++)
    {
        double mult = a + i * h;
        vec[i][0] = mult;
        vec[i][1] = f(mult);
    }
    for (int i = 1; i < n + 2; i++)
    {
        for (int j = 0; j < n - i + 1; j++)
        {
            double finite_difference = calculateFiniteDifference(vec[j][0], vec[i + j][0], vec[j][i], vec[j + 1][i]);
            vec[j][i + 1] = finite_difference;
        }
    }
}

void vecFiller2(std::vector<std::vector<double>>& vec, int n, double a, double b, double (*f)(double)) {
    for (int i = 0; i < n + 1; i++) {
        double mult = (a + b) / 2.0 + (b - a) / 2.0 * cos((2.0 * i + 1.0) / (2.0* (n + 1))* acos(-1.0));
        vec[i][0] = mult;
        vec[i][1] = f(mult);
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < n - i + 1; j++) {
            double finite_difference = calculateFiniteDifference(vec[j][0], vec[i + j][0], vec[j][i], vec[j + 1][i]);
            vec[j][i + 1] = finite_difference;
        }
    }
}

double calculateInterpolationPolynomial(double x, double x0,double b, double h, double f_x0, int n, double (*f)(double),vector<vector<double>> vec)
{
    double result = f(x0);
    double term = 1.0;
    double mult = 0;
    double test = 0;
    for (int i = 1; i <= n; ++i) 
    {
        mult = x - (x0 + (i - 1) * h);
        term *= mult;
        test = vec[0][i+1];
        result += test * term;
    }

    return result;
}

double calculateInterpolationPolynomial2(double x, double x0, double b, double h, double f_x0, int n, double (*f)(double), vector<vector<double>> vec)
{
    double result = f(x0);
    double term = 1.0;
    double mult = 0;
    double test = 0;
    for (int i = 1; i <= n; ++i) {
        mult = x - (((x0 + b) / 2.0 + (b - x0) / 2.0 * cos(acos(-1.0) * (2.0 * (i - 1) + 1.0) / (2.0 * (n + 1)))));
        term *= mult;
        test = vec[0][i + 1];
        result += test * term;
    }

    return result;
}

double errorCalculation(double (*f)(double), vector<double> Xline, vector<double> ans)
{
    double maxError = DBL_MIN;
    int n = Xline.size();

    for (int i = 0; i < n; i++)
    {
        double currentError = abs(f(Xline[i]) - ans[i]);
        if (maxError < currentError)
        {
            maxError = currentError;
        }
    }

    return maxError;
}



int main() {
    const double a = -3.0;
    const double b = 3.0;

    const int n = 30;
    double h = (b - a) / n;



    vector<vector<double>> vec(n + 1, vector<double>(n + 2, 0.0));
    vecFiller(vec, n, a, h,f1);
        
    int size = 100;

    vector<double> points(size+1, 0);
    int k = 0;
    for (double i = -3; i <= 3;)
    {
        points[k] = i;
        i += (b - a) / size;
        k++;
    }
    points[size] = b;

    cout << "For f1:" << endl;
    vector<double> values1(size + 1);
    for (int i = 0; i <= size; ++i) {
        values1[i] = calculateInterpolationPolynomial(points[i], a, b, h, f1(points[i]), n, f1, vec);
    }
    vecFiller(vec, n, a, h, f2);
    vector<double> values2(size + 1);
    for (int i = 0; i <= size; ++i) 
    {
        values2[i] = calculateInterpolationPolynomial(points[i], a,b, h, f2(points[i]), n, f2,vec);
    }
    for (int i = 0; i <= size; ++i) {
        //cout << "Interpolated value for f1 at X_i = " << setw(10) << points[i] << setw(10) << f1(points[i]) << ": " << setw(15) << values1[i] << endl;
    }
    fout3 << errorCalculation(f1, points, values1)<<endl;

    cout << "For f2:" << endl;
    cout << endl;
    for (int i = 0; i <= size; ++i) {
        //cout << "Interpolated value for f2 at X_i = " << setw(10) << points[i] << setw(10) << f2(points[i]) << ": " << setw(15) << values2[i] << endl;
    }
    fout3 << errorCalculation(f2, points, values2) << endl;


    vecFiller2(vec, n, a, b, f1);
    cout << "For f3:" << endl;
    vector<double> values3(size + 1);
    for (int i = 0; i <= size; ++i)
    {
        double x = points[i];
        values3[i] = calculateInterpolationPolynomial2(x, a, b, h, f1(x), n, f1, vec);
    }
    vecFiller2(vec, n, a, b, f2);
    vector<double> values4(size + 1);
    for (int i = 0; i <= size; ++i) {
        double x = points[i];
        values4[i] = calculateInterpolationPolynomial2(x, a, b, h, f2(x), n, f2, vec);
    }

    for (int i = 0; i <= size; ++i) {
        double x = points[i];
        //cout << "Interpolated value for f3 at X_i = " << setw(10) << x << setw(10) << f1(x) << ": " << setw(15) << values3[i] << endl;
        fout1 << points[i] << "\t" << values3[i] << endl;
    }
    fout3 << errorCalculation(f1, points, values3) << endl;

    cout << "For f4:" << endl;
    cout << endl;
    for (int i = 0; i <= size; ++i) {
        double x = points[i];
        //cout << "Interpolated value for f4 at X_i = " << setw(10) << x << setw(10) << f2(x) << ": " << setw(15) << values4[i] << endl;
        fout2 << points[i] << "\t" << values4[i] << endl;
    }
    fout3 << errorCalculation(f2, points, values4) << endl;
    
    return 0;
}
