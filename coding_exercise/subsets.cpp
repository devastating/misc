#include "basic_includes.hpp"

using namespace std;

void print_res(const vector<vector<int>> &res);

class Solution {
    public:
        vector<vector<int>> subsets_recur(const vector<int>& nums, int idx)
        {
            if (idx == 0)
            {
                // Base case
                vector<vector<int>> res;
                vector<int> val;
                res.push_back(val);
                val.push_back(nums[0]);
                res.push_back(val);
                return res;
            }
            else
            {
                auto res = subsets_recur(nums, idx - 1);
                size_t original_size = res.size();
                for (size_t i = 0; i < original_size; i++)
                {
                    auto new_val = res[i];
                    new_val.push_back(nums[idx]);
                    res.push_back(new_val);
                }
                return res;
            }
        }
        vector<vector<int>> subsets(vector<int>& nums) {
            sort(nums.begin(), nums.end());
            return subsets_recur(nums, nums.size() - 1);
        }
};

void print_res(const vector<vector<int>> &res)
{
    for (auto subset: res)
    {
        cout << "[";
        for (auto val: subset)
        {
            cout << val << ",";
        }
        cout << "]" << endl;
    }
}

void test(vector<int> input)
{
    Solution sol;
    auto res = sol.subsets(input);
    cout << "test:\n";
    print_res(res);
}

int main()
{
    vector<int> input = {4, 2, 3};
    test(input);
    vector<int> input2 = {3};
    test(input2);
    vector<int> input3 = {1, 2, 3, 4, 5};
    test(input3);
    return 0;
}
