#include <iostream>
#include <map>
#include <string>
using namespace std;

// Basic trie

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

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");

int test_1()
{
	Trie trie;
	string str1("sometimes");
	string str2("somet");
	string str3("someday");
	
	trie.insert(str1);trie.insert(str2);trie.insert(str3);
	//cout << str1 << " in trie? " << trie.search(str1) << endl;
	cout << str1 << " in trie? " << trie.search(str1) << " prefix? " << trie.startsWith(str1) <<endl;
	cout << str2 << " in trie? " << trie.search(str2) << endl;
	cout << str3 << " in trie? " << trie.search(str3) << endl;
	string str4("some");
	cout << str4 << " in trie? " << trie.search(str4) << " prefix? " << trie.startsWith(str4) <<endl;
}

int main() {
	// your code goes here
	test_1();
	return 0;
}