#include<fstream>
#include <iostream>
#include<vector>
using namespace std;

int leftElement(vector <int>& myVec, int question, int& b)
{
    int l = 0, r = myVec.size();
    int mid = 0;
    while (l < r)
    {
        mid = (l + r) / 2;
        if (myVec[mid] < question)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    return r;
}

int RightElement(vector <int>& myVec, int question)
{
    int l = 0, r = myVec.size();
    int mid = 0;
    while (l < r)
    {
        mid = (l + r) / 2;
        if (myVec[mid] > question)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return l;
}


int main()
{
    int n = 0;
    cin >> n;
    vector <int> MyVec(n);
    int test = 0;
    for (int i = 0; i < n ; i++)
    {
        cin >> test;
        MyVec[i] = test;
    }
    int k = 0;
    cin >> k;
    int question = 0;
    int b = 0, l = 0, r = 0;
    for (int i = 0; i < k; i++)
    {
        cin >> question;
        l = leftElement(MyVec, question,b);
        r = RightElement(MyVec, question);
        cout << b << " " << l << " " << r << endl;
        b = 0;
    }
    return 0;
}



//for (int i = 0; i < k; i++)
//{
//    cin >> question;
//    int left = 0;
//    bool maxAndMin = true;
//    int right = MyVec.size();
//    int mid = 0;
//    bool flag = false;
//    if (question > MyVec[n - 1])
//    {
//        l = n;
//        r = n;
//        cout << b << " " << l << " " << r << endl;
//        continue;
//    }
//    else if (question < MyVec[0])
//    {
//        l = 0;
//        r = 0;
//        cout << b << " " << l << " " << r << endl;
//        continue;
//    }
//    else {
//        while (left <= right)
//        {
//            mid = left + (right - left) / 2;
//            if (MyVec[mid] == question)
//            {
//                flag = true;
//                break;
//            }
//            else if (MyVec[mid] > question)
//            {
//                right = mid - 1;
//            }
//            else if (MyVec[mid] < question)
//            {
//                left = mid + 1;
//            }
//        }
//        if (flag)
//        {
//            b = 1;
//            l = mid;
//            r = mid + 1;
//            if (mid != 0)
//            {
//                if (MyVec[mid] == question)
//                {
//                    while (MyVec[mid] == question && mid > 0)
//                    {
//                        mid--;
//                    }
//                    l = mid;
//                    if (MyVec[mid] != question)
//                    {
//                        l += 1;
//                    }
//                    if (r < n)
//                    {
//                        while (MyVec[r] == question)
//                        {
//                            r++;
//                            if (r == n)
//                                break;
//                        }
//                    }
//                }
//            }
//        }
//        else
//        {
//            l = mid + 1;
//            r = mid + 1;
//        }
//        cout << b << " " << l << " " << r << endl;
//        maxAndMin = true;
//        flag = false;
//        b = 0;
//    }
//}