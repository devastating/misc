#include "basic_includes.hpp"

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums)
    {
        int furthest = nums[0];
        int future_furthest = furthest;
        int cache1 = 0, cache0 = 0;
        int res = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            if (i <= furthest)
            {
                res = cache0 + 1;
            }
            else if (i <= future_furthest)
            {
                res = cache1 + 1;
                cache0 = cache1;
                furthest = future_furthest;
            }

            if (nums[i] + i > future_furthest)
            {
                cache1 = res;
                future_furthest = nums[i] + i;
            }
        }
        return res;
    }
};

void test(vector<int> &nums)
{
    print_vector<int>(nums, "Input");
    Solution sol;
    cout << "min jump: " << sol.jump(nums) << endl;
}

int main()
{
    vector<int> input = {2,3,1,1,4};
    test(input);
    input = {2,3,4,0, 1};
    test(input);
    return 0;
}
