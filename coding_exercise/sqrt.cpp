#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        int mySqrt(int x) {
            
            int64_t low = 0, high = x;
            while(high >= low)
            {
                int64_t med = low + (high - low) / 2;
                int64_t sqr = med * med;
                if (sqr == x) return med;
                if (sqr > x)
                {
                    high = med - 1;
                }
                else
                {
                    low = med + 1;
                }
            }
            return min(high, low);
        }
};

int main()
{
    Solution sol;
    int in;

    in = 2147483647;
    cout << "Input: " << in << " sqrt " << sol.mySqrt(in) << endl;
    in = 16;
    cout << "Input: " << in << " sqrt " << sol.mySqrt(in) << endl;
    in = 4;
    cout << "Input: " << in << " sqrt " << sol.mySqrt(in) << endl;
    in = 5;
    cout << "Input: " << in << " sqrt " << sol.mySqrt(in) << endl;
    in = 2;
    cout << "Input: " << in << " sqrt " << sol.mySqrt(in) << endl;
    return 0;
}
