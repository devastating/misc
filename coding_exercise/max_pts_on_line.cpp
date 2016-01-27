#include "basic_includes.hpp"

using namespace std;

/**
 * Definition for a point.
 */
 struct Point {
     int x;
     int y;
     Point() : x(0), y(0) {}
     Point(int a, int b) : x(a), y(b) {}
 };
 
class Solution {
    public:
        int gcd(int x, int y)
        {
            while (true)
            {
                int mod_num = x % y;
                if (mod_num == 0) return y;
                x = y; y = mod_num;
            }
        }
        int maxPoints(vector<Point>& points)
        {
            int max_pts = 0;

            if (points.empty()) return 0;

            for (auto pt = points.begin(); pt != points.end(); pt++)
            {
                int v_pt = 0;
                int h_pt = 0;
                int dup_pt = 0;
                unordered_map<string, int> slope_pt_map;

                for (auto other_pt = pt + 1; other_pt != points.end(); other_pt++)
                {
                    if (pt->x == other_pt->x && pt->y == other_pt->y)
                    {
                        dup_pt++;
                        continue;
                    }
                    if (pt->x == other_pt->x)
                    {
                        v_pt++;
                        continue;
                    }
                    if (pt->y == other_pt->y)
                    {
                        h_pt++;
                        continue;
                    }
                    int diff_x = (pt->x - other_pt->x);
                    int diff_y = (pt->y - other_pt->y);
                    int this_gcd = gcd(diff_x, diff_y);
                    diff_x /= this_gcd;
                    diff_y /= this_gcd;
                    if (diff_x * diff_y < 0 && diff_x > 0)
                    {
                        diff_x *= -1; diff_y *= -1;
                    }
                    if (diff_x * diff_y > 0 && diff_x < 0)
                    {
                        diff_x *= -1; diff_y *= -1;
                    }
                    stringstream slope_str; slope_str << diff_x << "_" << diff_y;
                    if (slope_pt_map.find(slope_str.str()) == slope_pt_map.end())
                    {
                        slope_pt_map[slope_str.str()] = 1;
                    }
                    else
                    {
                        slope_pt_map[slope_str.str()] += 1;
                    }
                }
                if (v_pt + dup_pt > max_pts) max_pts = v_pt + dup_pt;
                if (h_pt + dup_pt > max_pts) max_pts = h_pt + dup_pt;
                for (auto map_iter: slope_pt_map)
                {
                    if (map_iter.second + dup_pt > max_pts)
                    {
                        max_pts = map_iter.second + dup_pt;
                    }
                }
            }
            return max_pts + 1;
        }
};

void test(vector<Point> &input)
{
    for (auto i: input)
    {
        cout << "(" << i.x << "," << i.y << ") ";
    }
    cout << endl;
    Solution sol;
    cout << "max ptrs " << sol.maxPoints(input) << endl;
}

int main()
{
    vector<Point> input; 
    input = {{0, 0}, {1, 0}};
    test(input);
    input = {{0, 1}, {1, 0}};
    test(input);
    input = {{0, 1}, {0, 2}, {0, 3}, {1, 0}};
    test(input);
    input = {{0, 2}, {1, 1}, {2, 0}};
    test(input);
    return 0;
}
