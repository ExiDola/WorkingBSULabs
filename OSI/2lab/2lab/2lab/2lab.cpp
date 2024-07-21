#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include <windows.h>
#include<iomanip>
using namespace std;

struct AverageNum
{
    double num;
};

void minMaxThread(std::vector<std::vector<double>>& vec, double& resultNum) 
{
    int min = INT_MAX;
    int max = INT_MIN;
    int i1 = -1, i2 = -1, j1 = -1, j2 = -1;
    for (int i = 0; i < vec[0].size(); i++)
    {
        for (int j = 0; j < vec.size(); j++)
        {
            if (vec[i][j] > max)
            {
                max = vec[i][j];
                i1 = i;
                j1 = j;

            }
            Sleep(7);
            if (vec[i][j] < min)
            {
                min = vec[i][j];
                i2 = i;
                j2 = j;

            }
            Sleep(7);
        }
    }

    if (i1 != -1 && j1 != -1)
    {
        vec[i1][j1] = resultNum;
    }

    if (i2 != -1 && j2 != -1)
    {
        vec[i2][j2] = resultNum;
    }

    std:cout << "Время после выполнения minMax: " << clock() / 1000.0 << endl;
    cout << "Минимальный элемента матрицы: " << min << " Максимальный элемент: " << max << endl;
}

AverageNum averageThread(const std::vector<vector<double>>& vec) {
    int n = vec.size();
    long sum = 0;
    for (int i = 0; i < vec[0].size(); i++)
    {
        for (int j = 0; j < vec.size(); j++)
        {
            sum += vec[i][j];
            Sleep(12);
        }
    }

    double num = sum / (n * n);
    std:cout << "Время после выполнения avarage: " << clock() / 1000.0 << endl;
    cout << "Среднее арифметическое матрицы: " << (double)sum / (n * n) << endl;

    return { num };
}

int main() 
{
    setlocale(LC_ALL, "rus");
    
    int n = 0;
    cout << "Выведите разерность квадратной матрицы:" << endl;
    cin >> n;
    std::vector<std::vector<double>> vec(n, vector<double>(n, 0));

    cout << "Выведите значения матрицы:" << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> vec[i][j];
        }
    }

    cout << "Матрица до вычислений и работы" << endl;
    for (int i = 0; i < vec[0].size(); i++)
    {
        for (int j = 0; j < vec.size(); j++)
        {
            cout << setw(5) << vec[i][j];
        }
        cout << endl;
    }

    AverageNum result;
    std::thread average([&]() { result = averageThread(vec); });
    std:cout<< "Время начале программы: " << clock()/1000.0<<endl;
    std::thread minMax(minMaxThread, std::ref(vec), std::ref(result.num));

    minMax.join();
    average.join();

    cout << "Матрица после" << endl;
    for (int i = 0; i < vec[0].size(); i++)
    {
        for (int j = 0; j < vec.size(); j++)
        {
            cout << setw(5) << vec[i][j];
        }
        cout << endl;
    }

    return 0;
}
