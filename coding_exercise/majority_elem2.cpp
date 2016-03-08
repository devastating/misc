#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        vector<int> majorityElement(vector<int>& nums)
        {
            int m1 = 0, m2 = 0, m1_cnt = 0, m2_cnt = 0;
            for (auto num: nums)
            {
                if (num == m1)
                {
                    m1_cnt++;
                }
                else if (num == m2)
                {
                    m2_cnt++;
                }
                else if (m1_cnt == 0)
                {
                    m1 = num;
                    m1_cnt = 1;
                }
                else if (m2_cnt == 0)
                {
                    m2 = num;
                    m2_cnt = 1;
                }
                else
                {
                    // m1 & m2 are non-zero
                    m1_cnt--;
                    m2_cnt--;
                }
            }
            m1_cnt = 0; m2_cnt = 0;
            for (auto num: nums)
            {
                if (num == m1)
                {
                    m1_cnt++;
                }
                else if (num == m2)
                {
                    m2_cnt++;
                }
            }
            vector<int> result;
            if (m1_cnt > nums.size() / 3)
            {
                result.push_back(m1);
            }
            if (m2_cnt > nums.size() / 3)
            {
                result.push_back(m2);
            }
            return result;
        }
};

void test(vector<int> &in)
{
    print_vector<int>(in, "Input");
    Solution sol;
    auto result = sol.majorityElement(in);
    print_vector<int>(result, "Output");
}

int main()
{
    vector<int> test_input;

    test_input = {0, 0, 0, 1, 2};
    test(test_input);

    test_input = {0, 0, 1, 1, 1, 2, 2, 2};
    test(test_input);

    test_input = {0, 1, 2};
    test(test_input);

    test_input = {1, 1, 1, 3, 3, 2, 2, 2};
    test(test_input);

    test_input = {2,2,9,3,9,3,9,3,9,3,9,3,9,3,9,3,9};
    test(test_input);

    return 0;
}
