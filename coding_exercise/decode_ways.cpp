#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        // Slow
        int numDecodingsRecur(string s) {
            if (s.length() == 0) return 1;

            // First encoding - need to consider '0'
            int ways = 0;
            if (s[1] != '0')
            {
                ways += numDecodings(s.substr(1));
            }
            if (s[0] <= '2' && s[2] != '0')
            {
                stringstream ss(s.substr(0, 2));
                int two_digit; ss >> two_digit;
                if (two_digit >= 1 && two_digit <= 26)
                {
                    // Second encoding
                    ways += numDecodings(s.substr(2));
                }
            }
            return ways;
        }
        // DP
        int numDecodings(string s) {
            if (s.length() == 0) return 0;
            vector<int> dp_cache;
            dp_cache.resize(s.length(), 0);
            if (s[0] >= '1' && s[0] <= '9')
            {
                dp_cache[0] = 1;
            }
            for (unsigned i = 1; i < s.length(); i++)
            {
                int sum = 0;
                if (s[i] != '0')
                {
                    sum += dp_cache[i - 1];
                }
                if (s[i - 1] != '0')
                {
                    stringstream ss(s.substr(i - 1, 2));
                    int two_digit; ss >> two_digit;
                    if (two_digit <= 26)
                    {
                        if (i == 1)
                        {
                            sum += 1;
                        }
                        else
                        {
                            sum += dp_cache[i - 2];
                        }
                    }
                }
                dp_cache[i] = sum;
            }
            return dp_cache[s.length() - 1];
        }
};

void test(string encoded_str)
{
    cout << "Input " << encoded_str << ": ";
    Solution sol;
    cout << sol.numDecodings(encoded_str) << " ways to decode\n";
}

int main()
{
    test("0");
    test("011");
    return 0;
    test("12");
    test("1231");
    test("11023");
    test("9371597631128776948387197132267188677349946742344217846154932859125134924241649584251978418763151253");
}
