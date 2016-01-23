#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        bool isValid(int64_t a, int64_t b, string &num, int begin)
        {
            int64_t sum = a + b;

            //cout << a << " " << b << " " << num.substr(begin) << endl;

            if (begin == num.size()) return true;
            if (num[begin] == '0') return false;

            stringstream ss; ss << sum;

            if (ss.str() == num.substr(begin, ss.str().length()))
            {
                return isValid(b, sum, num, begin + ss.str().length());
            }
            else
            {
                return false;
            }
        }
        bool isAdditiveNumber(string num)
        {
            if (num.length() < 3) return false;
            for (int i = 0; i < num.length() - 2; i++)
            {
                if (num[0] == '0' && i > 0) break;
                for (int j = 1; j < num.length() - i - 1; j++)
                {
                    int64_t a, b;
                    if (num[i + 1] == '0' && j > 1) break;
                    stringstream ss(num.substr(0, i + 1));ss >> a;
                    //ss << num.substr(0, i + 1); ss >> a;
                    stringstream ss2(num.substr(i + 1, j));ss2 >> b;
                    //ss << num.substr(i + 1, j); ss >> b;
                    //cout << a << " " << b << endl;
                    if (isValid(a, b, num, i + 1 + j))
                    {
                        return true;
                    }
                }
            }
            return false;
        }
};

void test(string in)
{
    Solution sol;
    cout << "Input: " << in << " " << sol.isAdditiveNumber(in) << endl;
}

int main()
{
    string in;

    in = "121474836472147483648";
    test(in);

    in = "112";
    test(in);
    in = "11";
    test(in);
    in = "112358";
    test(in);
    in = "199100199";
    test(in);
    in = "0";
    test(in);
    in = "0123";
    test(in);
    in = "1023";
    test(in);
    in = "101";
    test(in);
    in = "011235";
    test(in);

    return 0;
}
