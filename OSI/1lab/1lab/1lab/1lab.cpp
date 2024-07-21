#include<string>
#include <iostream>
#include <windows.h>
using namespace std;

int main() 
{
    setlocale(LC_ALL, "rus");
    string str;
    int numOfString = 0;
    cout << "Введите название файла" << endl;
    cin >> str;
    cout << "Ввдите количество записей" << endl;
    cin >> numOfString;


    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    string creatorCmdLine = "Creator.exe " + str + " " + to_string(numOfString);
    wstring cretorCmdLineToLPWSTR = wstring(creatorCmdLine.begin(), creatorCmdLine.end());

    try
    {
        CreateProcess(NULL,   // the path
            &cretorCmdLineToLPWSTR[0],        // Command line LPWSTR format
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory 
            &si,            // Pointer to STARTUPINFO structure
            &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
        );
    }
    catch (const std::exception&)
    {
        cout << "что-то не так с попыткой запуска Creator" << endl;
    }

    return 0;
}
