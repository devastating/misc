#include "basic_includes.hpp"

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x = 0) : val(x), next(NULL) {}
};

class Solution {
    public:
        ListNode* rotateRight(ListNode* head, int k)
        {
            if (head == nullptr) return head;

            int list_len = 0;
            auto node_iter = head;
            auto list_tail = head;
            while (node_iter)
            {
                list_len++;
                list_tail = node_iter;
                node_iter = node_iter->next;
            }

            k %= list_len;
            if (k == 0) return head;
            //cout << "k is " << k << endl;
            auto new_head = head;
            auto new_tail = head;
            k = list_len - k;
            while (k)
            {
                k--;
                new_tail = new_head;
                new_head = new_head->next;
            }
            if (new_head == nullptr)
            {
                list_tail->next = head;
                new_head = head->next;
                head->next = nullptr;
            }
            else
            {
                cout << "new head " << new_head->val << endl;
                list_tail->next = head;
                new_tail->next = nullptr;
            }
            return new_head;
        }
};

void test(vector<int> &in, int k)
{
    vector<ListNode> list;
    list.resize(in.size());
    for (size_t i = 0; i < in.size(); i++)
    {
        list[i].val = in[i];
        if (i != in.size() - 1)
        {
            list[i].next = &list[i + 1];
        }
    }
    print_vector<int>(in);
    Solution sol;
    auto new_head = sol.rotateRight(&list[0], k);
    cout << "Output: ";
    while (new_head)
    {
        cout << new_head->val << " ";
        new_head = new_head->next;
    }
    cout << endl;
}

int main()
{
    vector<int> input;

    input = {1, 2, 3};
    test(input, 2000000000);
    input = {1, 2, 3, 4, 5};
    test(input, 2);
    input = {1, 2, 3, 4, 5};
    test(input, 1);
    input = {1};
    test(input, 201);
    return 0;
}
