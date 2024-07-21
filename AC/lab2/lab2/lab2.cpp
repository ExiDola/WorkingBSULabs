#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include<iostream>
using namespace std;
const double PI = 3.14159265358;
double f(double x)
{
    if (x >= 0 && x <= PI / 2) {
        return cos(x);
    }
    return PI / 2 - x;
}

double exactPoint(double x)
{
    if (x >= 0 && x < PI / 2) {
        return -sin(x);
    }
    else if (x >= PI / 2 && x <= 2) {
        return -1.0;
    }
    else {
        return 0.0;
    }
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    if (argc != 2)
    {
        cerr << "Что-то не так с аргументами ком строки " << endl;
        return 1;
    }

    omp_set_num_threads(16);
    int N = atoi(argv[1]);

    double a = 0.0;
    double b = 1.0;
    double h1 = (b - a) / N;
    double h2 = (b - a) / (4 * N);
    double MaxDerivative = 0.0;
    double MaxDerivative4N = 0.0;
    double x = 0;
    double x4N = 0;

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
#pragma omp parallel for reduction(max:MaxDerivative)
                for (int i = 0; i <= N; i++) {
                    double x1 = a + i * h1;
                    double x2 = a + (i + 1) * h1;
                    if (x2 <= 2)
                    {
                        double derivative = (f(x2) - f(x1)) / h1;
                        if (std::fabs(derivative) > MaxDerivative) {
                            MaxDerivative = std::fabs(derivative);
                            x = x2;
                        }
                    }
                }
            }

#pragma omp section
            {
#pragma omp parallel for reduction(max:MaxDerivative4N)
                for (int i = 0; i <= 4 * N; i++) {
                    double x1 = a + i * h2;
                    double x2 = a + (i + 1) * h2;
                    if (x2 <= 2)
                    {
                        double derivative2 = (f(x2) - f(x1)) / h2;
                        if (std::fabs(derivative2) > MaxDerivative4N) {
                            MaxDerivative4N = std::fabs(derivative2);
                            x4N = x2;
                        }
                    }
                }
            }
        }
    }

        cout << "Приближённый результат: " << MaxDerivative<<endl;
        cout << "Точный результат: " << fabs(exactPoint(x)) << endl;

        cout << "Приближённый результат при 4N : " << MaxDerivative4N << endl;
        cout << "Точный результат ghb 4N: " << fabs(exactPoint(x4N)) << endl;

        cout << "Время выполнения: " << clock() / 1000.0 << endl;

    return 0;
}




//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <omp.h>
//#include<iostream>
//using namespace std;
//
//
//double func(double x)
//{
//    return x * x - 2 * x;
//}
//
//
//int main(int argc, char* argv[])
//{
//    setlocale(LC_ALL, "rus");
//    if (argc != 2)
//    {
//        cerr << "Что-то не так с аргументами ком строки " << endl;
//        return 1;
//    }
//
//    omp_set_num_threads(16);
//    int N = atoi(argv[1]);
//
//    double a = 0.0;
//    double b = 1.0;
//    double h1 = (b - a) / N;
//    double h2 = (b - a) / (4 * N);
//    double res1 = 0;
//    double res2 = 0;
//
//#pragma omp parallel
//    {
//#pragma omp sections
//        {
//#pragma omp section
//            {
//#pragma omp parallel for reduction(+:res1)
//                for (int i = 0; i < N; i++) {
//                    double x_i = a + i * h1;
//                    res1 += func(x_i) * h1;
//                }
//            }
//
//#pragma omp section
//            {
//#pragma omp parallel for reduction(+:res2)
//                for (int i = 0; i < N * 4; i++) {
//                    double x_i = a + i * h2;
//                    res2 += func(x_i) * h2;
//                }
//            }
//        }
//    }
//
//    double exectRes = (double) - 2 / (double)3;
//        cout << "Приближённый результат: " << res1<<endl;
//        cout << "Точный результат: " << exectRes << endl;
//        cout << "Время выполнения: " << clock() / 1000.0 << endl;
//
//    return 0;
//}