#include "basic_includes.hpp"
/*
   Given a string s, partition s such that every substring of the partition is a palindrome.

   Return all possible palindrome partitioning of s.

   For example, given s = "aab",
   Return

   [
    ["aa","b"],
    ["a","a","b"]
   ]
 */

using namespace std;

class Solution {
    public:
        bool is_palindrome(const string &s, int begin, int len)
        {
            int end = begin + len - 1;
            bool ret = true;
            while (end > begin)
            {
                if (s[begin] != s[end])
                {
                    ret = false;
                    break;
                }
                begin++; end--;
            }
            return ret;
        }
        vector<vector<string>> partition(string s) 
        {
            vector<vector<string>> ret;

            if (s.length() == 1)
            {
                vector<string> ret_sub = {s};
                ret = {ret_sub};
                return ret;
            }
            for (int i = 0; i < s.length(); i++)
            {
                if (is_palindrome(s, 0, i + 1))
                {
                    auto res = partition(s.substr(i + 1));
                    if (res.empty() == false)
                    {
                        for (auto res_elem: res)
                        {
                            vector<string> new_list = {s.substr(0, i + 1)};
                            for (auto res_elem_str: res_elem)
                            {
                                new_list.push_back(res_elem_str);
                            }
                            ret.push_back(new_list);
                        }
                    }
                    else
                    {
                        vector<string> new_list = {s.substr(0, i + 1)};
                        ret.push_back(new_list);
                    }
                }
            }
            return ret;
        }
};

void test(string in)
{
    cout << "input " << in << endl;
    Solution sol;
    auto res = sol.partition(in);
    for (auto res_elem: res)
    {
        for (auto res_substr: res_elem)
        {
            cout << res_substr << ",";
        }
        cout << endl;
    }
}

int main()
{
    test("abc");
    test("aab");
    test("aaa");
    return 0;
}
