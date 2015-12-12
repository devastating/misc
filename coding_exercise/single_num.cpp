#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        int singleNumber(vector<int>& nums) {
            unordered_set<int> seen;

            for (auto num: nums)
            {
                if (seen.find(num) == seen.end())
                {
                    seen.insert(num);
                }
                else
                {
                    seen.erase(num);
                }
            }
            assert(seen.size() == 1);
            return *(seen.begin());
        }
};
