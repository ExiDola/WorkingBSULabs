#include <string>
#include <iostream>
using namespace std;

string longestPalindrome(string s)
{
    string BigString1;
    bool flag = true;
    int n = s.size();
    if (n == 1)
        return s;
    if (n == 2 && s[0] != s[1])
        return s.substr(0, 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
            if (s[i] == s[j])
            {
                for (int k=0; 2 * k < (j-i+1); k++)
                {
                    char f = s[i+k];
                    char sec = s[j-k];
                    if (s[i+k] != s[j - k])
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    if (BigString1.size() < j - i+1)
                    {
                        BigString1 = s.substr(i, j - i+1);
                    }
                }
                flag = true;
            }
    }
    if (BigString1.size() == 0)
        return s.substr(0, 1);
    return BigString1;
}
    
int main()
{
    string s = "aacabdjoojkacaa";
    cout << longestPalindrome(s) << endl;
    return 0;
}
