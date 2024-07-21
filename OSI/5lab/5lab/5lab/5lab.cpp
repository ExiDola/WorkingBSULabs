#include "../header.h"

string path;
int n;
employee* employees;
int a;
vector<HANDLE> hPipes;
vector<HANDLE> hThreads;
vector<HANDLE> hSem;
vector <HANDLE> hMutexRead;
vector<HANDLE> hProcesses;

int retIndex(int id)
{
	for (int i = 0; i < n; i++)
	{
		if (employees[i].num == id)
		{
			return i;
		}
	}
	return -1;
}

DWORD WINAPI ThreadOper(LPVOID pipe)
{
	HANDLE hPipe = (HANDLE)pipe;
	DWORD bytesRead = 0;
	DWORD bytesWrite = 0;

	// Create a structure object to accept from the file
	employee* mess = new employee();
	while (true)
	{

		ReadFile(hPipe, mess, sizeof(employee), &bytesRead, NULL);
		cout << "ID: " << mess->num << " Operation: " << mess->oper << endl;
		cout << retIndex(mess->num) << endl;
		if (mess->oper == 1)
		{

			for (int i = 0; i < a; i++)
			{
				WaitForSingleObject(hSem[retIndex(mess->num)], INFINITE);
			}

			employee* emp = new employee;
			*emp = employees[retIndex(mess->num)];
			bool written = WriteFile(hPipe, emp, sizeof(employee), &bytesWrite, NULL);
			if (written)
			{
				cout << "Data sent" << endl;
			}
			else
			{
				cout << "Data was not sent" << endl;
			}

			bool read = ReadFile(hPipe, emp, sizeof(employee), &bytesWrite, NULL);
			if (!read)
			{
				cout << "Unable to read data" << endl;
			}
			employees[retIndex(mess->num)] = *emp;

			std::ofstream fout(path, std::ios::out);  // Открытие файла для записи
			if (!fout) {  // Проверка на успешное открытие файла
				cout << "Ошибка при открытии файла для записи: " << path << std::endl;
				return 1;  // Возврат кода ошибки
			}

			for (int i = 0; i < n;i++) {
				fout << employees[i].num << " " << employees[i].name << " " << employees[i].hours <<endl;
			}

			int msg;
			read = ReadFile(hPipe, &msg, sizeof(msg), &bytesWrite, NULL);
			if (!read)
			{
				cout << "Unable to read data" << endl;
			}

			if (msg == 1)
			{
				for (int i = 0; i < a; i++)
				{
					ReleaseSemaphore(hSem[retIndex(mess->num)],1,NULL);
				}
			}
		}
		if (mess->oper == 2)
		{
			WaitForSingleObject(hSem[retIndex(mess->num)], INFINITY);

			employee* emp = new employee();
			*emp = employees[retIndex(mess->num)];
			bool written = WriteFile(hPipe, emp, sizeof(employee), &bytesWrite, NULL);
			if (written)
			{
				cout << "Data sent" << endl;
			}
			else
			{
				cout << "Data was not sent" << endl;
			}

			
			int msg;
			bool read = ReadFile(hPipe, &msg, sizeof(msg), &bytesWrite, NULL);
			if (!read)
			{
				cout << "Unable to read data" << endl;
			}
			if (msg == 1 );
			{
				ReleaseSemaphore(hSem[retIndex(mess->num)], 1, NULL);
			}
		}
		if (mess->oper == 3)
		{
			break;
		}
	}

	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	return 0;
}

int main()
{
	setlocale(LC_ALL, "ru");

	path = "text.txt";

	cout << "Enter the number of employees:" << endl;
	cin >> n;

	cout << "Enter the number of clients:" << endl;
	cin >> a;

	employees = new employee[n];
	for (int i = 0; i < n; i++)
	{
		cout << "Enter information about employee " << i + 1 << endl;

		cout << "Enter Id:" << endl;
		cin >> employees[i].num;

		cout << "Enter name:" << endl;
		cin >> employees[i].name;

		cout << "Enter the number of hours worked:" << endl;
		cin >> employees[i].hours;
	}

	ofstream fout(path);
	for (int i = 0; i < n; i++)
	{
		fout << employees[i].num << " " << employees[i].name << " " << employees[i].hours << endl;
	}
	fout.close();

	cout << "All employee data:" << endl;

	ifstream fin(path);
	for (int i = 0; i < n; i++)
	{
		int id;
		string name;
		double hours;
		fin >> id >> name >> hours;

		cout << "ID: " << id << " Name: " << name << " Hours worked: " << hours << endl;
	}
	fin.close();

	hSem.resize(n);
	for (int i = 0; i < n; i++)
	{
		wstring mutexName = L"MutexNum" + to_wstring(i);
		hSem[i] = CreateSemaphore(NULL, a,a, mutexName.c_str());
	}

	/*hMutexRead.resize(n);
	for (int i = 0; i < n; i++)
	{
		wstring mutexName = L"MutexRead" + to_wstring(i);
		hMutexRead[i] = CreateMutex(NULL, FALSE, mutexName.c_str());
	}*/

	hPipes.resize(a);
	hThreads.resize(a);
	hProcesses.resize(a);
	for (int i = 0; i < a; ++i)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		string cmd = "AnotherProc.exe";
		wstring strToWstr = std::wstring(cmd.begin(), cmd.end());
		LPWSTR clientCmdLine = &strToWstr[0];

		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);

		CreateProcess(NULL, clientCmdLine, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		hProcesses[i] = CreateEvent(NULL, FALSE, FALSE, L"Process Started");

		CloseHandle(pi.hProcess);

		hPipes[i] = CreateNamedPipe(L"\\\\.\\pipe\\main",
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			0,
			0,
			INFINITE, NULL);
		hThreads[i] = CreateThread(NULL,
			0,
			ThreadOper,
			static_cast<LPVOID>(hPipes[i]),
			0,
			NULL);
		Sleep(50);
	}
	
	WaitForMultipleObjects(a, hProcesses.data(), TRUE, INFINITE);
	WaitForMultipleObjects(a, hThreads.data(), TRUE, INFINITE);

	cout << "Employees:" << endl;

	fin.open(path);
	for (int i = 0; i < n; i++)
	{
		int id;
		string name;
		double hours;
		fin >> id >> name >> hours;

		cout << "ID: " << id << "Name: " << name << "Hours worked: " << hours << endl << endl;
	}
	fin.close();

	int a;
	cin >> a;

	return 0;
}
