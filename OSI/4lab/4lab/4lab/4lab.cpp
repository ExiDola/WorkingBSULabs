#include "../header.h"

using namespace std;

HANDLE pMutex = CreateMutex(NULL, TRUE, L"Global\\pMutex");
HANDLE pSemaphore1 = CreateSemaphore(NULL, 0, 5, L"Global\\semaphore1");
HANDLE pSemaphore2 = CreateSemaphore(NULL, 0, 5, L"Global\\semaphore2");
HANDLE pSemaphore3 = CreateSemaphore(NULL, 0, 5, L"Global\\semaphore3");
HANDLE pSemaphore4 = CreateSemaphore(NULL, 0, 5, L"Global\\semaphore4");

void check()
{
    if (ReleaseSemaphore(pSemaphore1, 0, nullptr) && ReleaseSemaphore(pSemaphore2, 0, nullptr) && ReleaseSemaphore(pSemaphore3, 0, nullptr) && ReleaseSemaphore(pSemaphore4, 0, nullptr))
    {
        pS1 = false;
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
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    string creatorCmdLine = "SecondProc.exe ";
    wstring cretorCmdLineToLPWSTR = wstring(creatorCmdLine.begin(), creatorCmdLine.end());

    try
    {
        if (!CreateProcess(NULL,   // the path
            &cretorCmdLineToLPWSTR[0],        // Command line LPWSTR format
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory 
            &si,            // Pointer to STARTUPINFO structure
            &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
        ))
            throw "что-то не так с попыткой запуска SecondProc";
    }
    catch (const char* mess)
    {
        cout << mess << endl;
    }

    vector <double> vec1;
    vector <double> vec2;
    vector<char> vecOper;

    while (true)
    {
        WaitForSingleObject(pMutex, INFINITE);
        check();
        if (CheckSemaphores())
        {
        vec1 = read1(path1);
        double a = vec1[rand() % 10];
        double b = vec1[rand() % 10];
        cout << endl;
        cout << "Первый процесс" << endl;
        cout<<a<<"  "<< b <<endl;
        cout<<pS1<<"  "<<pS2<<"  "<<pS3<<"  "<<pS4<<endl;
        char operation;
        int i = 0;
        char point;
        vecOper = read2(path3);
        int vecOperTests = static_cast<int>(vecOper[0] - '0');
        cout<<"Номер операции:   "<< vecOperTests << endl;
            operation = vecOper[static_cast<int>(vecOper[0] - '0')];
            cout << operation << endl;
            vecOper[0]++;
            write(vecOper, path3);
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
                    if (oper != NULL && oper !=INT_MIN)
                    {
                        vec2 = read1(path2);
                        vec2[rand() % 10] = oper;
                        write(vec2, path2);
                        couter(vec1, "Первый массив первого процесса:");
                        couter(vec2, "Второй массив первого процесса:");
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
                    Sleep(500);
                    ReleaseMutex(pMutex);
                    
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
    char point;
    vecOper = read2(path3);

    vecOper[0] = '1';

    write(vecOper, path3);

    if (!pS1 && !pS2 && !pS3 && !pS4)
    {
        cout << "Конец работы основного процесса" << endl;
    }

    return 0;
}
