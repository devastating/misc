#include "basic_includes.hpp"

using namespace std;

/**
 Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

 You have the following 3 operations permitted on a word:

 a) Insert a character
 b) Delete a character
 c) Replace a character
 */

class Solution {
    public:
        int minDistance(string word1, string word2) 
        {
            size_t w1_len = word1.length(), w2_len = word2.length();
            init_cache(w1_len, w2_len);
            for (size_t i = 1; i <= w1_len; i++)
            {
                for (size_t j = 1; j <= w2_len; j++)
                {
                    minDistanceDP(word1.substr(0, i), word2.substr(0, j));
                }
            }
            return m_cache[w1_len][w2_len];
        }
        int minDistanceDP(string word1, string word2) 
        {
            size_t w1_len = word1.length(), w2_len = word2.length();

            if (w1_len == 0)
            {
                return w2_len;
            }
            if (w2_len == 0)
            {
                return w1_len;
            }

            if (m_cache[w1_len][w2_len] != -1)
            {
                // In cache
                return m_cache[w1_len][w2_len];
            }

            // Insert
            int insert_cost = 1 + minDistanceDP(word1, word2.substr(0, w2_len - 1));
            // Delete
            int del_cost = 1 + minDistanceDP(word1.substr(0, w1_len - 1), word2);
            // Replace
            int replace_cost = minDistanceDP(word1.substr(0, w1_len - 1), word2.substr(0, w2_len - 1));
            if (word1[w1_len - 1] != word2[w2_len - 1])
            {
                replace_cost += 1;
            }
            int res = insert_cost;
            if (res > del_cost) res = del_cost;
            if (res > replace_cost) res = replace_cost;
            m_cache[w1_len][w2_len] = res;
            return res;
        }
        void init_cache(size_t w1_len, size_t w2_len)
        {
            vector<int> init_row;
            init_row.resize(w2_len + 1, -1);
            m_cache.resize(w1_len + 1, init_row);
            for (size_t i = 0; i < w1_len + 1; i++)
            {
                m_cache[i][0] = i;
            }
            for (size_t i = 0; i < w2_len + 1; i++)
            {
                m_cache[0][i] = i;
            }
        }
    private:
        vector<vector<int>> m_cache;
};

void test(string w1, string w2)
{
    Solution sol;
    auto steps = sol.minDistance(w1, w2);
    cout << w1 << " to " << w2 << " requires min " << steps << endl;
}

int main()
{
    test("de", "abc");
    test("abc", "abc");
    test("abd", "abc");
    test("abcb", "abc");
    test("ab", "abc");
    return 0;
}
