#include "basic_includes.hpp"

using namespace std;

// allow to buy stock twice

class Solution {
    public:
        int maxProfit(vector<int>& prices) {

            if (prices.size() <= 1) return 0;
            vector<int> max_on_trac_profit;
            vector<int> max_on_trac_profit_reverse;
            max_on_trac_profit.resize(prices.size());
            max_on_trac_profit_reverse.resize(prices.size());
            int min = 0xffffff, max = 0, max_profit = 0;
            // Calculate one traction max
            for (int i = 0; i < prices.size(); i++)
            {
                if (prices[i] < min)
                {
                    min = prices[i];
                }
                if (prices[i] > max)
                {
                    max = prices[i];
                    max_profit = max - min;
                }
                else
                {
                    if ((prices[i] - min) > max_profit)
                    {
                        max_profit = prices[i] - min;
                    }
                }
                max_on_trac_profit[i] = max_profit;
                //cout << max_profit << " ";
            }
            //cout << endl;
            max_profit = 0;
            int sec_trac_max = prices[prices.size() - 1];
            for (int i = prices.size() - 1; i >= 0; i--)
            {
                if (i == prices.size() - 1)
                {
                    if (max_on_trac_profit[i] > max_profit) max_profit = max_on_trac_profit[i];
                    continue;
                }
                int sec_trac = sec_trac_max - prices[i + 1];
                if (sec_trac < 0) sec_trac = 0;
                int lcl_max = max_on_trac_profit[i] + sec_trac;
                if (lcl_max > max_profit)
                {
                    max_profit = lcl_max;
                }
                if (prices[i + 1] > sec_trac_max) sec_trac_max = prices[i + 1];
            }
            return max_profit;
        }
};

void test(vector<int>& prices)
{
    for (auto price: prices)
    {
        cout << price << " ";
    }
    cout << endl;
    Solution sol;
    cout << "Max: " << sol.maxProfit(prices) << endl;
}

int main()
{
    vector<int> input;
    input = {1,2};
    test(input);
    input = {2,1,4,5,2,9,7};
    test(input);
    input = {4, 1, 2};
    test(input);
    input = {1, 2, 3, 4};
    test(input);
    input = {5, 10, 7, 15, 9, 20};
    test(input);
    input = {3, 2, 1};
    test(input);
    return 0;
}
