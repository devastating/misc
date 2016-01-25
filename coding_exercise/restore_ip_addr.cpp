#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        vector<string> restoreIpAddresses(string s) 
        {
            return restoreIpAddresses(s, 0);
        }
        vector<string> restoreIpAddresses(string s, int found) 
        {
            vector<string> res;
            if (found == 3)
            {
                stringstream ss(s);
                int val; ss >> val;
                if (val < 0 || val > 255) return res;
                if (s[0] == '0' && s.length() > 1) return res;
                res.push_back(s);
            }

            for (int i = 1; i < 4; i++)
            {
                if (s.length() <= i) break;
                if (s[0] == '0' && i > 1) break;
                stringstream ss(s.substr(0, i));
                int val; ss >> val;
                if (val < 0 || val > 255) continue;
                auto sub_result = restoreIpAddresses(s.substr(i), found + 1);
                if (sub_result.empty()) continue;
                for(auto sub_result_iter: sub_result)
                {
                    res.push_back(s.substr(0, i) + "." + sub_result_iter);
                }
            }
            return res;
        }
};

void test(string s)
{
    cout << "Input: " << s << endl;
    Solution sol;
    auto res = sol.restoreIpAddresses(s);
    print_vector(res, "Output");
}

int main()
{
    string in;

    in = "25525511135";
    test(in);
    in = "10525511135";
    test(in);
    in = "101011135";
    test(in);
    in = "101911135";
    test(in);
    in = "0000";
    test(in);
    in = "10011135";
    test(in);
    in = "010010";
    test(in);

    return 0;
}
