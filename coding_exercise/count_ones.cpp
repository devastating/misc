#include "basic_includes.hpp"

using namespace std;


class Solution {
    public:
        int countDigitOne(int n)
        {
            if (n <= 0) return 0;
            if (n < 10) return 1;
            int value = n;
            int div = 1;
            int sum = 0;
            while (value)
            {
                int current_digit = value % 10;
                value /= 10;
                if (current_digit == 0)
                {
                    sum += value * div;
                }
                else if (current_digit == 1)
                {
                    sum += value * div;
                    sum += n % div + 1;
                }
                else
                {
                    sum += (value + 1) * div;
                }
                div *= 10;
            }
            return sum;
        }
};

void test(int input)
{
    Solution sol;
    cout << "Input: " << input << " " << sol.countDigitOne(input) << endl;
}

int main()
{
    test(-1);
    test(0);
    test(19);
    test(99);
    test(109);
    test(119);
    test(209);
    test(319);
    test(999);
    test(5746);
    return 0;
}
