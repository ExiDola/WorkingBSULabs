#include <vector>
#include<string>
#include <iostream>
#include<algorithm>
#include<set>
using namespace std;

//int Factorial(int i)
//{
//    if (i == 0)
//        return 1;
//    return Factorial(i - 1) * i;
//}
//
//
//bool Check(string str)
//{
//    bool flag = true;
//    size_t targ = 0;
//    while(true)
//    {
//        targ = str.find("()");
//        if (targ == string::npos)
//            break;
//        str.erase(targ, 2);
//        
//    }
//    return str.size()==0;
//}
//
//vector<string> generateParenthesis(int n) 
//{
//    if (n == 1) {
//        vector<std::string> result(1);
//        result[0]= "()";
//        return result;
//    }
//    set<string> mySet;
//    int iterations = Factorial(2 * n) / (Factorial(n + 1) * Factorial(n));
//    string str;
//    for (int i = 0; i < n; i++)
//    {
//        str += "()";
//    }
//    string testStr;
//    for (int i = 0; i < iterations; i++)
//    {
//        for (int k = 1; k < 2 * n-1; k++)
//        {
//            for (int g = 1; g < 2 * n -1; g++)
//            {
//                random_shuffle(str.begin() + 1, str.end() - 1);
//                if (Check(str))
//                {
//                    mySet.insert(str);
//                }
//            }
//        }
//    }
//    vector<string> myVec(mySet.size());
//    int i = 0;
//    for (auto it = mySet.begin(); it != mySet.end(); ++it, i++)
//    {
//        myVec[i]=*it;
//    }
//    return myVec;
//}

void generateParenthesisRecurcion(set<string>& MySet, string str, int openB, int closeB, int n)
{
    if (str.size() == 2 * n)
    {
        MySet.insert(str);
        return;
    }
    if (openB < n)
    {
        generateParenthesisRecurcion(MySet, str + "(", openB + 1, closeB, n);
    }
    if (closeB < openB)
    {
        generateParenthesisRecurcion(MySet, str + ")", openB, closeB+1, n);
    }
}

vector<string> generateParenthesis(int n)
{
    set<string> MySet;
    generateParenthesisRecurcion(MySet, "", 0, 0, n);
    int i = 0;
    vector<string> MyVec(MySet.size());
    for (auto it = MySet.begin(); it != MySet.end(); ++it, i++)
      {
          MyVec[i]=*it;
      }
    return MyVec;
}


int main()
{   
    vector<string> a;
    a = generateParenthesis(4);
    for(int i =0 ;i<a.size();i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}

