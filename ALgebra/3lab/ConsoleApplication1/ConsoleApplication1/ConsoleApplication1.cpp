#include <vector>
#include<string>
#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;
int n = 3;
const double e = 0.0000001;

void filler(vector <vector<double>>& vec)
{
    int n = vec.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            vec[i][j] = 2 * (i + 1) - (j+1);
            if (i!=j)
            {
                vec[j][i] = 2 * (i + 1)-(j + 1);
            }
        }
    }

}

void couter(vector <vector<double>>& vec)
{
    int n = vec.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(14) << vec[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<double>> multiplyMatrix(const vector<vector<double>>& yakobyMatrix, const vector<vector<double>>& vec) {
    int n = vec.size();
    vector<vector<double>> C(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][k] += yakobyMatrix[i][j] * vec[j][k];
            }
        }
    }

    return C;
}


void YakobiMethod(vector <vector<double>> vec, vector<vector<double>> S) {
    int k = 0;
    int n = vec.size();
    int fir = 0, sec = 0;

    while (true) {
        double maxEl = INT_MIN;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && vec[i][j] != 0) {
                    if (maxEl < abs(vec[i][j]))
                    {
                        maxEl = abs(vec[i][j]);
                        fir = i;
                        sec = j;
                    }
                }
            }
        }
        if (maxEl < e ) {
            cout << "Марица собственных значений: " << endl;
            couter(vec);
            cout << "Марица собственных векторов: " << endl;
            couter(S);
            cout << "Количество итераций: " << k << endl;
            cout << endl;
            break;
        }
        vector<vector<double>> yakobyMatrix(n, vector<double>(n, 0));
        for (int i = 0; i < n; i++) 
        {
            yakobyMatrix[i][i] = 1;
        }
        double alpha = atan2(2.0 * vec[fir][sec], vec[fir][fir] - vec[sec][sec]) / 2.0;
        yakobyMatrix[fir][fir] = yakobyMatrix[sec][sec] = cos(alpha);
        yakobyMatrix[sec][fir] = -sin(alpha);
        yakobyMatrix[fir][sec] = sin(alpha);
        vec = multiplyMatrix(yakobyMatrix, vec);
        swap(yakobyMatrix[sec][fir], yakobyMatrix[fir][sec]);
        vec = multiplyMatrix(vec, yakobyMatrix);
        S = multiplyMatrix(S,yakobyMatrix);
        k++;
    }
}   

vector<double> multiplyMatrixVector(const vector<vector<double>>& matrix, const vector<double>& vector) 
{
    int n = matrix.size();
    std::vector<double> result(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}


double vectorNorm(const std::vector<double>& vector) {
    double sumSquares = 0.0;

    for (double element : vector) {
        sumSquares += element * element;
    }

    return std::sqrt(sumSquares);
}

vector<double> FindedNormed(vector<double>Yvec, double norma)
{
    int n = Yvec.size();
    vector<double> C(n, 0);
    for (int i = 0; i < n; i++)
    {
        C[i] = Yvec[i] / norma;
    }
    return C;
}

vector<double> multVec(double lamb, vector<double> vec)
{
    int n = vec.size();
    vector < double > answ(n, 0);
    for (int i = 0; i < n; i++)
    {
        answ[i] = vec[i] * lamb;
    }
    return answ;
}

vector<double> incremVec(vector<double> vec,vector<double> vec2)
{
    int n = vec.size();
    vector<double> answ(n, 0);
    for (int i = 0; i < n; i++)
    {
        answ[i] = vec[i] - vec2[i];
    }
    return answ;
}

double calculateEigenvalue(vector<double> vec1, vector<double> vec2) {
    int n = vec1.size();
    double lamda=0;
    for (int i = 0; i < n; i++)
    {
        lamda += (vec1[i] * vec2[i]);
    }
    return lamda;
}

void DegreeMethod(vector<vector<double>> vec) 
{
    vector<double> Yvec(n, 0);
    Yvec[0] = 1;
    int k = 0;
    double lamda = 0;
    vector<double> test;
    do
    {   
        test = multiplyMatrixVector(vec, Yvec);
        lamda = calculateEigenvalue(test, Yvec) / calculateEigenvalue(Yvec, Yvec);
        test = FindedNormed(test, vectorNorm(test));
        Yvec = test;
        k++;
    }
    while (vectorNorm(incremVec(multiplyMatrixVector(vec, test), multVec(lamda, test))) > e);

    cout << "Собственные вектор степенного метода: " << std::endl;
    for (int i = 0; i < n; i++)
    {
        cout << Yvec[i] << endl;
    }
    cout<< "Собственное значение степенного метода: " << lamda << std::endl;
    cout << "Количесто итераций: " << k << std::endl;

}


int main()
{
    setlocale(LC_ALL, "rus");
    vector <vector<double>> vec(n, vector<double>(n, 0));
    filler(vec);
    couter(vec);
    vector <vector<double>> testVec = vec;
    vector<vector<double>> OnesMatricx(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++)
    {
        OnesMatricx[i][i] = 1;
    }
    YakobiMethod(testVec,OnesMatricx);
    testVec = vec; 
    DegreeMethod(testVec);
    return 0;
}
