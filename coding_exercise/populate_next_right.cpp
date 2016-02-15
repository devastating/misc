#include "basic_includes.hpp"

using namespace std;

/*
 * Definition for binary tree with next pointer.
 */
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
    public:
        void connect(TreeLinkNode *root) {

            if (root == nullptr)
            {
                return;
            }

            list<TreeLinkNode *> queue;
            queue.push_back(root);
            auto stop = root;
            while (queue.empty() == false)
            {
                TreeLinkNode *prev = nullptr;
                while (queue.empty() == false)
                {
                    auto node_iter = queue.front();
                    queue.pop_front();
                    if (node_iter->right) queue.push_back(node_iter->right);
                    if (node_iter->left) queue.push_back(node_iter->left);
                    node_iter->next = prev;
                    prev = node_iter;
                    if (node_iter == stop) break;
                }
                stop = queue.back();
            }
        }
};
