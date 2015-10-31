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
    void reorderList(ListNode* head) 
    {
        if (!head || !head->next || !head->next->next) return;
        auto fast_p = head;
        auto slow_p = head;

        while (fast_p->next && fast_p->next->next)
        {
            fast_p = fast_p->next->next;
            slow_p = slow_p->next;
        }
        auto last_node = slow_p;
        while (last_node->next) last_node = last_node->next;

        auto r_iter = slow_p->next;
        slow_p->next = nullptr;
        auto reverse_list_iter = slow_p->next;
        while(r_iter)
        {
            auto tmp = r_iter->next;
            r_iter->next = reverse_list_iter;
            reverse_list_iter = r_iter;
            r_iter = tmp;
        }

        // Merge two lists
        auto list1 = head;
        auto list2 = last_node;
        while (list2)
        {
            auto tmp = list2;
            list2 = list2->next;
            tmp->next = list1->next;
            list1->next = tmp;
            list1 = tmp->next;
        }
    }
    void reorderListSlow(ListNode* head) 
    {
        // O(n^2) implementation
        if (head == nullptr) return;

        int list_len = 1;
        auto node_iter = head;
        auto prev_node = head; prev_node = nullptr;

        while (node_iter->next)
        {
            list_len++;
            prev_node = node_iter;
            node_iter = node_iter->next;
        }

        int total_round = (list_len - 1) / 2;
        auto change_head = head;
        auto change_tail = prev_node;
        for (int i = 0; i < total_round; i++)
        {
            auto tmp_node = change_head->next;
            change_head->next = change_tail->next;
            change_head->next->next = tmp_node;
            change_tail->next = nullptr;

            change_head = change_head->next->next;
            change_tail = change_head;
            while (change_tail->next && change_tail->next->next)
            {
                change_tail = change_tail->next;
            }
        }
    }
};

void test1(int size)
{
    ListNode *head = nullptr;
    ListNode *tail = nullptr;
    for (int i = 0; i < size; i++)
    {
        auto new_node = new ListNode(i + 1);
        if (head == nullptr)
        {
            head = new_node;
        }
        if (tail != nullptr)
        {
            tail->next = new_node;
        }
        tail = new_node;
    }
    auto iter = head;
    cout << "input: ";
    while (iter)
    {
        cout << iter->val << " ";
        iter = iter->next;
    }
    cout << endl;
    Solution sol;
    sol.reorderList(head);
    cout << "output: ";
    iter = head;
    while (iter)
    {
        cout << iter->val << " ";
        iter = iter->next;
    }
    cout << endl;
}

int main()
{
    test1(1);
    test1(2);
    test1(3);
    test1(4);
    test1(5);
    test1(7);
    return 0;
}
