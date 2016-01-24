#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        void external_loop(vector<vector<int>>& matrix, int x, int y, vector<int> *res)
        {
            int x_max = matrix.size();
            if (x_max == 0) return;

            int y_max = matrix[0].size();
            if (x_max == 1 && y_max == 1)
            {
                res->push_back(matrix[x][y]);
                return;
            }
            assert(x < x_max);
            assert(y < y_max);
            // Upper row
            for (int j = y; j < y_max - y; j++)
            {
                res->push_back(matrix[x][j]);
            }
            //print_vector<int>(*res, "ur");
            // Right col 
            for (int i = x + 1; i < x_max - x; i++)
            {
                res->push_back(matrix[i][y_max - y - 1]);
            }
            //print_vector<int>(*res, "rc");
            // lower row
            if (x != x_max - x - 1)
            {
                for (int i = y_max - y - 2; i >= y; i--)
                {
                    res->push_back(matrix[x_max - x - 1][i]);
                }
            }
            //print_vector<int>(*res, "lr");
            // Left col
            if (y != y_max - y - 1)
            {
                for (int i = x_max - x - 2; i >= x + 1; i--)
                {
                    //cout << i << " " << y << endl;
                    res->push_back(matrix[i][y]);
                }
            }
            //print_vector<int>(*res, "lc");
            // Recusive
            x++; y++;
            if (res->size() < x_max * y_max)
            {
                if (res->size() + 1 == x_max * y_max) res->push_back(matrix[x][y]);
                else
                {
                    external_loop(matrix, x, y, res);
                }
            }
        }
        vector<int> spiralOrder(vector<vector<int>>& matrix) {
            vector<int> res;
            external_loop(matrix, 0, 0, &res);
            return res;
        }
};

void test(vector<vector<int>>& matrix)
{
    for (auto row: matrix)
    {
        print_vector<int>(row);
    }
    Solution sol;
    auto order = sol.spiralOrder(matrix);
    print_vector<int>(order, "Output");
}

int main()
{
    vector<vector<int>> matrix;

    matrix = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    test(matrix);
    matrix = {{1, 2}, {3, 4}};
    test(matrix);
    matrix = {{2}, {3}};
    test(matrix);
    matrix = {{2}, {3}, {4}};
    test(matrix);
    matrix = {{2, 3}, {4, 5}, {6, 7}};
    test(matrix);
    matrix = {{1}};
    test(matrix);
    matrix = {};
    test(matrix);
    matrix = {{1, 2, 3, 4}};
    test(matrix);
    return 0;
}
