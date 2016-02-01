#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        int candy(vector<int>& ratings)
        {
            if (ratings.empty()) return 0;

            vector<int> scan_left, scan_right;
            int total = ratings.size();
            scan_left.resize(total, 1);
            scan_right.resize(total, 1);
            for (int i = 0; i < total; i++)
            {
                if (i > 0)
                {
                    if (ratings[i] > ratings[i - 1])
                    {
                        scan_right[i] = scan_right[i - 1] + 1;
                    }
                    else if (ratings[i] == ratings[i - 1])
                    {
                        //scan_right[i] = scan_right[i - 1];
                    }
                    if (ratings[total - 1 - i] > ratings[total - i])
                    {
                        scan_left[total - 1 - i] = scan_left[total - i] + 1;
                    }
                    else if (ratings[total - 1 - i] == ratings[total - i])
                    {
                        //scan_left[total - 1 - i] = scan_left[total - i];
                    }
                }
            }
            int res = 0;
            for (int i = 0; i < total; i++)
            {
                res += max(scan_right[i], scan_left[i]);
            }
            return res;
        }
};

void test(vector<int> ratings)
{
    print_vector<int>(ratings);
    Solution sol;
    cout << "total: " << sol.candy(ratings) << endl;
}

int main()
{
    vector<int> input;

    input = {1, 3, 2};
    test(input);
    input = {1, 2, 2};
    test(input);
    input = {1, 3, 3, 2};
    test(input);
    input = {3, 3, 3, 3};
    test(input);
    input = {1, 2, 3, 4};
    test(input);
    input = {1, 2, 3, 4, 5};
    test(input);
    input = {1};
    test(input);
    return 0;
}
