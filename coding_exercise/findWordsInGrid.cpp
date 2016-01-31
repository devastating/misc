// PrintWordsInGrid.cpp : Given a dict and a grid of chars, find the possible words in the grid
//

#include "stdafx.h"
#include <unordered_set>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> get_neighbors(const vector<vector<bool>> &used, int x, int y)
{
	vector<pair<int, int>> res;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int new_x = x + i;
			int new_y = y + j;
			if (new_x < 0 || new_x >= used.size()) continue;
			if (new_y < 0 || new_y >= used[0].size()) continue;
			if (used[new_x][new_y]) continue;
			res.push_back(pair<int, int>(new_x, new_y));
		}
	}
	return res;
}

vector<string> get_words(
	vector<vector<bool>> &used,
	const vector<vector<char>> &in,
	int x, int y)
{
	used[x][y] = true;
	vector<string> res;
	auto neighbors = get_neighbors(used, x, y);
	for (auto neighbor : neighbors)
	{
		auto new_words = get_words(used, in, neighbor.first, neighbor.second);
		for (auto new_word : new_words)
		{
			string word; word.push_back(in[x][y]);
			word += new_word;
			res.push_back(word);
		}
	}
	used[x][y] = false;
	string word; word.push_back(in[x][y]);
	res.push_back(word);
	return res;
}

vector<string> get_words_in_grid(
	const unordered_set<string> dict,
	const vector<vector<char>> in)
{
	vector<string> res;
	vector<vector<bool>> used;
	vector<bool> empty_row; empty_row.resize(in[0].size(), false);
	used.resize(in.size(), empty_row);

	for (int i = 0; i < in.size(); i++)
	{
		for (int j = 0; j < in[0].size(); j++)
		{
			auto words = get_words(used, in, i, j);
			for (auto word : words)
			{
				if (dict.find(word) != dict.end())
				{
					res.push_back(word);
				}
			}
		}
	}
	return res;
}

int main(int argc, _TCHAR* argv[])
{
	vector<vector<char>> in;
	unordered_set<string> dict;

	in = { {'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'} };
	dict.insert("bc");
	dict.insert("f");
	dict.insert("bdh");
	dict.insert("bbb");
	dict.insert("abcfedghi");
	auto words = get_words_in_grid(dict, in);
	for (auto word : words)
	{
		cout << "word: " << word << endl;
	}
	return 0;
}

