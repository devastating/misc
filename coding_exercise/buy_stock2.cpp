#include "basic_includes.hpp"

using namespace std;

// allow to buy stock multiple times

class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            vector<int> lcl_max_min;
            bool is_up = true;
            int buy;
            int max_profit = 0;

            for (int i = 0; i < prices.size(); i++)
            {
                if (i == 0)
                {
                    buy = prices[i];
                    continue;
                }

                if (prices[i] >= prices[i - 1])
                {
                    if (is_up == false)
                    {
                        buy = prices[i - 1];
                        is_up = true;
                    }
                }
                else
                {
                    if (is_up == true)
                    {
                        max_profit += prices[i - 1] - buy;
                        is_up = false;
                    }
                }
            }
            if (is_up == true && prices.empty() == false)
            {
                max_profit += prices[prices.size() - 1] - buy;
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
    vector<int> input4 = {100, 80, 90, 60};
    test(input4);

    return 0;
}
