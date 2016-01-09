#include "basic_includes.hpp"

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        vector<vector<int>> ret;
        if (nums.size() < 3) return ret;
        sort(nums.begin(), nums.end());
        for (size_t i = 0; i <= nums.size() - 3; i++)
        {
            size_t k = nums.size() - 1;
            for (size_t j = i + 1; j <= nums.size() - 2; j++)
            {
                while(k > j)
                {
                    auto sum = nums[i] + nums[j] + nums[k];
                    if (sum == 0)
                    {
                        vector<int> solution = {nums[i], nums[j], nums[k]};
                        ret.push_back(solution);
                        k--;
                        break;
                    }
                    else if (sum > 0)
                    {
                        k--;
                    }
                    else
                    {
                        break;
                    }
                }
                auto current = nums[j];
                while (current == nums[j + 1])
                {
                    j++;
                    if (j == nums.size() - 1) break;
                }
            }
            auto current = nums[i];
            while (current == nums[i + 1])
            {
                i++;
                if (i == nums.size() - 1) break;
            }
        }
        return ret;
    }
};

void test(vector<int> &input)
{
    Solution sol;
    cout << "Input: ";
    for (auto num: input)
    {
        cout << num << " ";
    }
    cout << "\nOutput:\n";
    auto ret = sol.threeSum(input);
    for (auto item: ret)
    {
        for (auto num: item)
        {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main()
{
    vector<int> input1 = {-1, 0, 1, 2, -1, -1, -1, -4};
    vector<int> input2;
    vector<int> input3 = {100, -100, 1};
    vector<int> input4 = {100, -100, 0};
    test(input1);
    test(input2);
    test(input3);
    test(input4);
}
