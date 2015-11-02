#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        inline void markDiagnal(vector<vector<int>> &used, int x, int y,
                                int n, int diff_x, int diff_y, bool mark)
        {
            for (int i = 1; i < n; i++)
            {
                int new_x = x + diff_x * i;
                int new_y = y + diff_y * i;
                if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= n)
                {
                    break;
                }
                used[new_x][new_y] += mark? 1: -1;
                assert(used[new_x][new_y] >= 0);
            }
        }
        inline void markLines(vector<vector<int>> &used, int x, int y, int n, bool mark)
        {
            // Begin to mark used space
            for (int j = 0; j < n; j++)
            {
                used[x][j] += mark? 1: -1;
                assert(used[x][j] >= 0);
            }
            for (int j = 0; j < n; j++)
            {
                used[j][y] += mark? 1: -1;
                assert(used[j][y] >= 0);
            }

        }
        void solveNQueens(int n, int row, vector<vector<int>> &used)
        {
            // Begin to check
            for (int i = 0; i < n; i++)
            {
                if (used[row][i] == 0)
                {
                    m_sol[row][i] = 'Q';
                    if (row == n - 1)
                    {
                        // Found solution
                        m_sol_sum.push_back(m_sol);
                    }
                    else
                    {
                        markLines(used, row, i, n, true);
                        markDiagnal(used, row, i, n, 1, 1, true);
                        markDiagnal(used, row, i, n, -1, 1, true);
                        markDiagnal(used, row, i, n, -1, -1, true);
                        markDiagnal(used, row, i, n, 1, -1, true);

                        solveNQueens(n, row + 1, used);

                        markLines(used, row, i, n, false);
                        markDiagnal(used, row, i, n, 1, 1, false);
                        markDiagnal(used, row, i, n, -1, 1, false);
                        markDiagnal(used, row, i, n, -1, -1, false);
                        markDiagnal(used, row, i, n, 1, -1, false);
                    }
                    m_sol[row][i] = '.';
                }
            }
        }
        vector<vector<string>> solveNQueens(int n) 
        {
            vector<vector<int>> used;
            vector<int> empty_used;
            empty_used.resize(n, 0);
            used.resize(n, empty_used);

            string empty_sol_string;
            empty_sol_string.resize(n, '.');
            m_sol.resize(n, empty_sol_string);

            solveNQueens(n, 0, used);
            return m_sol_sum;
        }
        void print_sol()
        {
            cout << "Total " << m_sol_sum.size() << " solutions\n";
            for (auto sol: m_sol_sum)
            {
                cout << "Solution:\n";
                for (auto row_str: sol)
                {
                    cout << row_str << endl;
                }
            }
        }
    private:
        vector<string> m_sol;
        vector<vector<string>> m_sol_sum;
};

void test(int n)
{
    Solution sol;
    auto res = sol.solveNQueens(n);
    sol.print_sol();
}

int main()
{
    test(4);
    test(5);
    test(7);
    return 0;
}
