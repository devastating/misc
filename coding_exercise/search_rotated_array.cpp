#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        int search(vector<int>& nums, int target)
        {
            int len = nums.size();
            int begin = 0, end = len - 1;
            int res = -1;

            if (len == 0) return res;

            while (end >= begin)
            {
                unsigned mid = begin + (end - begin) / 2;

                if (nums[mid] == target)
                {
                    res = mid;
                    break;
                }
                if (nums[mid] >= nums[begin])
                {
                    if (target > nums[mid] || target < nums[begin])
                    {
                        begin = mid + 1;
                    }
                    else
                    {
                        end = mid - 1;
                    }
                    continue;
                }
                else
                {
                    if (target > nums[mid] && target <= nums[end])
                    {
                        begin = mid + 1;
                    }
                    else
                    {
                        end = mid - 1;
                    }
                    continue;
                }
            }
            return res;
        }
};

void test(vector<int>& nums, int target)
{
    print_vector<int>(nums);
    Solution sol;
    cout << "Found " << target << " at index " << sol.search(nums, target) << endl;
}

int main()
{
    vector<int> nums;

    nums = {4, 5, 6, 7, 0, 1, 2};
    test(nums, 0);
    test(nums, 3);
    test(nums, 8);
    test(nums, -1);
    nums = {};
    test(nums, 5);
    nums = {1};
    test(nums, 5);
    test(nums, 1);
    nums = {3, 1};
    test(nums, 1);
    return 0;
}
