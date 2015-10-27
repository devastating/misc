#include "basic_includes.hpp"

using namespace std;

// Keep current max/min because min might become max with next num!
// Remember to reset when meeting 0

class Solution {
    public:
        int maxProduct(vector<int>& nums) {
            int best_sum = nums[0], max_sum = 1, min_sum = 1;
            for (auto num: nums)
            {
                max_sum *= num;
                min_sum *= num;
                if (min_sum > max_sum)
                {
                    swap(min_sum, max_sum);
                }
                if (num > max_sum)
                {
                    max_sum = num;
                }
                if (num < min_sum)
                {
                    min_sum = num;
                }
                if (max_sum > best_sum)
                {
                    best_sum = max_sum;
                }
                if (num == 0)
                {
                    max_sum = 1;
                    min_sum = 1;
                }
            }
            return best_sum;
        }
};

void test_case(vector<int> &in)
{
    Solution sol;
    cout << "result: " << sol.maxProduct(in) << endl;;
}

int main()
{
    vector<int> test = {2,3,-2,4};
    test_case(test);
    vector<int> test2 = {-2,0,3};
    test_case(test2);
    vector<int> test3 = {-2,-1,-3, -1};
    test_case(test3);
    vector<int> test4 = {-2,0};
    test_case(test4);
    vector<int> test5 = {3, -1, 4};
    test_case(test5);
    vector<int> test6 = {2, -5, -2, -4, 3};
    test_case(test6);
    return 0;
}
