#include "basic_includes.hpp"

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums)
    {
        int size = nums.size();
        int max_jump = 0;
        for (int i = 0; i < size; i++)
        {
            if (i > max_jump) return false;
            if (i + nums[i] >= size - 1) return true;
            if (i + nums[i] > max_jump)
            {
                max_jump = i + nums[i];
            }
        }
        return false;
    }
};

void test(vector<int> &nums)
{
    print_vector<int>(nums, "Input");
    Solution sol;
    cout << "can jump: " << sol.canJump(nums) << endl;
}

int main()
{
    vector<int> input = {2,3,1,1,4};
    test(input);
    input = {3,2,1,0,4};
    test(input);
    input = {2,0,6,9,8,4,5,0,8,9,1,2,9,6,8,8,0,6,3,1,2,2,1,2,6,5,3,1,2,2,6,4,2,4,3,0,0,0,3,8,2,4,0,1,2,0,1,4,6,5,8,0,7,9,3,4,6,6,5,8,9,3,4,3,7,0,4,9,0,9,8,4,3,0,7,7,1,9,1,9,4,9,0,1,9,5,7,7,1,5,8,2,8,2,6,8,2,2,7,5,1,7,9,6};
    test(input);
    return 0;
}
