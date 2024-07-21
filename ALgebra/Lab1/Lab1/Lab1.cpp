#include<vector>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

void PrintX(vector<vector<double>>& MainVec, vector<double>& Bline, vector<double> xVec)
{
    for (int i = 0; i < MainVec.size(); i++)
    {
        for (int j = 0; j < MainVec[i].size(); j++)
        {
            cout << setw(10) << MainVec[i][j];
        }
        cout << setw(4) <<"(x"<<i+1<<")" << xVec[i];
        cout << setw(20) << "(b" << i + 1 << ")" << Bline[i] << endl;
    }
    cout << endl;
}

void PrintVec(vector<vector<double>>& Vec,string str)
{
    int n = Vec.size();
    cout << str << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(abs(Vec[i][j])<=0.0000000001)
                cout << setw(15) << 0;
            else 
            {
                cout << setw(15) << Vec[i][j];
            }
        }
        cout << endl;
    }
}

vector<double> runThroughMethod(vector<vector<double>>& MainVec, vector<double>& Bline)
{
    int n = MainVec.size();
    vector<double> answer(n);

    vector<double> cPrime(n);
    vector<double> dPrime(n);

    cPrime[0] = MainVec[0][0] / MainVec[0][1];
    dPrime[0] = Bline[0] / MainVec[0][1];

    for (int i = 1; i < n - 1; i++) {
        double m = 1.0 / (MainVec[i][i] - MainVec[i][i - 1] * cPrime[i - 1]);
        cPrime[i] = MainVec[i][i + 1] * m;
        dPrime[i] = (Bline[i] - MainVec[i][i - 1] * dPrime[i - 1]) * m;
    }

    answer[n - 1] = dPrime[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        answer[i] = dPrime[i] - cPrime[i] * answer[i + 1];
    }

    return answer;
}

void Cheker(vector<vector<double>>& L, vector<vector<double>>& U, vector<vector<double>>& A);

void LUDecomposition(vector<vector<double>> MainVec)
{
    int n = MainVec.size();
    vector<vector<double>> U =MainVec;
    vector<vector<double>>  L = MainVec;

    double Multiplaer = 0;


    for (int j = 0; j < n; j++)
    {
        for (int i = j; i < n-1; i++)
        {
            Multiplaer = U[i + 1][j] / U[i][j];
            if (U[i][j] == 0)
                Multiplaer = 0;
            for (int k = j; k < n; k++)
            {
                U[i + 1][k] -= Multiplaer * U[i][k];
 
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            L[i][j] = 0;
        }
    }
    int counter = 1;
    for (int j = 0; j < counter && counter<=n; j++)
    {
        for (int i = j; i < n-1; i++)
        {
            L[i+1][j] /= L[j][j];
        }
        L[j][j] = 1;
        counter++;
    }
    PrintVec(L, "L");
    PrintVec(U, "U");
    

    Cheker(L, U, MainVec);
}


vector<vector<double>> findInverseMatrix(const vector<vector<double>>& mainVec) {
    int n = mainVec.size();
    vector<vector<double>> augmentedMatrix(n, vector<double>(2 * n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmentedMatrix[i][j] = mainVec[i][j];
            if (i == j) {
                augmentedMatrix[i][j + n] = 1.0;
            }
            else 
            {
                augmentedMatrix[i][j + n] = 0.0;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        double chechRight = augmentedMatrix[i][i];
        if (chechRight == 0.0) {
            cerr << "Не удается найти обратную матрицу. Присутствует нулевой элемент на диагонали." << endl;
            return vector<vector<double>>();
        }

        for (int j = 0; j < 2 * n; ++j) {
            augmentedMatrix[i][j] /= chechRight;
        }

        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = augmentedMatrix[k][i];
                for (int j = 0; j < 2 * n; ++j) {
                    augmentedMatrix[k][j] -= factor * augmentedMatrix[i][j];
                }
            }
        }
    }

    vector<vector<double>> inverseMatrix(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverseMatrix[i][j] = augmentedMatrix[i][j + n];
        }
    }

    return inverseMatrix;
}

double QuadroNorm(vector<vector<double>>& MainVec);

void Cheker(vector<vector<double>>&L, vector<vector<double>>&U, vector<vector<double>>&A)
{
    int n = L.size();
    vector<vector<double>> MultipliedAndMinusedMatrix(n, { vector<double>(n, 0.0) });
    double mult = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            for (int k = 0; k < n; k++)
            {
                mult += L[i][k] * U[k][j]; 

            }
            MultipliedAndMinusedMatrix[i][j] = mult; 
            mult = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            MultipliedAndMinusedMatrix[i][j] -= A[i][j];
        }
    }
    double LUNorm = QuadroNorm(MultipliedAndMinusedMatrix);
    cout << "Норма LU-A: " << LUNorm << endl;
}

double QuadroNorm(vector<vector<double>>& MainVec)
{
    double Norm = 0;
    int n = MainVec.size();
    for(int i=0;i<n;i++)
        for (int j = 0; j < n; j++)
        {
            Norm += MainVec[i][j] * MainVec[i][j];
        }
    return sqrt(Norm);
}

int main()
{
    setlocale(LC_ALL, "rus");

    int n = 0;
    cout << "Введите размер матрицы N: " << endl;
    cin >> n;
    vector <vector<double>> mainVec(n,vector<double>(n,0));
    vector<double> Bline(n,0);
    
    mainVec[0][0] = 5;
    mainVec[0][1] = -(1+sqrt(2));
    mainVec[n - 1][n - 2] = -(n + sqrt(n-1));;
    mainVec[n - 1][n - 1] = 5*(n);
    Bline[0] = 3 * sqrt(1);
    Bline[n - 1] = 3 * sqrt(n);

    int helpCounter = n-3;
    for (int i = 1; i < n-1; i++) 
    {
        for (int j = i-1; j < n-helpCounter && j<n; j++)
        {
            if (j == i)
            {
                mainVec[i][i] = 5 * (i+1);
            }
            else
            {
                mainVec[i][j] = -((i + 1) + sqrt(j+1));
            }
            Bline[i] = 3 * sqrt((i + 1));
        }
        helpCounter--;
    }
    vector<double> xVec = runThroughMethod(mainVec, Bline);

    PrintX(mainVec, Bline,xVec);
    LUDecomposition(mainVec);
    vector<vector<double>> inverseMatrix = findInverseMatrix(mainVec);
    
PrintVec(inverseMatrix, "inverseMatrix");
    cout << endl;
    cout << "Число обусловленности: " << QuadroNorm(mainVec) * QuadroNorm(inverseMatrix) << endl;
    return 0;
}
