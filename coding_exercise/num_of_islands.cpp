#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        void calculate_island(vector<vector<char>>& grid, size_t x, size_t y)
        {
            grid[x][y] = 'X';
            list<pair<size_t, size_t>> queue;
            queue.push_back(pair<size_t, size_t>(x, y));
            while (queue.empty() != true)
            {
                auto pt = queue.front(); queue.pop_front();
                if (pt.first > 0 && grid[pt.first - 1][pt.second] == '1')
                {
                    grid[pt.first - 1][pt.second] = 'X';
                    queue.push_back(pair<size_t, size_t>(pt.first - 1, pt.second));
                }
                if (pt.second > 0 && grid[pt.first][pt.second - 1] == '1')
                {
                    grid[pt.first][pt.second - 1] = 'X';
                    queue.push_back(pair<size_t, size_t>(pt.first, pt.second - 1));
                }
                if (pt.first < (grid.size() - 1)  && grid[pt.first + 1][pt.second] == '1')
                {
                    grid[pt.first + 1][pt.second] = 'X';
                    queue.push_back(pair<size_t, size_t>(pt.first + 1, pt.second));
                }
                if (pt.second < (grid[0].size() - 1) && grid[pt.first][pt.second + 1] == '1')
                {
                    grid[pt.first][pt.second + 1] = 'X';
                    queue.push_back(pair<size_t, size_t>(pt.first, pt.second + 1));
                }
            }
        }

        int numIslands(vector<vector<char>>& grid)
        {
            int islands = 0;
            for (size_t row = 0; row < grid.size(); row++)
            {
                for (size_t col = 0; col != grid[0].size(); col++)
                {
                    if (grid[row][col] != '1') continue;

                    pair<int, int> origin; 
                    calculate_island(grid, row, col);
                    islands++;
                }
            }
            return islands;
        }
};

void test(vector<vector<char>> &grid)
{
    cout << "Input:\n";
    for (auto row: grid)
    {
        for (auto col: row)
        {
            cout << col << " ";
        }
        cout << endl;
    }
    Solution sol;
    cout << "Islands: " << sol.numIslands(grid) << endl;
}

void test1()
{
//    vector<string> in = {"11111011111111101011","01111111111110111110","10111001101111111111","11110111111111111111","10011111111111111111","10111111011101110111","01111111111101101111","11111111111101111011","11111111110111111111","11111111111111111111","01111111011111111111","11111111111111111111","11111111111111111111","11111011111110111111","10111110111011110111","11111111111101111110","11111111111110111100","11111111111111111111","11111111111111111111","11111111111111111111"}
}

int main()
{
    vector<vector<char>> grid;
    grid = {{'1', '1', '0'}, {'1', '0', '0'}, {'0', '0', '1'}};
    test(grid);
    grid = {{'1', '1', '0'}, {'1', '0', '0'}};
    test(grid);
    grid = {{'1', '1', '1'}, {'1', '1', '1'}};
    test(grid);
    grid = {{'1', '1', '1'}, {'1', '0', '0'}};
    test(grid);
    grid = {{}};
    test(grid);
    return 0;
}
