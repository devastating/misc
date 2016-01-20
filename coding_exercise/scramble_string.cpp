#include "basic_includes.hpp"

using namespace std;


class Solution {
    public:
        bool quick_check(const string &s1, const string &s2)
        {
            map<char, int> dedup;
            for (auto char_iter: s1)
            {
                if (dedup.find(char_iter) == dedup.end()) dedup[char_iter] = 1;
                else dedup[char_iter] += 1;
            }
            for (auto char_iter: s2)
            {
                if (dedup.find(char_iter) == dedup.end()) return false;
                else 
                {
                    dedup[char_iter] -= 1;
                    if (dedup[char_iter] == 0) dedup.erase(char_iter);
                }
            }
            return true;
        }
        bool isScramble(string s1, string s2)
        {
            size_t str_len = s1.length();
            if (str_len != s2.length()) return false;
            if (quick_check(s1, s2) != true) return false;
            if (str_len <= 2) return true;
            for (size_t i = 1; i < str_len; i++)
            {
                auto substr1 = s1.substr(0, i);
                auto substr1_2 = s1.substr(i);
                auto substr2 = s2.substr(0, i);
                auto substr2_2 = s2.substr(i);
                if (isScramble(substr1, substr2) && isScramble(substr1_2, substr2_2))
                {
                    return true;
                }
                else
                {
                    substr2 = s2.substr(str_len - i);
                    substr2_2 = s2.substr(0, str_len - i);
                    if (isScramble(substr1, substr2) && isScramble(substr1_2, substr2_2))
                    {
                        return true;
                    }
                }
            }
            return false;
        }
};

void test(string s1, string s2)
{
    cout << s1 << endl << s2 << endl;
    Solution sol;
    cout << "is scramble? " << (sol.isScramble(s1, s2)? "true": "false") << endl;
}

int main()
{
    string s1, s2;

    s1 = "abab";
    s2 = "bbaa";
    test(s1, s2);
    s1 = "abc";
    s2 = "bcc";
    test(s1, s2);
    s1 = "acc";
    s2 = "cac";
    test(s1, s2);
    s1 = "rgeat";
    s2 = "great";
    test(s1, s2);
    s1 = "configuration";
    s2 = "ocnfirguonti";
    test(s1, s2);

    return 0;
}
