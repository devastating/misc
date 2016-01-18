#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        int evalRPN(vector<string>& tokens) {
            vector<int> op_stack;

            for (auto token: tokens)
            {
                if (token == "*")
                {
                    int op1, op2;
                    op2 = op_stack.back(); op_stack.pop_back();
                    op1 = op_stack.back(); op_stack.pop_back();
                    op_stack.push_back(op1 * op2);
                }
                else if (token == "/")
                {
                    int op1, op2;
                    op2 = op_stack.back(); op_stack.pop_back();
                    op1 = op_stack.back(); op_stack.pop_back();
                    op_stack.push_back(op1 / op2);
                }
                else if (token == "+")
                {
                    int op1, op2;
                    op2 = op_stack.back(); op_stack.pop_back();
                    op1 = op_stack.back(); op_stack.pop_back();
                    op_stack.push_back(op1 + op2);
                }
                else if (token == "-")
                {
                    int op1, op2;
                    op2 = op_stack.back(); op_stack.pop_back();
                    op1 = op_stack.back(); op_stack.pop_back();
                    op_stack.push_back(op1 - op2);
                }
                else
                {
                    int op;
                    stringstream ss(token);
                    ss >> op;
                    op_stack.push_back(op);
                }
            }
            if (op_stack.size() != 1)
            {
                cout << "WTF?" << endl;
            }
            return op_stack[0];
        }
};

void test(vector<string> &input)
{
    print_vector(input);
    Solution sol;
    cout << "result: " << sol.evalRPN(input) << endl;
}

int main()
{
    vector<string> input;
    input = {"2", "1", "+", "3", "*"};
    test(input);
    input = {"4", "13", "5", "/", "+"};
    test(input);
    return 0;
}
