#include "basic_includes.hpp"

using namespace std;

/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4. 
*/

class Solution {
    public:
        int longestValidParentheses(string s)
        {
            vector<pair<int, char>> paren_stack;

            int max_len = 0;
            int cur_len = 0;
            for (size_t i = 0; i < s.length(); i++)
            {
                auto s_char = s[i];
                if (s_char == ')')
                {
                    if (!paren_stack.empty())
                    {
                        int len = 0;
                        if (paren_stack.size() == 1)
                        {
                            len = i - paren_stack.back().first + 1;
                            cur_len += len;
                            if (cur_len > max_len) max_len = cur_len;
                        }
                        paren_stack.pop_back();
                        if (paren_stack.empty() == false)
                        {
                            int len = i - paren_stack.back().first;
                            if (len > max_len)
                            {
                                max_len = len;
                            }
                        }
                    }
                    else
                    {
                        cur_len = 0;
                    }
                }
                else // s_char == '('
                {
                    pair<int, char> tmp(i, s_char);
                    paren_stack.push_back(tmp);
                }
            }
            if (cur_len > max_len)
            {
                max_len = cur_len;
            }
            return max_len;
        }
};

void test(string in)
{
    Solution sol;
    cout << "input: " << in << " " << sol.longestValidParentheses(in) << endl;
}

int main()
{
    test("()()");
    test(")()()");
    test("()()()");
    test(")()())");
    test(")((()())");
    test("()(()()");
    test("()(())");
    return 0;
}
