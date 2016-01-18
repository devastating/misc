#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        string addition(string num1, string num2)
        {
            size_t n1_len = num1.size(), n2_len = num2.size();
            size_t iteration = n1_len > n2_len? n1_len: n2_len;
            string res;
            res.resize(iteration);

            int carry = 0;
            for (size_t i = 0; i < iteration; i++)
            {
                int sum = 0;
                if (i < n1_len) sum += num1[n1_len - 1 - i] - '0';
                if (i < n2_len) sum += num2[n2_len - 1 - i] - '0';
                sum += carry;
                carry = sum / 10;
                *(res.rbegin() + i) = '0' + sum % 10;
            }
            if (carry) res.insert(res.begin(), '0' + carry);
            cout << num1 << " " << num2 << " " << res << endl;
            return res;
        }
        string multiply_by_num(string num1, int num)
        {
            int carry = 0;
            string res;
            res.resize(num1.size());
            auto iter = num1.rbegin();
            for (int i = 0; iter < num1.rend(); i++, iter++)
            {
                int digit = (*iter) - '0';
                int total = digit * num + carry;
                carry = total  / 10;
                *(res.rbegin() + i) = '0' + total % 10;
            }
            if (carry) res.insert(res.begin(), '0' + carry);
            cout << num1 << " * " << num << " " << res << endl;
            return res;
        }
        string multiply(string num1, string num2)
        {
            size_t n1_len = num1.size(), n2_len = num2.size();
            size_t iteration = n1_len > n2_len? n1_len: n2_len;
            string sum = "0";

            for (size_t i = 0; i < iteration; i++)
            {
                if (i >= num2.size()) break;
                auto res = multiply_by_num(num1, *(num2.rbegin() + i) - '0');
                res.resize(res.size() + i, '0');
                sum = addition(res, sum);
            }
            bool allzero = true;
            for (auto digit: sum)
            {
                if (digit != '0')
                {
                    allzero = false;
                    break;
                }
            }
            if (allzero) sum.resize(1);
            return sum;
        }
};

void test(string n1, string n2)
{
    cout << "n1=" << n1 << " n2=" << n2 << endl;
    Solution sol;
    cout << "multply is " << sol.multiply(n1, n2) << endl;
}

int main()
{
    string in1, in2;

    in1 = "123";
    in2 = "456";
    test(in1, in2);
    return 0;
    in1 = "99";
    in2 = "99";
    test(in1, in2);
    in1 = "101";
    in2 = "99";
    test(in1, in2);
    in1 = "99";
    in2 = "101";
    test(in1, in2);
    in1 = "0";
    in2 = "101";
    test(in1, in2);
    in1 = "101";
    in2 = "0";
    test(in1, in2);

    return 0;
}
