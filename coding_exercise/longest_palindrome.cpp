#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        string longestPalindrome(string s) {
            int max = 1;
            int s_len = s.length();
            string ret;

            if (s_len == 0) return "";
            if (s_len == 1) return s;

            for (int i = 0; i < s.length(); i++)
            {
                int j = i;
                int k = i;
                while (j < (s_len - 1) && s[j + 1] == s[i]) j++;
                while (k > 0 && j < (s_len - 1))
                {
                    if (s[k - 1] != s[j + 1])
                    {
                        break;
                    }
                    k--;
                    j++;
                }
                int len = j - k + 1;
                if (s[k] != s[j])
                {
                    len -= 2;
                    k++;
                    j--;
                }
                if (len > max) 
                {
                    max = len;
                    ret = s.substr(k, len);
                }
            }
            return ret;
        }
};

void test(string input)
{
    cout << "Input " << input << " : ";
    Solution sol;
    cout << sol.longestPalindrome(input) << endl;
}

int main()
{
    test("aba");
    test("abc");
    test("bb");
    test("lkflaaaalfkl");
    return 0;
}
