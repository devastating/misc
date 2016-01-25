#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        void reverse_range(vector<int>& nums, int begin, int len)
        {
            int i = begin, j = begin + len - 1;
            while (j > i)
            {
                auto tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
                i++; j--;
            }
        }
        void rotate(vector<int>& nums, int k) 
        {
            if (nums.size() == 0) return;
            k = k % nums.size();
            if (k == 0) return;
            reverse_range(nums, 0, nums.size());
            reverse_range(nums, 0, k);
            reverse_range(nums, k, nums.size() - k);
        }
};

void test(vector<int> &in, int k)
{
    print_vector<int>(in);
    Solution sol;
    sol.rotate(in, k);
    print_vector<int>(in, "Output");
}

int main()
{
    vector<int> in;

    in = {1, 2, 3, 4, 5, 6, 7};
    test(in, 2);
    in = {1, 2, 3, 4, 5, 6, 7};
    test(in, 1);
    in = {};
    test(in, 1);
    return 0;
}
