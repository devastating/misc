#include "basic_includes.hpp"

using namespace std;

/*
   Now consider if some obstacles are added to the grids. How many unique paths would there be?

   An obstacle and empty space is marked as 1 and 0 respectively in the grid.

   For example,

   There is one obstacle in the middle of a 3x3 grid as illustrated below.

   [
    [0,0,0],
    [0,1,0],
    [0,0,0]
   ]

   The total number of unique paths is 2.
 */

class Solution {
    public:
        int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) 
        {
            int m, n;
            m = obstacleGrid.size();
            n = obstacleGrid[0].size();

            m_paths.clear();
            vector<int> init_row;
            init_row.resize(n, 0);
            m_paths.resize(m, init_row);
            m_paths[0][0] = 1;

            // processing obstacle grid        
            for (int row = 0; row < m; row++)
            {
                for (int col = 0; col < n; col++)
                {
                    if (obstacleGrid[row][col] == 1)
                    {
                        m_paths[row][col] = 0;
                    }
                }
            }
            return uniquePaths(m, n, obstacleGrid);
        }
        int uniquePaths(int m, int n, vector<vector<int>>& obstacleGrid) 
        {
            for (int row = 0; row < m; row++)
            {
                for (int col = 0; col < n; col++)
                {
                    if (row == 0 && col == 0) continue;
                    if (obstacleGrid[row][col] == 1)
                    {
                        continue;
                    }
                    int p1 = (col == 0)? 0: m_paths[row][col - 1];
                    if (p1 == -1) p1 = 0; // Cannot use p1
                    int p2 = (row == 0)? 0: m_paths[row - 1][col];
                    if (p2 == -1) p2 = 0; // Cannot use p1
                    m_paths[row][col] = p1 + p2;
                }
            }
            return m_paths[m - 1][n - 1];
        }
    private:
        vector<vector<int>> m_paths;
};

void test(vector<vector<int>> in)
{
    Solution sol;
    cout << sol.uniquePathsWithObstacles(in) << endl;;
}

int main()
{
    vector<vector<int>> in = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    test(in);
    in = {{1}};
    test(in);
    return 0;
}
