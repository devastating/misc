#include "basic_includes.hpp"

using namespace std;

// Ahh...brute force approach :( It was slow, but it passes..


class Solution {
    public:
        int maximalRectangle(vector<vector<char>>& matrix)
        {
            if (matrix.empty()) return 0;

            unsigned matrix_width = matrix.size();
            unsigned matrix_width_y = matrix[0].size();
            vector<vector<int>> x_count;
            vector<int> x_count_row;

            x_count_row.resize(matrix_width_y, 0);
            x_count.resize(matrix_width, x_count_row);
            for (unsigned i = 0; i < matrix_width; i++)
            {
                for (unsigned j = 0; j < matrix_width_y; j++)
                {
                    if (matrix[i][j] != '0')
                    {
                        if (j == 0) x_count[i][j] = 1;
                        else
                        {
                            x_count[i][j] = x_count[i][j - 1] + 1;
                        }
                    }
                }
            }
            int max_rec = 0;
            for (unsigned i = 0; i < matrix_width; i++)
            {
                for (unsigned j = 0; j < matrix_width_y; j++)
                {
                    if (x_count[i][j])
                    {
                        int max_width = x_count[i][j];
                        unsigned k;
                        for (k = i; k < matrix_width; k++)
                        {
                            if (x_count[k][j] == 0) break;
                            if (x_count[k][j] < max_width)
                            {
                                int new_rec = (k - i) * max_width;
                                if (new_rec > max_rec) max_rec = new_rec;
                                max_width = x_count[k][j];
                            }
                        }
                        int new_rec = (k - i) * max_width;
                        if (new_rec > max_rec) max_rec = new_rec;
                    }
                }
            }
            return max_rec;
        }

        int maximalRectangleBruteForce(vector<vector<char>>& matrix)
        {
            if (matrix.empty()) return 0;
            unsigned matrix_width = matrix.size();
            unsigned matrix_width_y = matrix[0].size();
            unsigned res_w = 0;

            for (unsigned i = 0; i < matrix_width; i++)
            {
                for (unsigned j = 0; j < matrix_width_y; j++)
                {
                    if (matrix[i][j] == '0') continue;
                    unsigned max_width_x = (matrix_width - i);
                    unsigned max_width_y = (matrix_width_y - j);
                    unsigned w = 1;
                    unsigned y = 1;
                    for (w = 0; w < max_width_x; w++)
                    {
                        bool w_ok = true;
                        unsigned range;
                        for (y = 0; y < max_width_y; y++)
                        {
                            for (range = 0; range <= w; range++)
                            {
                                if (matrix[i + range][j + y] == '0')
                                {
                                    w_ok = false;
                                    break;
                                }
                            }
                            if (((range) * (y + 1)) > res_w)
                            {
                                res_w = (range) * (y + 1);
                            }
                            if (w_ok == false)
                            {
                                break;
                            }
                        }
                    }
                }
            }
            return (res_w);
        }
};

void test(vector<vector<char>>& matrix)
{
    for (auto row: matrix)
    {
        print_vector<char>(row, "in");
    }

    Solution sol;
    cout << "Max rec area: " << sol.maximalRectangle(matrix) << endl;
}

void test2(vector<string>& matrix)
{
    vector<vector<char>> matrix2;
    for (auto in_str: matrix)
    {
        vector<char> row;
        for (auto str_char: in_str)
        {
            row.push_back(str_char);
        }
        matrix2.push_back(row);
    }
    test(matrix2);
}

int main()
{
    vector<vector<char>> matrix;
    vector<string> matrix2;

    matrix2 = {"0110010101","0010101010","1000010110","0111111010","0011111110","1101011110","0001100010","1101100111","0101101011"};
    test2(matrix2);
    return 0;

    matrix = {{'1', '1'}};
    test(matrix);
    matrix = {{'0', '0', '0'}, {'0', '0', '0'}, {'0', '0', '0'}};
    test(matrix);
    matrix = {{'0', '0', '0'}, {'0', '1', '1'}, {'0', '1', '0'}};
    test(matrix);
    matrix = {{'0', '0', '0'}, {'0', '1', '1'}, {'0', '1', '1'}};
    test(matrix);
    matrix = {{'1', '0', '0'}, {'0', '1', '1'}, {'0', '1', '1'}};
    test(matrix);
    matrix = {{'1', '1', '1'}, {'1', '1', '1'}, {'0', '1', '1'}};
    test(matrix);
    matrix = {{'1', '1', '1'}, {'1', '1', '1'}, {'1', '1', '1'}};
    test(matrix);
    matrix = {{'1', '1'}, {'1', '0'}};
    test(matrix);
    matrix = {{'1', '1'}, {'1', '1'}};
    test(matrix);
    matrix = {{'1'}};
    test(matrix);
    matrix = {{'0'}};
    test(matrix);
    matrix = {{'0', '1'}};
    test(matrix);
    matrix = {{'1'}, {'1'}, {'1'}};
    test(matrix);
    matrix = {{'0'}, {'1'}, {'1'}};
    test(matrix);
    matrix = {{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}};
    test(matrix);
    matrix2 = {"11111111","11111110","11111110","11111000","01111000"};
    test2(matrix2);
    return 0;
}
