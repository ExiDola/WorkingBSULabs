#include <iostream>
#include <windows.h>
#include<random>
#include <cstdlib>
#include<ctime>
#include <thread>
#include<vector>
using namespace std;

int SIZEVEC = 10;

vector<int> vec1(SIZEVEC, 0);
vector<int> vec2(SIZEVEC, 0);

HANDLE hMutex = CreateMutex(NULL, TRUE, L"mainMutex");

void PrintVector(vector<int> vec, const char* mess,int i)
{
    cout<< mess <<"---On the step:"<< i << endl;
    for (int i = 0; i < SIZEVEC; i++)
    {
		cout << vec[i] << " ";
	}
	cout << endl;
    cout << endl;
}

void firstThread()
{
    for (int k = 0; k < 10; k++)
    {
        WaitForSingleObject(hMutex, INFINITE);
        int a, b;
        int sum = vec1[rand() % SIZEVEC] + vec1[rand() % SIZEVEC];
        vec2[rand() % SIZEVEC] = sum;
        Sleep(50);
        PrintVector(vec2, "From first thread", k);
        ReleaseMutex(hMutex);
       
    }
}

void secThread()
{
    for (int k = 0; k < 10; k++)
    {
	WaitForSingleObject(hMutex, INFINITE);
    int sum = vec2[rand() % SIZEVEC] + vec2[rand() % SIZEVEC];
    vec1[rand() % SIZEVEC] = sum;
    Sleep(50);
    PrintVector(vec1, "From second thread", k);
	ReleaseMutex(hMutex);
    }
}

int main()
{
    srand(time(nullptr));
    for (int i = 0; i < SIZEVEC; i++)
    {
        int a = rand() % 50;
        vec1[i] = a;
        a = rand() % 50;
        vec2[i] = a;
    }

    ReleaseMutex(hMutex);
    thread firstThreadObj(firstThread);
    thread secThreadObj(secThread);


    secThreadObj.join();
    firstThreadObj.join();

    CloseHandle(hMutex);

    return 0;
}
