//защита от двойного включения
#ifndef HEADER_H
#define HEADER_H


#include <fstream>
#include <vector>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>

using namespace std;



struct employee
{
	int num;
	char name[10];
	double hours;
	int oper;

	employee()
	{
		num = 0;
		strcpy_s(name, "");
		hours = 0;
		oper = 0;
	}
};




#endif