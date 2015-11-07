#include "basic_includes.hpp"

using namespace std;

/**
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut. 
*/

class Solution {
    public:        
        bool is_palindrome(const string &s, int begin, int len)
        {
            int end = begin + len - 1;
            int old_begin = begin, old_end = end;
            bool ret = true;
            if (m_isPa[begin][end] != -1)
            {
                return (m_isPa[begin][end] == 1);
            }

            while (end > begin)
            {
                if (m_isPa[begin][end] == 1)
                {
                    break;
                }
                else if (m_isPa[begin][end] == 0)
                {
                    ret = false;
                    break;
                }
                if (s[begin] != s[end])
                {
                    ret = false;
                    break;
                }
                begin++; end--;
            }
            m_isPa[old_begin][old_end] = ret? 1: 0;
            return ret;
        }

        int minCut(string s) 
        {
            size_t len = s.length();

            // Init the cache
            m_minCut.clear();
            m_minCut.resize(len);   
            m_minCut[0] = 0;
            vector<int> is_palindrome_row;
            is_palindrome_row.resize(len + 1, -1);
            m_isPa.clear();
            m_isPa.resize(len + 1, is_palindrome_row);
            for (size_t i = 0; i < len; i++)
            {
                m_isPa[i][i] = 1;
            }

            for (size_t i = 1; i < len; i++)
            {
                // Find the min
                int min = i;
                for (size_t j = 0; j <= i; j++)
                {
                    bool ret = false;
                    if (m_isPa[j][i] == -1)
                    {
                        ret = is_palindrome(s, j, (i - j + 1));
                        m_isPa[j][i] = ret? 1: 0;
                    }
                    else
                    {
                        ret = (m_isPa[j][i] == 0)? false: true;
                    }
                    if (ret)
                    {
                        // Possible min cut
                        int candidate = 0;
                        if (j != 0)
                        {
                            candidate = 1 + m_minCut[j - 1];
                        }
                        else
                        {
                            candidate = 0;
                        }
                        if (candidate < min)
                        {
                            min = candidate;
                            if (min == 0) break;
                        }
                    }
                }
                m_minCut[i] = min;
            }
            return m_minCut[len - 1];
        }
    private:
        vector<int> m_minCut;
        vector<vector<int>> m_isPa;
};

void test(string in)
{
    Solution sol;
    cout << in << ": " << sol.minCut(in) << endl;;
}

int main()
{
    test("ab");
    test("aab");
    test("aabb");
    test("abba");
    test("aaaaa");
    return 0;
}
