
#include <iostream>
#include <string>
#include<vector>
#include<fstream>
#include <cstring>
using namespace std;

struct employee
{
    int num; 
    char name[10]; 
    double hours; 


};

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    string strArg = argv[1];
    int n = stoi(argv[2]);
    n = 2;
    strArg = "text";
    cout << "Введите инофрмацию о сотрудниках" << endl;
    vector<employee> vec(n);
    int number = 0;
    char name_[10];
    double workHours=0;
    cout << strArg << endl;
    int a;
    cin >> a;
    cout << n << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Данные в формате num , name , hours 2" << endl;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> number;
        cin >> name_;
        cin >> workHours;
        vec[i].num = number;
        strcpy_s(vec[i].name, name_);
        vec[i].hours = workHours;
        cout << "Данные в формате num , name , hours2" << endl;
    }

    for (int i = 0; i < n; i++)
    {
        cout << vec[i].num << " " << vec[i].name << " " << vec[i].hours << endl;
    }

    std::ofstream fout(strArg, std::ios::binary);
    for (int i = 0; i < n; i++)
    {
        fout << vec[i].num << " " << vec[i].name << " " << vec[i].hours << endl;
    }

    return 0;
}

