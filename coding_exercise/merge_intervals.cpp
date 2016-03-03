#include "basic_includes.hpp"

using namespace std;

/**
 * Definition for an interval.
 */
 struct Interval {
     int start;
     int end;
     Interval() : start(0), end(0) {}
     Interval(int s, int e) : start(s), end(e) {}
 };
 
class Solution {
public:
    static bool intvl_cmp(Interval a, Interval b)
    {
        return a.start < b.start;
    }
    vector<Interval> merge(vector<Interval>& intervals)
    {
        vector<Interval> res;
        // Sort the time points
        sort(intervals.begin(), intervals.end(), intvl_cmp);
        for (auto intvl: intervals)
        {
            if (res.empty() || intvl.start > res.back().end)
            {
                res.push_back(intvl);
            }
            else
            {
                int extend_end = res.back().end > intvl.end? res.back().end: intvl.end;
                res.back().end = extend_end;
            }
        }
        return res;
    }
};

void test(vector<pair<int, int>> &input)
{
    vector<Interval> test_in;
    for (auto per_in: input)
    {
        auto new_intvl = Interval(per_in.first, per_in.second);
        test_in.push_back(new_intvl);
    }

    cout << "Input\n";
    for (auto intvl: test_in)
    {
        cout << "[" << intvl.start << ","
            << intvl.end << "]";
    }
    cout << endl;

    Solution sol;
    auto merged = sol.merge(test_in);
    cout << "Output\n";
    for (auto merged_intvl: merged)
    {
        cout << "[" << merged_intvl.start << ","
            << merged_intvl.end << "] ";
    }
    cout << endl;
}

int main()
{
    vector<pair<int, int>> test_in;
    test_in = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    test(test_in);
    test_in = {{1, 6}, {2, 3}, {6, 8}};
    test(test_in);
    return 0;
}
