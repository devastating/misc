// Non recursive w/o parent pointer

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

void postorder_traversal_iterative(TreeNode *root,
                                   vector<int> *ret)
{
    TreeNode *prev = nullptr;
    vector<TreeNode *> stack;

    stack.push_back(root);
    while (stack.empty() == false)
    {
        auto top = stack.back();

        if (top->right == nullptr && top->left == nullptr)
        {
            ret->push_back(top->val);
            stack.pop_back();
        }
        else
        {
            if (!prev || prev->right == top || prev->left == top)
            {
                if (top->left)
                {
                    stack.push_back(top->left);
                }
                else if (top->right)
                {
                    stack.push_back(top->right);
                }
                else
                {
                    ret->push_back(top->val);
                    stack.pop_back();
                }
            }
            else if (top->left == prev || top->right == prev)
            {
                if (top->left == prev)
                {
                    if (top->right)
                    {
                        stack.push_back(top->right);
                    }
                    else
                    {
                        ret->push_back(top->val);
                        stack.pop_back();
                    }
                }
                else
                {
                    ret->push_back(top->val);
                    stack.pop_back();
                }
            }
            else
            {
                assert(false);
            }
        }
        prev = top;
    }
}

void test(string input)
{
    cout << "Input: " << input << endl;
    binary_tree bt(input);
    vector<int> out;
    postorder_traversal_iterative(bt.m_root, &out);
    print_vector<int>(out, "Output");
}

int main()
{
    string input;
    
    input = "1|#|5|1|10|#|4|#|5|";
    test(input);

    return 0;
}
