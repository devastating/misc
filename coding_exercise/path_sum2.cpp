
#include "basic_includes.hpp"
using namespace std;


/**
 ** Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class binary_tree
{
    public:
        TreeNode *m_root = nullptr;
        binary_tree(string serialized_str)
        {
            vector<string> tree_nodes;
            tree_str_preprocessor(serialized_str, tree_nodes);
            m_root = construct_tree(tree_nodes);
        }
        string deserialize_to_str()
        {
            list<TreeNode *> que;
            string res;
            stringstream ss;
            que.push_back(m_root);
            while (que.empty() != true)
            {
                auto node = que.front();
                que.pop_front();
                if (node != nullptr)
                {
                    ss << node->val << "|";
                }
                else
                {
                    ss << "#|";
                }
                if (node)
                {
                    que.push_back(node->left);
                    que.push_back(node->right);
                }
            }
            return ss.str();
        }
    private:
        void tree_str_preprocessor(string serialized_str, vector<string> &out)
        {
            int idx = 0;
            while (idx < serialized_str.length())
            {
                int stop_idx = serialized_str.find('|', idx);
                if (stop_idx == string::npos) break;
                out.push_back(serialized_str.substr(idx, stop_idx - idx));
                idx = stop_idx + 1;
                if (idx == serialized_str.length()) break;
            }
        }
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
                    if (que.empty() == true)
                    {
                        assert(i == (nodes.size() - 1));
                        break;
                    }
                    prev_node = que.front();
                    que.pop_front();
                    iter = 0;
                }
            }
            return root;
        }
};

class Solution {
    public:
        vector<vector<int>> pathSum(TreeNode* root, int sum)
        {
            vector<vector<int>> res;
            vector<int> current;

            pathWalker(&res, &current, root, sum);
            return res;
        }

        void pathWalker(vector<vector<int>> *res, vector<int> *current,
                        TreeNode *root, int sum)
        {
            if (root == nullptr)
            {
                return;
            }
            if (root->left == nullptr && root->right == nullptr)
            {
                if (sum == root->val)
                {
                    // Found one path
                    current->push_back(root->val);
                    res->push_back(*current);
                    current->pop_back();
                }
            }
            else
            {
                current->push_back(root->val);
                sum -= root->val;
                if (root->left)
                {
                    pathWalker(res, current, root->left, sum);
                }
                if (root->right)
                {
                    pathWalker(res, current, root->right, sum);
                }
                current->pop_back();
            }
        }
};

void test(string input, int sum)
{
    cout << "Input: " << input << endl;
    cout << "Sum of path is " << sum << endl;
    binary_tree bt(input);
    vector<int> out;
    Solution sol;
    auto res = sol.pathSum(bt.m_root, sum);
    for (auto path: res)
    {
        print_vector<int>(path, "One path");
    }
}

int main()
{
    string input;
    
    input = "5|4|8|11|#|13|4|7|2|#|#|5|1|";
    test(input, 22);
    input = "5|";
    test(input, 2);
    input = "5|";
    test(input, 5);

    return 0;
}
