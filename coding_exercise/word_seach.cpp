#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>
using namespace std;

// Word search

class Solution {
public:
	struct bfs_node
	{
		int row_idx;
		int col_idx;
		int next_comp_idx;
	};
	void get_neighbor(vector<vector<char>>& board, int row_i, int col_i,
		vector<pair<int, int>> &out, set<pair<int, int>> &dedup)
	{
		out.clear();
		int row = board.size();
        int col = board[0].size();
        //cout << "tgt " << row_i << " " << col_i << endl;
        for (int i = -1; i < 2; i++)
      	{
      		if (i == -1 && row_i == 0) continue;
      		if (i == 1 && row_i == (row - 1)) continue;
      		for (int j = -1; j < 2; j++)
      		{
      			if (i * j) continue;
      			if (j == -1 && col_i == 0) continue;
      			if (j == 1 && col_i == (col - 1)) continue;
      			auto candidate = pair<int, int>(row_i + i, col_i + j);
      			if (dedup.find(candidate) == dedup.end())
      			{
      				//cout << "neighbor " << candidate.first << " " << candidate.second << endl;
      				out.push_back(candidate);
      			}
      		}
      	}
	}
	bool dfs_go(vector<vector<char>>& board, string word, int row, int col, int lvl, set<pair<int, int>> &dedup)
	{
		// Dont bother to go on
		if (board[row][col] != word[lvl]) return false;
		// Found end
		if (lvl + 1 == word.length()) return true;
		
		vector<pair<int, int>> neighbors;
		dedup.insert(pair<int, int>(row, col));
		get_neighbor(board, row, col, neighbors, dedup);
		if (neighbors.empty()) return false;
		for (auto neighbor: neighbors)
		{
			//if (board[neighbor.first][neighbor.second] == word[lvl])
			{
				//dedup.insert(neighbor);
				bool ret = dfs_go(board, word,neighbor.first, neighbor.second, lvl + 1, dedup);
				if (ret == true) return true;
				//dedup.erase(neighbor);
			}
		}
		dedup.erase(pair<int, int>(row, col));
		return false;
	}
    bool exist(vector<vector<char>>& board, string word) {
        //assert(board.empty() == false);
        list<bfs_node> bfs_queue;
        int row = board.size();
        int col = board[0].size();
        
        for (int i = 0; i < row; i++)
        {
        	for (int j = 0; j < col; j++)
        	{
				set<pair<int, int>> dedup;
        		//auto elem = bfs_queue.front();
        		//bfs_queue.pop_front();
        		dedup.clear();
        		bool ret = dfs_go(board, word, i, j, 0, dedup);
        		if (ret == true) return true;
        	}
        }
        return false;
    }
};

int test_basic2()
{
	vector<vector<char>> out;
	vector<char> tmp1 = {'A', 'B'};
	vector<char> tmp2 = {'C', 'D'};
	out.push_back(tmp1); out.push_back(tmp2);
	Solution sol;
	string test1("ABCD");
	cout << test1 << " " << sol.exist(out, test1) << endl;
}

int test_basic()
{
	vector<vector<char>> out;
	vector<char> tmp1 = {'A', 'B', 'C', 'E'};
	vector<char> tmp2 = {'S', 'F', 'C', 'S'};
	vector<char> tmp3 = {'A', 'D', 'E', 'E'};
	out.push_back(tmp1); out.push_back(tmp2); out.push_back(tmp3);
	Solution sol;
	string test1("ABCCED");
	cout << test1 << " " << sol.exist(out, test1) << endl;
	string test2("SEE");
	cout << test2 << " " << sol.exist(out, test2) << endl;
	string test3("ABCB");
	cout << test3 << " " << sol.exist(out, test3) << endl;
}
int main() {
	// your code goes here
	test_basic();
	test_basic2();
	return 0;
}