#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        bool isAnagram(string s, string t) {
            vector<int> result;

            result.resize(256);
            for (auto s_char: s)
            {
                result[s_char] += 1;
            }
            for (auto t_char: t)
            {
                if (result[t_char] == 0)
                {
                    return false;
                }
                result[t_char] -= 1;
            }
            for (auto iter: result)
            {
                if (iter != 0) return false;
            }
            return true;
        }
};

void test(string s, string t)
{
    cout << "s = " << s << " t = " << t << endl;
    Solution sol;
    bool ret = sol.isAnagram(s, t);
    cout << (ret? "is Anagram": "is not Anagram") << endl;
}

int main()
{
    string s, t;
    s = "cat"; t = "tac";
    test(s, t);
    s = "cat"; t = "tacc";
    test(s, t);
    s = ""; t = "";
    test(s, t);
    s = "abcd"; t = "efg";
    test(s, t);
    return 0;
}
