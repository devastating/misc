#include "basic_includes.hpp"

using namespace std;

/**
 Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ? s. If there isn't one, return 0 instead.

 For example, given the array [2,3,1,2,4,3] and s = 7,
 the subarray [4,3] has the minimal length under the problem constraint. 
 */

class Solution {
    public:
        int minSubArrayLen(int s, vector<int>& nums)
        {
            int begin = 0, end, sum = 0;
            int res = nums.size() + 1;

            for (end = 0; end < nums.size(); end++)
            {
                sum += nums[end];
                if (sum >= s)
                {
                    int subarray_len = end - begin + 1;
                    if (subarray_len < res)
                    {
                        res = subarray_len;
                    }
                    if (nums[end] > nums[begin])
                    {
                        //cout << begin << " - " << end << endl;
                        while (sum - nums[begin] >= s)
                        {
                            sum -= nums[begin];
                            begin++;
                        }
                        subarray_len = end - begin + 1;
                        if (subarray_len < res)
                        {
                            //cout << "shrink to " << begin << " - " << end << endl;
                            res = subarray_len;
                        }
                    }
                }
            }
            if (res == nums.size() + 1) return 0;
            else return res;
        }
};

void test(int s, vector<int> &nums)
{
    Solution sol;
    cout << "num " << s << endl;
    for (auto num: nums)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << "result: " << sol.minSubArrayLen(s, nums) << endl;;
}

int main()
{
    vector<int> test_input = {2,3,1,2,4,3};
    test(7, test_input);
    test(100, test_input);
    test(4, test_input);
    return 0;
}
