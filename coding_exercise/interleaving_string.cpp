#include "basic_includes.hpp"

using namespace std;

void debug_cache(vector<vector<bool>> &cache)
{
    return;
    cout << "DEBUG\n";
    for (auto row: cache)
    {
        print_vector<bool>(row, "Cache");
    }
}

class Solution {
    public:
        bool isInterleave(string s1, string s2, string s3)
        {
            int s1_len = s1.length();
            int s2_len = s2.length();
            int s3_len = s3.length();

            if (s1_len + s2_len != s3_len) return false;
            if (!s1_len && !s3_len && !s2_len) return true;

            vector<vector<bool>> cache;
            vector<bool> cache_row;
            cache_row.resize(s2_len + 1, false);
            cache.resize(s1_len + 1, cache_row);

            // Initialization
            for (int i = 1; i <= s1_len; i++)
            {
                if (s1.substr(0, i) == s3.substr(0, i))
                {
                    cache[i][0] = true;
                }
            }
            for (int i = 1; i <= s2_len; i++)
            {
                if (s2.substr(0, i) == s3.substr(0, i))
                {
                    cache[0][i] = true;
                }
            }

            for (int i = 1; i <= s1_len; i++)
            {
                for (int j = 1; j <= s2_len; j++)
                {
                    if (s1[i - 1] == s3[i + j - 1] && cache[i - 1][j])
                    {
                        cache[i][j] = true;
                    }
                    else if (s2[j - 1] == s3[i + j - 1] && cache[i][j - 1])
                    {
                        cache[i][j] = true;
                    }
                }
            }
            return cache[s1_len][s2_len];
        }
        bool isInterleaveRecursive(string s1, string s2, string s3)
        {
            if (s3.empty())
            {
                return (s1.empty() && s2.empty());
            }

            if (s2.empty() == false && s3.back() == s2.back())
            {
                bool res = isInterleave(s1, s2.substr(0, s2.length() - 1),
                                        s3.substr(0, s3.length() - 1));
                if (res) return true;
            }
            if (s1.empty() == false && s3.back() == s1.back())
            {
                return isInterleave(s1.substr(0, s1.length() - 1), s2,
                                    s3.substr(0, s3.length() - 1));
            }
            return false;
        }
};

void test(string s1, string s2, string s3)
{
    cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3 << endl;
    Solution sol;
    cout << sol.isInterleave(s1, s2, s3) << endl;
}

int main()
{
    string s1, s2, s3;

    s1 = "aabcc";
    s2 = "dbbca";
    s3 = "aadbbcbcac";
    test(s1, s2, s3);
    s3 = "aadbbbaccc";
    test(s1, s2, s3);

    s1 = "a";
    s2 = "";
    s3 = "a";
    test(s1, s2, s3);
    return 0;
}
