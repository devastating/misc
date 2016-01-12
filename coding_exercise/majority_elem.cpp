#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        int majorityElement(vector<int>& nums) {
            int thresh = nums.size() / 2;
            unordered_map<int, int> record;

            for (auto num: nums)
            {
                if (record.find(num) == record.end())
                {
                    record[num] = 1;
                    if (thresh < 1)
                    {
                        return num;
                    }
                }
                else
                {
                    record[num] += 1;
                    if (record[num] > thresh)
                    {
                        return num;
                    }
                }
            }
            // Should assert
            return 0;
        }
};

void test(vector<int> &nums)
{
    cout << "Input: ";
    for (auto num: nums)
    {
        cout << num << " ";
    }
    Solution sol;
    auto res = sol.majorityElement(nums);
    cout << "\nResult: " << res << endl;
}

int main()
{
    vector<int> input = {2, 1, 1};
    test(input);
    vector<int> input2 = {2, 2, 1, 1, 1, 1};
    test(input2);
    vector<int> input3 = {2};
    test(input3);

    return 0;
}
