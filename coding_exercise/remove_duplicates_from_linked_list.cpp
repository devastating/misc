#include "basic_includes.hpp"

using namespace std;


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        ListNode* deleteDuplicates(ListNode* head) {
            auto iter = head;
            auto iter_prev = head;
            auto res = head;
            while (iter && iter->next)
            {
                if (iter->val == iter->next->val)
                {
                    // Begin to find duplicates
                    auto dup_iter = iter->next;
                    while (dup_iter && dup_iter->next)
                    {
                        if (dup_iter->val != dup_iter->next->val)
                        {
                            break;
                        }
                        dup_iter = dup_iter->next;
                    }
                    if (dup_iter->next != nullptr)
                    {
                        // Remove those in between
                        if (iter == res)
                        {
                            res = dup_iter->next;
                            iter_prev = dup_iter->next;
                        }
                        else
                        {
                            iter_prev->next = dup_iter->next;
                        }
                    }
                    else
                    {
                        // Remove those in between
                        if (iter == res)
                        {
                            res = nullptr;
                        }
                        else
                        {
                            iter_prev->next = nullptr;
                        }
                    }
                    iter = dup_iter->next;
                }
                else
                {
                    iter_prev = iter;
                    iter = iter->next;
                }
            }
            return res;
        }
};

void test(vector<int> &input)
{
    vector<ListNode> test_nodes;
    // Allocate nodes
    for (auto i: input)
    {
        auto new_node = ListNode(i);
        test_nodes.push_back(new_node);
    }
    // Link nodes
    for (size_t i = 0; i < test_nodes.size() - 1; i++)
    {
        test_nodes[i].next = &test_nodes[i + 1];
    }
    print_vector(input);
    Solution sol;
    auto res = sol.deleteDuplicates(&test_nodes[0]);
    cout << "Result: ";
    while (res)
    {
        cout << res->val << " ";
        res = res->next;
    }
    cout << endl;
}

int main()
{
    vector<int> inputs;

    inputs = {1, 2, 3, 4};
    test(inputs);
    inputs = {1, 2, 2, 4};
    test(inputs);
    inputs = {2, 2, 2, 4};
    test(inputs);
    inputs = {2, 2, 2, 2};
    test(inputs);
    inputs = {2, 2, 3, 4};
    test(inputs);
    inputs = {2, };
    test(inputs);
    return 0;
}
