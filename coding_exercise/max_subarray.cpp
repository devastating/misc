#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        int maxSubArray(vector<int>& nums) {
            int best_sum = nums[0], current_sum = 0;
            for (auto num: nums)
            {
                if (current_sum < 0)
                {
                    current_sum = num;
                }
                else
                {
                    current_sum += num;
                }
                if (current_sum > best_sum)
                {
                    best_sum = current_sum;
                }
            }
            return best_sum;
        }
};

void test_case(vector<int> &in)
{
    Solution sol;
    cout << "result: " << sol.maxSubArray(in) << endl;;
}

int main()
{
    vector<int> test = {-2,1,-3,4,-1,2,1,-5,4};
    test_case(test);
    vector<int> test2 = {-2,-1,-3};
    test_case(test2);
    vector<int> test3 = {2,1,3};
    test_case(test3);
    return 0;
}
