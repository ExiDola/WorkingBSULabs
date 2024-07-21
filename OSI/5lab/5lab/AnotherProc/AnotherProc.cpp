#include "../header.h"

int main(int argc, char* argv)
{
	setlocale(LC_ALL, "ru");

	HANDLE hEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, L"Process Started");
	SetEvent(hEvent);

	HANDLE hPipe = CreateFile(L"\\\\.\\pipe\\main", GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

	int ans = 0;
	while (true)
	{
		cout << "Choose the method" << endl << "1. Modify entry" << endl << "2. Read entry" << endl << "3. Terminate process" << endl;

		cin >> ans;

		if (ans == 1)
		{
			DWORD bytesWriten = 0;
			DWORD bytesRead = 0;

			int ID;
			cout << "Enter employee ID: ";
			cin >> ID;

			employee* emp1 = new employee();
			emp1->num = ID;
			emp1->oper = ans;
			bool writen = WriteFile(hPipe, emp1, sizeof(employee), &bytesWriten, NULL);

			if (writen)
			{
				cout << "Message sent" << endl;
			}
			else
			{
				cout << "Message was not sent" << endl;
			}

			employee* emp = new employee();
			bool read = ReadFile(hPipe, emp, sizeof(employee), &bytesRead, NULL);
			if (!read)
			{
				cout << "Message was not read" << endl;
			}

			if (emp->num == ID)
			{
				cout << "ID: " << emp->num << endl << "Name: " << emp->name << endl << "Hours worked: " << emp->hours << endl;

				cout << "Enter new name: ";
				cin >> emp->name;

				cout << "Enter new number of hours worked: ";
				cin >> emp->hours;
			}

			string str;

			while (true)
			{
				cout << "Send x, if u want to stop the work with this element"<<endl;
				cin >> str;

				if (str == "x")
				{
					break;
				}
			}

			writen = WriteFile(hPipe, emp, sizeof(employee), &bytesWriten, NULL);
			if (writen)
			{
				cout << "Сообщение отправлено\n";
			}
			else
			{
				cout << "Сообщение не было отправлено\n";
			}

			int msg = 1;
			WriteFile(hPipe, &msg, sizeof(msg), &bytesWriten, NULL);
			delete emp;
		}
		else if (ans == 2)
		{
			DWORD bytesWritten = 0;
			DWORD bytesRead = 0;

			int ID;
			cout << "Enter employee ID: ";
			cin >> ID;

			employee* emp1 = new employee();
			emp1->num = ID;
			emp1->oper = ans;
			bool writen = WriteFile(hPipe, emp1, sizeof(employee), &bytesWritten, NULL);
			if (writen)
			{
				cout << "Message sent" << endl;
			}
			else
			{
				cout << "Message was not sent" << endl;
			}

			employee* emp = new employee();
			bool read = ReadFile(hPipe, emp, sizeof(employee), &bytesRead, NULL);
			if (!read)
			{
				cout << "Message was not read" << endl;
			}

			if (emp->num == ID)
			{
				cout << "ID: " << emp->num << endl << "Name: " << emp->name << endl << "Hours worked: " << emp->hours << endl;
			}

			string str;

			while (true)
			{
				cout << "Send x, if u want to stop the work with this element"<<endl;
				cin >> str;

				if (str == "x")
				{
					break;
				}
			}

			int msg = 1;
			WriteFile(hPipe, &msg, sizeof(msg), &bytesWritten, NULL);
		}
		else if (ans == 3)
		{
			DWORD bytesWritten;
			DWORD bytesRead;

			employee* emp1 = new employee();
			emp1->num = 0;
			emp1->oper = ans;
			bool writen = WriteFile(hPipe, emp1, sizeof(employee), &bytesWritten, NULL);
			if (writen)
			{
				cout << "Message sent" << endl;
			}
			else
			{
				cout << "Message was not sent" << endl;
			}

			break;
		}
		else
		{
			cout << "Invalid input. Try again" << endl << endl;
		}
	}

	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	return 0;
}
