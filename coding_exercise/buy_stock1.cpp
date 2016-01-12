#include "basic_includes.hpp"

using namespace std;

// only allow to buy stock once

class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int min = 0xffffff, max = 0;
            int max_profit = 0;
            for (auto price: prices)
            {
                if (price < min)
                {
                    min = price;
                }
                if (price > max)
                {
                    max = price;
                    max_profit = max - min;
                }
                else
                {
                    if (price > min && (price - min) > max_profit)
                    {
                        max_profit = price - min;
                    }
                }
            }
            return max_profit;
        }
};

void test(vector<int> &prices)
{
    cout << "Input: ";
    for (auto num: prices)
    {
        cout << num << " ";
    }
    Solution sol;
    auto res = sol.maxProfit(prices);
    cout << "\nResult: " << res << endl;
}

int main()
{
    vector<int> input = {2, 3, 4};
    test(input);
    vector<int> input2 = {2, 1, 5, 4, 8, 4};
    test(input2);
    vector<int> input3 = {4, 1, 2};
    test(input3);

    return 0;
}
