#include <vector>
#include <cmath>
#include <iostream>

const double M_PI = 3.14159265358979323846;
const int stage = 4;

using namespace std;


double f(double x)
{
    return sqrt((9 - 2 * x) / (2 * x - 21));
}

int main() {

    setlocale(LC_ALL, "rus");

    // Узлы и веса  КФ НАСТ
    vector<double> nativePoints = { -0.86113631, -0.33998104, 0.33998104, 0.86113631 };
    vector<double> values_weight = { 0.34785485, 0.65214515, 0.65214515, 0.34785485 };


    // Преобразование узлов на отрезок [6, 9]
    // по ф-ле x[i] = a + (b - a) * (x[i-1] + 1) / 2
    vector<double> points;
    for (double point : nativePoints) {
        points.push_back(6 + (9 - 6) * (point + 1) / 2);
    }

    // Преобразование весов
    vector<double> weights_transformed;
    for (double weight : values_weight) {
        weights_transformed.push_back((9 - 6) * weight / 2);
    }

    double integral = 0;
    for (int i = 0; i < stage; ++i) {
        integral += weights_transformed[i] * f(points[i]);
    }

    cout << "Узлы: "<<endl;
    for (int i = 0; i < stage;i++) {
        cout << "Узел " << i << "  :  " << points[i] << endl;
    }
    cout << endl;

    cout << "Веса: "<<endl;
    for (int i = 0; i < stage; i++) {
        cout << "Вес " << i << "  :  " << weights_transformed[i]<<endl;
    }
    cout << endl;

    cout <<"Значение интеграла (вычисленное): "<<integral<<endl;
    cout << "Значение интеграла (точное): " << M_PI << endl;
    cout << "ErrorSize: " << abs(M_PI - integral) << endl;

    return 0;
}
