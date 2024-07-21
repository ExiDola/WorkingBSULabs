#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;

// Функция f(x, u)
double func(double x, double u) {
    return (u * u + u * x) / (x * x);
}

//производная для метода Ньютона
double func_derivative(double x, double u) {
    return (2 * u + x) / (x * x);
}

// Точное решение
double CurrentFunc(double x) {
    return x / (2 - log(x));
}

// Функция для оценки погрешности методом Рунге
vector<double> RungError(const vector<double>& vecU, const vector<double>& vecUSec, double h, int p) {
    vector<double> errors;
    double a = 0;
    for (size_t i = 0; i < vecUSec.size(); ++i) {
        a = abs((vecU[i] - vecUSec[i]) / (pow(2, p) - 1));
        errors.push_back(abs(a));
    }
    return errors;
}

//Неявный метод трапеций
vector<double> implTrapez(const vector<double>& VecX, double u0, double h) {
    vector<double> vecU;
    vecU.push_back(u0);

    for (size_t i = 1; i < VecX.size(); ++i) {
        double xi = VecX[i - 1];
        double ui = vecU.back();
        double xIPlusH = VecX[i];
        double uNext = ui;
        double tol = 1e-6; // уровень допустимой погрешности
        int maxIter = 100; // максимальное количество итераций

        // Итерационный метод Ньютона для решения нелинейного уравнения
        for (int j = 0; j < maxIter; ++j) {
            double g = uNext - ui - h * (func(xi, ui) / 2 + func(xIPlusH, uNext) / 2);
            double g_prime = 1 - h / 2 * func_derivative(xIPlusH, uNext);
            double uPrev = uNext;
            uNext = uNext - g / g_prime;
            if (abs(uNext - uPrev) < tol) {
                break; // выход из цикла, если достигнута сходимость
            }
        }

        vecU.push_back(uNext);
    }
    return vecU;
}

// Явный метод трапеций
vector<double> explTrapez(const vector<double>& VecX, double u0, double h) {
    vector<double> vecU;
    vecU.push_back(u0);

    for (size_t i = 1; i < VecX.size(); ++i) {
        double xi = VecX[i - 1];
        double ui = vecU.back();
        double xIPlusH = VecX[i];

        double val = ui + h * func(xi, ui);
        double k1, k2;
        k1 = func(xi, ui);
        k2 = func(xIPlusH, val);

        double uNext = ui + h * (k1 / 2 + k2 / 2);

        vecU.push_back(uNext);
    }
    return vecU;
}

// Метод Адамса 2-го порядка
vector<double> AbrmSecDegr(const vector<double>& VecX, double u0, double h) {
    vector<double> vecU;
    vecU.push_back(u0);

    int i = 2;
    double xi = VecX[i - 1];
    double xIPlusH = VecX[i];
    double ui = vecU.back();
    double val = ui + h * func(xi, ui);
    double k1, k2;
    k1 = func(xi, ui);

    k2 = func(xIPlusH, val);
    double uNext = ui + h * (k1 / 2 + k2 / 2);

    vecU.push_back(uNext);

    for ( ; i < VecX.size(); ++i) {
        xi = VecX[i - 1];
        ui = vecU.back();
        double xPrev = VecX[i - 2];
        double uPrev = vecU[vecU.size() - 2];
        xIPlusH = VecX[i];

        double val = ui + h * (1.5 * func(xi, ui) - 0.5 * func(xPrev, uPrev));
        double k1, k2;
        k2 = func(xIPlusH, val);
        k1 = func(xi, ui);

        double u_np1 = ui + h * (k1 / 2 + k2 / 2);

        vecU.push_back(u_np1);
    }
    return vecU;
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Далее-> Неявный метод - НП" << endl;
    cout << "Далее-> Явный метод - ЯП" << endl;
    cout << "Далее-> Метод Абрамса - МА" << endl;
    double x0 = 1.0, u0 = 0.5;
    double h = 0.1;
    double xN = 2.0;

    // Шаги сетки
    vector<double> vecX;
    for (double x = x0; x <= xN + 0.000000000001; x += h) {
        vecX.push_back(x);
    }
    cout << fixed << setprecision(5);

    // Точные значения
    vector<double> currVecU;
    for (double x : vecX) {
        currVecU.push_back(CurrentFunc(x));
    }

    // Расчеты
    vector<double> u_impl = implTrapez(vecX, u0, h);
    vector<double> u_expl = explTrapez(vecX, u0, h);
    vector<double> u_adams = AbrmSecDegr(vecX, u0, h);

    // Запись значений x и y в file1
    ofstream file1("file1.txt");
    if (file1.is_open()) {
        for (size_t i = 0; i < vecX.size(); ++i) {
            file1 << vecX[i] << " " << currVecU[i] << endl;
        }
        file1.close();
    }
    else {
        cout << "Не удалось открыть файл file1.txt для записи" << endl;
    }

    // Запись значений x и значений от неявного метода в file2
    ofstream file2("file2.txt");
    if (file2.is_open()) {
        for (size_t i = 0; i < vecX.size(); ++i) {
            file2 << vecX[i] << " " << u_impl[i] << endl;
        }
        file2.close();
    }
    else {
        cout << "Не удалось открыть файл file2.txt для записи" << endl;
    }

    // Вывод результатов
    for (size_t i = 0; i < vecX.size(); ++i) {
        cout << "x = " << vecX[i];
        cout << " | u (НП) = " << u_impl[i];
        cout << " | u (ЯП) = " << u_expl[i];
        cout << " | u (МА) = " << u_adams[i];
        cout << " | u (точное) " << currVecU[i] << endl;
    }

    // Расчеты с шагом h/2
    double h_half = h / 2;
    vector<double> xs_half;
    for (double x = x0; x <= xN + 1e-10; x += h_half) {
        xs_half.push_back(x);
    }

    vector<double> NPu = implTrapez(xs_half, u0, h_half);
    vector<double> YAPu = explTrapez(xs_half, u0, h_half);
    vector<double> ADAMSu = AbrmSecDegr(xs_half, u0, h_half);

    // Интерполяция результатов для h на узлы сетки с шагом h
    vector<double> NPU_prevStep;
    vector<double> YAPu_prevStep;
    vector<double> ADAMSu_prevStep;

    for (size_t i = 0; i < vecX.size(); ++i) {
        NPU_prevStep.push_back(NPu[i * 2]);
        YAPu_prevStep.push_back(YAPu[i * 2]);
        ADAMSu_prevStep.push_back(ADAMSu[i * 2]);
    }
    // Оценка погрешности
    vector<double> ErrorNP = RungError(u_impl, NPU_prevStep, h, 2);
    vector<double> ErrorYAP = RungError(u_expl, YAPu_prevStep, h, 2);
    vector<double> ErrorMA = RungError(u_adams, ADAMSu_prevStep, h, 2);

   

    // Максимальные ошибки
    double max_ErrorNP = 0.0;
    double max_ErrorYAP = 0.0;
    double max_ErrorMA = 0.0;

    for (size_t i = 0; i < vecX.size(); ++i) {
        max_ErrorNP = max(max_ErrorNP, abs(u_expl[i] - currVecU[i]));
        max_ErrorYAP = max(max_ErrorYAP, abs(u_impl[i] - currVecU[i]));
        max_ErrorMA = max(max_ErrorMA, abs(u_adams[i] - currVecU[i]));
    }

    // Вывод оценки погрешности
    for (size_t i = 0; i < vecX.size(); ++i) {
        cout << "x = " << vecX[i];
        cout << " | Погрешность Рунге (НП) = " << 3.9 * ErrorNP[i];
        cout << " | Погрешность Рунге (ЯП) = " << 3.9 * ErrorYAP[i];
        cout << " | Погрешность Рунге (МА) = " << 3.9 * ErrorMA[i] << endl;
    }

    cout << " | max_НП = " << max_ErrorYAP;
    cout << " | max_ЯП = " << max_ErrorNP;
    cout << " | max_МА = " << max_ErrorMA << endl;

    return 0;
}
