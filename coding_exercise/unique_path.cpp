#include "basic_includes.hpp"

using namespace std;

/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?
*/

class Solution {
    public:
        int uniquePaths(int m, int n) 
        {
            m_paths.clear();
            vector<int> init_row;
            init_row.resize(n, 0);
            m_paths.resize(m, init_row);
            m_paths[0][0] = 1;
            for (int row = 0; row < m; row++)
            {
                for (int col = 0; col < n; col++)
                {
                    if (row == 0 && col == 0) continue;
                    int p1 = (col == 0)? 0: m_paths[row][col - 1];
                    int p2 = (row == 0)? 0: m_paths[row - 1][col];
                    m_paths[row][col] = p1 + p2;
                }
            }
            return m_paths[m - 1][n - 1];
        }
    private:
        vector<vector<int>> m_paths;
};

void test(int m, int n)
{
    Solution sol;
    cout << m << "x" << n << " " << sol.uniquePaths(m, n) << endl;;
}

int main()
{
    test(2, 2);
    test(3, 7);
    return 0;
}
