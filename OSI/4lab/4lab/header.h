#ifndef HEADER_H
#define HEADER_H

#include<Windows.h>
#include<vector>
#include<fstream>
#include<string>
#include <iostream>
#include<fstream>
#include<time.h>

using namespace std;

string path1 = "../../file1.txt";
string path2 = "../../file2.txt";
string path3 = "../../inputOperations.txt";


bool pS1 = true;
bool pS2 = true;
bool pS3 = true;
bool pS4 = true;



bool CheckSemaphores()
{
    if (pS1 || pS2 || pS3 || pS4)
		return true;
	else
		return false;
}

void couter(vector<double> vec,const char* mess)
{
    cout << mess << endl;
    for (int i = 0; i < 10; i++)
    {
		cout << vec[i] << " ";
	}
	cout << endl;
}


vector<double> read1(string path)
{
	vector<double> vec;
	double temp;
	ifstream fin(path);
	while (fin >> temp)
	{
		vec.push_back(temp);
	}
	return vec;
}

vector<char> read2(string path)
{
	vector<char> vec;
	char temp;
	ifstream fin(path);
	while (fin >> temp)
	{
		vec.push_back(temp);
	}
	return vec;
}

template <typename T>
void write(vector<T> vec, string path)
{
	ofstream fout(path);
	for (int i = 0; i < vec.size(); i++)
	{
		fout << vec[i] << endl;
	}
	fout.close();
}

#endif // HEADER_H