#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        int findKthLargest(vector<int>& nums, int k) {
            if (nums.empty())
            {
                return -1;
            }
            if (nums.size() < k || k <= 0)
            {
                return -1;
            }
            sort(nums.begin(), nums.end());
            return *(nums.end() - k);
        }
};

void test(vector<int> &input, int k)
{
    cout << "input: " << endl;
    for (auto num: input)
    {
        cout << num << " ";
    }
    cout << endl;
    Solution sol;
    cout << "result: " << sol.findKthLargest(input, k) << endl;
}

int main()
{
    vector<int> input;
    input = {3,2,1,5,6,4};
    test(input, 2);
    return 0;
}
