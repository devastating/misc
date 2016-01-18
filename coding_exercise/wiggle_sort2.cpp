#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        void wiggleSort(vector<int>& nums) {

            if (nums.empty()) return;
            sort(nums.begin(), nums.end());
            vector<int> res;
            int med = (nums.size() + 1) / 2 - 1;
            int i = med, j = nums.size() - 1;
            int iterations = 0;

            while (iterations < nums.size())
            {
                if ((iterations % 2) == 0)
                {
                    res.push_back(nums[i]);
                    i--;
                }
                else
                {
                    res.push_back(nums[j]);
                    j--;
                }
                iterations++;
            }
            nums = res;
        }
};

void test(vector<int> &input)
{
    cout << "input: " << endl;
    for (auto num: input)
    {
        cout << num << " ";
    }
    cout << endl;
    Solution sol; sol.wiggleSort(input);
    cout << "result: ";
    for (auto num: input)
    {
        cout << num << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> input;
    input = {1, 5, 1, 1, 6, 4};
    test(input);
    input = {1, 3, 2, 2, 3, 1};
    test(input);
    input = {1, 3, 2, 2, 3, 1, 1};
    test(input);
    return 0;
}
