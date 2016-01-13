#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        string simplifyPath(string path) {

            vector<string> path_stack;
            size_t path_len = path.length();

            for (size_t i = 0; i < path_len; i++)
            {
                if (path[i] == '/') continue;

                size_t begin = i;
                string token;
                while (i < path_len)
                {
                    if (path[i] == '/')
                    {
                        token = path.substr(begin, i - begin);
                        break;
                    }
                    if (i == path_len - 1)
                    {
                        token = path.substr(begin);
                        break;
                    }
                    i++;
                }
                if (token == "..")
                {
                    if (!path_stack.empty()) path_stack.pop_back();
                }
                else if (token != ".")
                {
                    path_stack.push_back(token);
                }
            }
            string ret;
            for (auto item: path_stack)
            {
                ret += "/" + item;
            }
            if (ret.empty()) ret = "/";
            return ret;
        }
};

void test(string path)
{
    cout << "original path " << path << endl;
    Solution sol;
    cout << "simplified: " << sol.simplifyPath(path) << endl;
}

int main()
{
    string input;
    input = "/home/";
    test(input);
    input = "/home/..";
    test(input);
    input = "////home/..";
    test(input);
    input = "/home///.././home";
    test(input);
    input = "/home///.././home/../../../..///";
    test(input);
    input = "/...";
    test(input);
    input = "/.../";
    test(input);
    input = "/...abc/";
    test(input);
    input = "/..abc";
    test(input);
    return 0;
}
