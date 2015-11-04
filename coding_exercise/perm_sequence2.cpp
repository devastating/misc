#include "basic_includes.hpp"

using namespace std;

/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 -> 1, 3, 2
3,2,1 -> 1, 2, 3
1,1,5 -> 1, 5, 1
*/

// This code calculates the permutation sequence, not next perm...

class Solution {
public:
    inline int factorial(int n)
    {
        int sum = 1;
        while (n)
        {
            sum *= n;
            n--;
        }
        return sum;
    }
    inline int perm_count(map<int, int> &count_map)
    {
        int count = 0;
        int dividend = 1;

        for (auto map_iter: count_map)
        {
            if (map_iter.second != 0)
            { 
                count += map_iter.second;
                if (map_iter.second > 1)
                {
                    dividend *= factorial(map_iter.second);
                }
            }
        }
        return factorial(count) / dividend;
    }
    int nextPermutation(vector<int>& nums) 
    {
        map<int, int> count_map;
        vector<int> in_order;
        for (auto num: nums)
        {
            // Construct the map
            auto map_iter = count_map.find(num);
            if (map_iter == count_map.end())
            {
                count_map[num] = 1;
                in_order.push_back(num);
            }
            else
            {
                map_iter->second += 1;
            }
            // Calculate the sequence
        }
        sort(in_order.begin(), in_order.end());
    
        int seq = 0;
        auto calculate_map = count_map;
        for (auto num: nums)
        {
            for (auto in_order_num: in_order)
            {
                if (in_order_num == num)
                {
                    break;
                }
                if (calculate_map.find(in_order_num) == calculate_map.end())
                {
                    continue;
                }
                calculate_map[in_order_num] -= 1;
                seq += perm_count(calculate_map);
                calculate_map[in_order_num] += 1;
            }
            calculate_map[num] -= 1;
            if (calculate_map[num] == 0)
            {
                calculate_map.erase(num);
            }
        }
        return seq;
    }
};

void test(vector<int> &input)
{
    Solution sol;
    for (auto item: input)
    {
        cout << item << " ";
    }
    cout << "seq is " << sol.nextPermutation(input) << endl;
}

int main(void)
{
    vector<int> input = {3, 2, 1};
    test(input);
    input = {1, 1, 5};
    test(input);
    input = {1, 2, 3};
    test(input);
    input = {1, 2, 1, 2};
    test(input);
    return 0;
}
