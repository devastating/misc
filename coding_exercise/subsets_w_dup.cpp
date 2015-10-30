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
                // First check if current num has dups
                int dups = 0;
                for (int i = idx - 1; i >= 0; i--)
                {
                    if(nums[i] != nums[idx]) break;
                    dups++;
                }
                auto res = subsets_recur(nums, idx - 1);
                size_t original_size = res.size();
                for (size_t i = 0; i < original_size; i++)
                {
                    auto new_val = res[i];
                    int dups_tmp = dups;
                    if (dups_tmp)
                    {
                        // Don't bother with empty set
                        if (new_val.empty()) continue;

                        for (size_t j = new_val.size() - 1; j >=0; j--)
                        {
                            if (new_val[j] != nums[idx]) break;
                            dups_tmp--;
                        }
                    }
                    if (dups_tmp == 0)
                    {
                        new_val.push_back(nums[idx]);
                        res.push_back(new_val);
                    }
                }
                return res;
            }
        }
        vector<vector<int>> subsetsWithDup(vector<int>& nums) {
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
    auto res = sol.subsetsWithDup(input);
    cout << "test:\n";
    print_res(res);
}

int main()
{
    vector<int> input = {4, 2, 3};
    test(input);
    vector<int> input2 = {3};
    test(input2);
    //vector<int> input3 = {1, 2, 3, 4, 5};
    //test(input3);
    vector<int> input4 = {1, 1};
    test(input4);
    vector<int> input5 = {1, 2, 1, 2};
    test(input5);
    vector<int> input6 = {1, 2, 2};
    test(input6);
    return 0;
}
