#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>
using namespace std;

// Word search

// Trie used
class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
    	m_word = false;    
    }
    void add_edge(char new_char, TrieNode *node)
    {
    	if (m_edges.find(new_char) != m_edges.end())
    	{
    		cout << "Fuck Me, existing node! " << new_char << endl;
    		return;
    	}
    	m_edges[new_char] = node;
    }
    void set_word()
    {
    	m_word = true;
    }
    bool has_word()
    {
    	return m_word;
    }
    TrieNode *get_next_node(char target)
    {
    	auto ret = m_edges.find(target);
    	if (ret != m_edges.end())
    	{
    		return ret->second;
    	}
    	else
    	{
    		return nullptr;
    	}
    }
private:
	map<char, TrieNode *> m_edges;
	bool m_word;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
    	auto node_iter = root;
        for (auto each_char: word)
        {
        	auto next_node = node_iter->get_next_node(each_char);
        	if (next_node == nullptr)
        	{
        		auto new_node = new TrieNode();
        		node_iter->add_edge(each_char, new_node);
        		node_iter = new_node;
        	}
        	else
        	{
        		node_iter = next_node;
        	}
        }
        node_iter->set_word();
    }

    // Returns if the word is in the trie.
    bool search(string word) {
    	auto node_iter = root;
        for (auto each_char: word)
        {
        	auto next_iter = node_iter->get_next_node(each_char);
        	if (next_iter == nullptr)
        	{
        		// nope
        		return false;
        	}
        	node_iter = next_iter;
        }
        return node_iter->has_word()? true: false;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
    	auto node_iter = root;
        for (auto each_char: prefix)
        {
        	auto next_iter = node_iter->get_next_node(each_char);
        	if (next_iter == nullptr)
        	{
        		// nope
        		return false;
        	}
        	node_iter = next_iter;
        }
        return true;
    }

private:
    TrieNode* root;
};

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
	void dfs_go(vector<vector<char>>& board, string &word, int row, int col,
			set<pair<int, int>> &dedup, Trie *tries, set<string> &left)
	{
		if (left.empty())
		{
			// No more target
			return;
		}
		
		word.push_back(board[row][col]);
		//cout << "Word: " << word << endl; 
		set<string> target;
		if (tries->startsWith(word) == true)
		{
			//cout << "startswith true" <<endl;
			if (left.find(word) != left.end())
			{
				// don't need to check this word anymore
				//cout << "found " << word << endl;
				left.erase(word);
			}
		}
		else
		{
			//cout << "not startswith\n";
			word.pop_back();
			return;
		}
		
		vector<pair<int, int>> neighbors;
		dedup.insert(pair<int, int>(row, col));
		get_neighbor(board, row, col, neighbors, dedup);
		//cout << row << " " << col << endl;
		for (auto nei: neighbors)
		{
			//cout << "neighbor " << nei.first << " " << nei.second << endl;
		}
		do
		{
			if (neighbors.empty())
			{
				//word.pop_back();
				//cout << "no neighbor\n";
				//cout << "current " << row << " " << col << endl;
				for (auto item_iter: dedup)
				{
					//cout << item_iter.first << " " << item_iter.second << endl;
				}
				//cout << endl;
				break;
			}
			for (auto neighbor: neighbors)
			{
				dfs_go(board, word,neighbor.first,
					neighbor.second, dedup, tries, left);
				if (left.empty()) break;
			}
		}
		while (false);
		dedup.erase(pair<int, int>(row, col));
		word.pop_back();
		return;
	}

	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // Create tries first
        set<string> candidates, original;
        auto word_tries = new Trie;
        for (auto word: words)
        {
        	word_tries->insert(word);
        	candidates.insert(word);
        	//cout << "candidates: " << word << endl;
        }
        original = candidates;
        
        int row = board.size();
        int col = board[0].size();
        
        set<pair<int, int>> dedup;
        for (int i = 0; i < row; i++)
        {
        	for (int j = 0; j < col; j++)
        	{
        		dedup.clear();
        		string word;
        		dfs_go(board, word, i, j, dedup, word_tries, candidates);
        		if (candidates.empty() == true) break;
        	}
        	if (candidates.empty() == true) break;
        }
        for (auto can: candidates)
        {
        	//cout << "left: " << can << endl;
        }
        vector<string> res;
        for (auto word: original)
        {
        	if (candidates.find(word) == candidates.end())
        	{
        		res.push_back(word);
        	}
        }
        return res;
    }
};

int test_basic2()
{
	vector<vector<char>> out;
	vector<char> tmp1 = {'a', 'a', 'a', 'a'};
	vector<char> tmp2 = {'a', 'a', 'a', 'a'};
	vector<char> tmp3 = {'a', 'a', 'a', 'a'};
	out.push_back(tmp1); out.push_back(tmp2); out.push_back(tmp3);
	
	vector<string> words;
	words.push_back("aaaaaaaaaaaa");
	words.push_back("aaaaaaaaaaaaa");
	Solution sol;
	//string test1("ABCD");
	//cout << test1 << " " << sol.exist(out, test1) << endl;
	auto ret = sol.findWords(out, words);
	if (ret.empty()) cout << "No fucking word!" << endl;
	else
	{
		for (auto word: ret)
		{
			cout << word << " ";
		}
		cout << endl;
	}
}

int test_basic()
{
	vector<string> words;
	vector<vector<char>> out;
	vector<char> tmp1 = {'A', 'B', 'C', 'E'};
	vector<char> tmp2 = {'S', 'F', 'C', 'S'};
	vector<char> tmp3 = {'A', 'D', 'E', 'E'};
	out.push_back(tmp1); out.push_back(tmp2); out.push_back(tmp3);
	words.push_back(string("ASA"));
	words.push_back(string("FCSE"));
	words.push_back(string("FDB"));
	Solution sol;
	auto ret = sol.findWords(out, words);
	if (ret.empty()) cout << "No fucking word!" << endl;
	else
	{
		for (auto word: ret)
		{
			cout << word << " ";
		}
		cout << endl;
	}
}

int main() {
	// your code goes here
	//test_basic();
	test_basic2();
	return 0;
}