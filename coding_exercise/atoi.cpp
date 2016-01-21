#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        int myAtoi(string str)
        {
            size_t i, str_len = str.length();
            int res = 0;
            bool is_neg = false;

            for (i = 0; i < str_len; i++)
            {
                if (str[i] != ' ') break;
            }
            // all spaces
            if (i == (str_len)) return res;

            if (str[i] == '+' || str[i] == '-')
            {
                is_neg = str[i] == '-';
                i++;
            }

            for (; i < str_len; i++)
            {
                int range = str[i] - '0';
                if (range < 0 || range > 9)
                {
                    break;
                }
                if (res > 214748364 || res < -214748364)
                {
                    // Overflow
                    res = is_neg? INT_MIN: INT_MAX;
                    break;
                }
                res *= 10;
                if (is_neg)
                {
                    if (res > 0) res *= -1;
                    if ((-1 * range) < (-2147483648 - res))
                    {
                        res = INT_MIN;
                        break;
                    }
                    res -= range;
                }
                else
                {
                    if (range > (2147483647 - res))
                    {
                        res = INT_MAX;
                        break;
                    }
                    res += range;
                }
            }
            return res;
        }
};

void test(string in)
{
    Solution sol;
    cout << "Input: " << in << " atoi " << sol.myAtoi(in) << endl;
}

int main()
{
    test("1234");
    test("+1234");
    test("-1234");
    test("   -1234");
    test("   -1234ab");
    test("   ");
    test("   +");
    test("abcd");
    test("2147483648");
    test("-2147483647");
    test("-2147483649");
    test("      -11919730356x");
    return 0;
}
