/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
 Two elements of a binary search tree (BST) are swapped by mistake.

 Recover the tree without changing its structure. 
*/

#include "basic_includes.hpp"

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class binary_tree
{
    public:
        TreeNode *get_root() const
        {
            return m_root;
        }
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
            size_t idx = 0;
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
        void inorderTraverse(TreeNode *root)
        {
            if (!root) return;

            inorderTraverse(root->left);

            if (root->val < m_last_visit_val)
            {
                cout << "Found! " << root->val << endl;
                // Find candidate
                if (m_can.empty())
                {
                    cout << "Prev " << m_last_visit->val << endl;
                    m_can.push_back(m_last_visit);
                }
                m_can.push_back(root);
            }
            m_last_visit_val = root->val;
            m_last_visit = root;

            inorderTraverse(root->right);
        }
        void recoverTree(TreeNode* root) {
            inorderTraverse(root);
            if (m_can.empty() == false)
            {
                assert(m_can.size() == 2 || m_can.size() == 3);
                int tmp = m_can.front()->val;
                m_can.front()->val = m_can.back()->val;
                m_can.back()->val = tmp;
            }
        }
    private:
        list<TreeNode *> m_can;
        int m_last_visit_val = INT_MIN;
        TreeNode *m_last_visit = nullptr;
};

void test1()
{
    string tree_str("2|3|1|#|#|#|4|");
    binary_tree bt(tree_str);
    auto root = bt.get_root();
    Solution sol;
    sol.recoverTree(root);
    cout << bt.deserialize_to_str() << endl;;
}

void test2()
{
    string tree_str("4|7|5|1|3|#|6|#|#|#|#|#|2|");
    binary_tree bt(tree_str);
    auto root = bt.get_root();
    Solution sol;
    sol.recoverTree(root);
    cout << bt.deserialize_to_str() << endl;;
}

int main()
{
    test1();
    test2();
    return 0;
}
