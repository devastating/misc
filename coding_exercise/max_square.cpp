#include "basic_includes.hpp"

using namespace std;

/*
 Given a 2D binary matrix filled with 0's and 1's, find the largest square containing all 1's and return its area.

 For example, given the following matrix:

 1 0 1 0 0
 1 0 1 1 1
 1 1 1 1 1
 1 0 0 1 0

 Return 4. 
*/

class Solution {
    public:
        int maximalSquare(vector<vector<char>>& matrix) 
        {
            if (matrix.empty())
            {
                return 0;
            }
            size_t row = matrix.size(), col = matrix[0].size();
            int max_sqr_side = 0;
            for (size_t i = 0; i < row; i++)
            {
                for (size_t j = 0; j < col; j++)
                {
                    if (matrix[i][j] == '1')
                    {
                        // Begin to check
                        int side = 1;
                        while (true)
                        {
                            if (i + side >= row || j + side >= col)
                            {
                                break;
                            }

                            bool no_sq = false;
                            for (int side_y = 0; side_y < side; side_y++)
                            {
                                if (matrix[i + side][j + side_y] == '0')
                                {
                                    no_sq = true;
                                    break;
                                }
                                if (matrix[i + side_y][j + side] == '0')
                                {
                                    no_sq = true;
                                    break;
                                }
                            }
                            if (no_sq || matrix[i + side][j + side] == '0')
                            {
                                break;
                            }
                            side++;
                        }
                        if (side > max_sqr_side)
                        {
                            cout << "origin " << i << "," << j << " side " << side << endl;
                            max_sqr_side = side;
                        }
                    }
                }
            }
            return max_sqr_side * max_sqr_side;
        }
};

void test(vector<vector<char>> &in)
{
    for (auto row: in)
    {
        for (auto col: row)
        {
            cout << col << " ";
        }
        cout << endl;
    }
    Solution sol;
    cout << "max sqr: " << sol.maximalSquare(in) << endl;
}

void parser(const vector<string> &in, vector<vector<char>> *out)
{
    out->clear();
    for (auto row: in)
    {
        vector<char> out_row;
        for (auto col: row)
        {
            out_row.push_back(col);
        }
        out->push_back(out_row);
    }
}

int main()
{
    vector<vector<char>> test_input;
    test_input = {{'1', '1'}, {'1', '1'}};
    //test(test_input);
    test_input = {{'1', '0'}, {'1', '1'}};
    //test(test_input);
    test_input = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
        };
    //test(test_input);
    vector<string> test_in = {"00010111","01100101","10111101","00010000","00100010","11100111","10011001","01001100","10010000"};
    parser(test_in, &test_input);
    test(test_input);

    return 0;
}
