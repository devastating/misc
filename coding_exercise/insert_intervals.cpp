/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
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
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
    {
        // Insert at right location
        bool inserted = false;
        for (size_t i = 0; i < intervals.size(); i++)
        {
            if (intervals[i].start > newInterval.start)
            {
                intervals.insert(intervals.begin() + i, newInterval);
                inserted = true;
                break;
            }
        }
        if (inserted == false)
        {
            intervals.insert(intervals.end(), newInterval);
        }
        vector<Interval> res;
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

void test(vector<pair<int, int>> &input, pair<int, int> new_intvl)
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
    cout << "Insert: " << "[" << new_intvl.first
        << "," << new_intvl.second << "]\n";

    Solution sol;
    auto merged = sol.insert(test_in, Interval(new_intvl.first, new_intvl.second));
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
    pair<int, int> insert;
    test_in = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    insert = {9, 17};
    test(test_in, insert);
    test_in = {{1, 6}, {2, 3}, {6, 8}};
    insert = {9, 17};
    test(test_in, insert);
    return 0;
}
