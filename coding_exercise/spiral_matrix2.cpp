#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        void fillMatrix(int next_num, int x, vector<vector<int>> *out)
        {
            int dim = out->size();
            // Upper row
            for (int i = x; i < dim - x; i++)
            {
                (*out)[x][i] = next_num;
                next_num++;
            }
            // right col
            for (int i = x + 1; i < dim - x; i++)
            {
                (*out)[i][dim - x - 1] = next_num;
                next_num++;
            }
            // lower row
            for (int i = dim - x - 2; i >= x; i--)
            {
                (*out)[dim - x - 1][i] = next_num;
                next_num++;
            }
            for (int i = dim - x - 2; i >= x + 1; i--)
            {
                (*out)[i][x] = next_num;
                next_num++;
            }
            if (next_num <= dim * dim)
            {
                fillMatrix(next_num, x + 1, out);
            }
        }
        vector<vector<int>> generateMatrix(int n) {
            vector<vector<int>> res;

            if (n <= 0) return res;
            res.resize(n);
            for (int i = 0; i < n; i++)
            {
                res[i].resize(n);
            }
            if (n == 1)
            {
                res[0][0] = 1;
            }
            else
            {
                fillMatrix(1, 0, &res);
            }
            return res;
        }
};

void test(int n)
{
    cout << "Input " << n << endl;
    Solution sol;
    auto res = sol.generateMatrix(n);
    for (auto row: res)
    {
        print_vector<int>(row, "Output");
    }
}

int main()
{
    test(0);
    test(1);
    test(5);
    test(4);
    return 0;
}
