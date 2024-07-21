#include <string>

#include <iostream>

using namespace std;

bool isSubsequence(string s, string t) 
{
    int i = 0;
    for (int k =0; i < s.size(), k<t.size(); k++)
    {
        if (t[k] == s[i])
            i++;

    }
    return i != s.size();
}




int main()
{
    string t = "ahbgdc";
    string s = "acd";
    if (isSubsequence(s, t))
        cout << "da" << endl;
    else
        cout << "no" << endl;
    return 0;
}

