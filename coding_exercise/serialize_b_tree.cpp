#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <assert.h>
using namespace std;

// Serialize/deserialize binary tree

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

int test_basic()
{
    string input("1|#|5|1|10|#|4|#|5|");
    binary_tree bt(input);
    string output = bt.deserialize_to_str();
    binary_tree bt2(output);
    string output2 = bt2.deserialize_to_str();
    if (output != output2)
    {
        cout << "in: " << output << endl;;
        cout << "out: " << output2 << endl;;
    }
}

int main() {
    // your code goes here
    test_basic();
    return 0;
}
