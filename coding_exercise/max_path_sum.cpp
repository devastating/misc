#include "basic_includes.hpp"

using namespace std;

/**
 * Definition for a binary tree node.
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
        TreeNode *m_root = nullptr;
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
    public:
        static TreeNode *construct_tree(vector<string> nodes)
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
        int maxPathSum(TreeNode* root)
        {
            int root_max;
            int res = maxPathSum(root, &root_max);
            return res;
        }
        int maxPathSum(TreeNode* root, int *root_max) 
        {
            if (root == nullptr)
            {
                *root_max = 0;
                return 0;
            }

            int left_max_root, right_max_root;
            int left_max = maxPathSum(root->left, &left_max_root);
            int right_max = maxPathSum(root->right, &right_max_root);
            int max = (root->val);
            *root_max = (root->val);

            if (root->left)
            {
                if (max < (left_max_root + root->val))
                {
                    max = (left_max_root + root->val);
                }
                if (max < left_max)
                {
                    max = left_max;
                }
                if (*root_max < (root->val + left_max_root))
                {
                    *root_max = (root->val + left_max_root);
                }
            }
            if (root->right)
            {
                if (max < (right_max_root + root->val))
                {
                    max = (right_max_root + root->val);
                }
                if (max < right_max)
                {
                    max = right_max;
                }
                if (*root_max < (root->val + right_max_root))
                {
                    *root_max = (root->val + right_max_root);
                }
            }
            if (root->right && root->left)
            {
                if (max < (right_max_root + root->val + left_max_root))
                {
                    max = (right_max_root + root->val + left_max_root);
                }
            }
            return max;
        }
};

void test(vector<int> &tree_values)
{
    vector<string> tree_token;
    for (auto tree_val: tree_values)
    {
        if (tree_val == INT_MAX)
        {
            tree_token.push_back("#");
            continue;
        }
        stringstream ss; ss << tree_val;
        tree_token.push_back(ss.str());
    }
    print_vector<string>(tree_token);
    auto root = binary_tree::construct_tree(tree_token);
    Solution sol;
    cout << "Max sum: " << sol.maxPathSum(root) << endl;
}

int main()
{
    vector<int> tree_val;

    tree_val = {1,-2,-3,1,3,-2,INT_MAX,-1};
    test(tree_val);
    tree_val = {1,2,3};
    test(tree_val);
    tree_val = {-2,1};
    test(tree_val);
    return 0;
}
