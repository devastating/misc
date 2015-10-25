#include <iostream>
#include <sstream>
#include <vector>
#include <list>
using namespace std;

// Count Complete Tree Nodes
/**
 * Definition for a binary tree node.
 */
 
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
class Solution {
public:
    int countNodes(TreeNode* root) {
    	if (root == nullptr) return 0;
        int height = 1;
        auto node_iter = root;
        while (node_iter->left)
        {
        	node_iter = node_iter->left;
        	height++;
        }
        if (height == 1) return 1;
        
        int total_leaves = 1 << (height - 1);
        node_iter = root;
        int leaves = (1 << (height - 1)) - 1;
        int begin_lvl = 2;
        cout << "height " << height << endl;
        cout << "leaves begin " << leaves << endl;
        while (node_iter && node_iter->left)
        {
        	auto lt_iter = node_iter->left;
        	int lvl = begin_lvl;
        	while (lt_iter->right)
        	{
        		lt_iter = lt_iter->right;
        		lvl++;
        	}
        	cout << "lvl " << lvl << " total_leaves " << total_leaves << endl;;
        	total_leaves /= 2;
        	if (lvl != height)
        	{
        		node_iter = node_iter->left;
        	}
        	else
        	{
        		leaves += total_leaves;
        		node_iter = node_iter->right;
        	}
        	if (begin_lvl == height && node_iter) leaves++;
        	begin_lvl++;
        }
        return leaves;
    }
};

TreeNode *construct_tree(vector<string> nodes)
{
	stringstream ss(nodes[0]);
	int root_val;
	ss >> root_val;
	auto root = new TreeNode(root_val);
	list<TreeNode *> que;;
	
	int iter = 0;
	auto prev_node = root;
	for (int i = 1; i < nodes.size(); i++)
	{
		iter++;
		TreeNode *new_node = nullptr;
		if (nodes[i] != "#")
		{
			stringstream ss(nodes[i]);
			int new_val; ss >> new_val;
			new_node = new TreeNode(new_val);
			que.push_back(new_node);
		}
		if (iter == 1)
		{
			prev_node->left = new_node;
		}
		else if (iter == 2)
		{
			prev_node->right = new_node;
			prev_node = que.front();
			que.pop_front();
			iter = 0;
		}
	}
	return root;
}

void iterate_tree(TreeNode *node)
{
	if (node == nullptr) return;
	cout << node->val << " ";
	iterate_tree(node->left); iterate_tree(node->right);
}

void test_case(vector<string> nodes)
{
	//nodes = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
	auto tree = construct_tree(nodes);
	Solution sol;
	cout << "total nodes = " << sol.countNodes(tree) << " " << nodes.size() << endl;
}

int main() {
	// your code goes here
	vector<string> nodes = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
	test_case(nodes);
	vector<string> nodes2 = {"1", "2", "3", "4", "5", "6"};
	test_case(nodes2);
	vector<string> nodes3 = {"1", "2", "3", "4", "5", "6", "7"};
	test_case(nodes3);
	vector<string> nodes4 = {"1"};
	test_case(nodes4);
	return 0;
}