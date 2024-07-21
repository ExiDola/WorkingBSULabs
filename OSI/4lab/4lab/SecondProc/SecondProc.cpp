#include "../header.h"
using namespace std;

//отерытие глобальных семафоров
HANDLE pSemaphore1 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Global\\semaphore1");
HANDLE pSemaphore2 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Global\\semaphore2");
HANDLE pSemaphore3 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Global\\semaphore3");
HANDLE pSemaphore4 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Global\\semaphore4");
HANDLE pMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"Global\\hMutex");

void check()
{
    if (ReleaseSemaphore(pSemaphore1, 0, nullptr) && ReleaseSemaphore(pSemaphore2, 0, nullptr) && ReleaseSemaphore(pSemaphore3, 0, nullptr) && ReleaseSemaphore(pSemaphore4,0, nullptr))
    {
        pS1= false;
        pS2 = false;
        pS3 = false;
        pS4 = false;
    }
    ReleaseSemaphore(pSemaphore1, 0, nullptr);
    ReleaseSemaphore(pSemaphore2, 0, nullptr);
    ReleaseSemaphore(pSemaphore3, 0, nullptr);
    ReleaseSemaphore(pSemaphore4, 0, nullptr);
}

double Operation1(double a, double b, char operation)
{
    LONG prev_count;
    if (operation == '+')
    {
        if (ReleaseSemaphore(pSemaphore1, 1, &prev_count))
        {
            if (prev_count == 5)
            {
                pS1 = false;
            }
            ReleaseSemaphore(pSemaphore1, 0, &prev_count);
            return a + b;
        }
        else
        {
            ReleaseSemaphore(pSemaphore1, 0, &prev_count);
            {
                pS1 = false;
                return NULL;
            }
        }
    }
    else if (operation == '-')
    {
        if (ReleaseSemaphore(pSemaphore2, 1, &prev_count))
        {
            if (prev_count == 5)
            {
                pS2 = false;
            }
            ReleaseSemaphore(pSemaphore2, 0, &prev_count);
            return a - b;
        }
        else
        {
            ReleaseSemaphore(pSemaphore2, 0, &prev_count);

            pS2 = false;
            return NULL;
        }
    }
    else if (operation == '*')
    {
        if (ReleaseSemaphore(pSemaphore3, 1, &prev_count))
        {
            if (prev_count == 5)
            {
                pS3 = false;
            }
            ReleaseSemaphore(pSemaphore3, 0, &prev_count);
            return a * b;
        }
        else
        {
            ReleaseSemaphore(pSemaphore3, 0, &prev_count);
            pS3 = false;
            return NULL;
        }
    }
    else if (operation == '/')
    {
        if (ReleaseSemaphore(pSemaphore4, 1, &prev_count))
        {
            if (prev_count == 5)
            {
                pS4 = false;
            }
            if (b == 0)
            {
                cout << "Деление на ноль" << endl;
                ReleaseSemaphore(pSemaphore4, 0, &prev_count);
                return a;
            }
            else
                ReleaseSemaphore(pSemaphore4, 0, &prev_count);
            return a / b;
        }
        else
        {
            ReleaseSemaphore(pSemaphore4, 0, &prev_count);
            pS4 = false;
            return NULL;
        }
    }
    else
    {
        pS4 = false;
        return NULL;
    }
}


int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    
    vector <double> vec1;
    vector <double> vec2;
    vector<char> vecOper;

    while (true)
    {
        WaitForSingleObject(pMutex, INFINITE);
        check();
        if (CheckSemaphores())
        {
        vec1 = read1(path2);
        double a = vec1[rand() % 10];
        double b = vec1[rand() % 10];
        cout << endl;
        cout << "Втрой процесс" << endl;
        cout << a << "  " << b << endl;
        cout << pS1 << "  " << pS2 << "  " << pS3 << "  " << pS4 << endl;
        char operation;
        int i = 0;
        char point;
            vecOper = read2(path3);
            int vecOperTests = static_cast<int>(vecOper[0] - '0');
            cout << "Номер операции:   " << vecOperTests << endl;
            operation = vecOper[static_cast<int>(vecOper[0] - '0')];
            cout << operation << endl;
            vecOper[0]++;
            write(vecOper,path3);

            if (operation == 'e')
            {
                cout << "Закончились операции в файле" << endl;
                ReleaseMutex(pMutex);
                break;
            }
            else
            {
                if (CheckSemaphores())
                {
                    double oper = Operation1(a, b, operation);
                    cout << oper << endl;
                    if (oper != NULL)
                    {
                        vec2 = read1(path1);
                        vec2[rand() % 10] = oper;
                        write(vec2, path1);
                        couter(vec2, "Первый массив второго процесса:");
                        couter(vec1, "Второй массив втрого процесса:");
                        cout << endl << endl;
                        cout << endl << endl;
                        Sleep(500);
                        ReleaseMutex(pMutex);
                    }
                    else
                    {

                        cout << endl;
                        cout << "Пропускаем операцию" << endl;
                        cout << endl;
                        Sleep(500);
                        ReleaseMutex(pMutex);
                    }
                }
                else
                {
                    ReleaseMutex(pMutex); 
                    Sleep(500);
                    break;
                }
            }
        }
        else
        {
            Sleep(500);
			ReleaseMutex(pMutex);
			break;
		}
    }

    if (!pS1 && !pS2 && !pS3 && !pS4)
    {
        cout << "Конец работы втрого процесса" << endl;
    }
    
    return 0;
}
