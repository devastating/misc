#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        string shortestPalindrome(string s) {
            size_t idx;
            for (idx = s.length() - 1; idx > 0; idx--)
            {
                // Check if s[0:idx] is palindrome
                int start = 0, end = idx;
                bool valid = true;
                while (end > start)
                {
                    if (s[start] != s[end])
                    {
                        valid = false;
                        break;
                    }
                    start++;
                    end--;
                }
                if (valid) break;
            }
            // We found the best
            if (idx == s.length() - 1)
            {
                return s;
            }
            else
            {
                string result;
                result.resize(s.length() - 1 - idx);
                for (size_t i = 0; i < s.length() - 1 - idx; i++)
                {
                    result[i] = s[s.length() - 1 - i];
                }
                result += s;
                return result;
            }
        }
};

void test(string s)
{
    Solution sol;
    auto res = sol.shortestPalindrome(s);
    //cout << "input: " << s << "\noutput: " << res << endl;
}

int main()
{
    test("caac");
    test("aaa");
    test("aa");
    test("aac");
    test("abc");
    test("abcd");
    test("aacecaaa");
    string test_large;
    test_large.resize(10000000, 'a');
    test(test_large);
    return 0;
}
