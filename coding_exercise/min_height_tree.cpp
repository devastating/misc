#include "basic_includes.hpp"

using namespace std;

class Solution {

#define NEW 0
#define IN_STACK 1 
#define DONE 2 
    struct node
    {
        int val;
        int height;
        vector<struct node *> links;
    };

    public:
        vector<int> findDistNode(int begin, int dist)
        {
            vector<int> ret;
            if (dist == 0)
            {
                ret.push_back(begin);
                return ret;
            }
            //cout << __func__ << " " << begin << " " << dist << endl;
            for (int i = 0; i < m_node_length; i++)
            {
                m_in_use[i] = NEW;
                m_nodes[i].height = 0;
            }

            vector<int> dfs_stack;
            m_in_use[begin] = IN_STACK;
            dfs_stack.push_back(begin);
            while(!dfs_stack.empty())
            {
                int node_id = dfs_stack.back();
                if (0 && m_nodes[node_id].height == dist)
                {
                    ret.push_back(m_nodes[node_id].val);
                    //cout << "found " <<  m_nodes[node_id].val<< endl;
                }
                assert(m_in_use[node_id] != DONE);
                bool done = true;
                for (auto n_node_ptr: m_nodes[node_id].links)
                {
                    if (m_in_use[n_node_ptr->val] == NEW)
                    {
                        done = false;
                        n_node_ptr->height = m_nodes[node_id].height + 1;
                        if (n_node_ptr->height == dist)
                        {
                            //cout << "found2 " << n_node_ptr->val << endl;
                            ret.push_back(n_node_ptr->val);
                        }
                        m_in_use[n_node_ptr->val] = IN_STACK;
                        dfs_stack.push_back(n_node_ptr->val);
                        break;
                    }
                }
                if (done)
                {
                    m_in_use[node_id] = DONE;
                    dfs_stack.pop_back();
                }
            }
            return ret;
        }
        int findFarestNode(int begin, int *node)
        {
            for (int i = 0; i < m_node_length; i++)
            {
                m_in_use[i] = NEW;
                m_nodes[i].height = 0;
            }
            //cout << __func__ << " " << begin << " " << endl;

            vector<int> dfs_stack;
            m_in_use[begin] = IN_STACK;
            dfs_stack.push_back(begin);
            int max_height = 0;
            while(!dfs_stack.empty())
            {
                int node_id = dfs_stack.back();
                assert(m_in_use[node_id] != DONE);
                bool done = true;
                for (auto n_node_ptr: m_nodes[node_id].links)
                {
                    if (m_in_use[n_node_ptr->val] == NEW)
                    {
                        done = false;
                        n_node_ptr->height = m_nodes[node_id].height + 1;
                        //cout << n_node_ptr->val << " h=" << n_node_ptr->height << endl;
                        if (n_node_ptr->height > max_height)
                        {
                            *node = n_node_ptr->val;
                            max_height = n_node_ptr->height;
                            //cout << *node << " max h " << max_height << endl;
                        }
                        m_in_use[n_node_ptr->val] = IN_STACK;
                        dfs_stack.push_back(n_node_ptr->val);
                    }
                }
                if (done)
                {
                    m_in_use[node_id] = DONE;
                    dfs_stack.pop_back();
                }
            }
            return max_height;
        }
        vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
            vector<int> res; 
            if (n == 0)
            {
                return res;
            }
            if (n == 1)
            {
                res.push_back(0);
                return res;
            }
            m_node_length = n;
            m_nodes.resize(n);
            m_in_use.resize(m_node_length, NEW);
            for (int i = 0; i < n; i++)
            {
                m_nodes[i].val = i;
                m_nodes[i].links.clear();
            }
            for (auto edge: edges)
            {
                m_nodes[edge.first].links.push_back(&m_nodes[edge.second]);
                m_nodes[edge.second].links.push_back(&m_nodes[edge.first]);
            }

            int node, node2;
            findFarestNode(0, &node);
            //cout << node << " Farest1 " << dist << endl;
            auto dist2 = findFarestNode(node, &node2);
            //cout << node2 << " Farest2 " << dist2 << endl;
            auto ret = findDistNode(node, (dist2)/2);
            auto ret2 = findDistNode(node2, (dist2)/2);
            set<int> dedup;
            for (auto node_val: ret)
            {
                dedup.insert(node_val);
            }
            for (auto node_val: ret2)
            {
                if (dedup.find(node_val) != dedup.end())
                {
                    res.push_back(node_val);
                    break;
                }
            }
            if (res.empty())
            {
                set<pair<int, int>> dedup_edges;
                for (auto edge: edges)
                {
                    dedup_edges.insert(edge);
                }
                for (auto node1: ret)
                {
                    for (auto node2: ret2)
                    {
                        pair<int, int> a = {node1, node2};
                        pair<int, int> b = {node2, node1};
                        if (dedup_edges.find(a) != dedup_edges.end() ||
                            dedup_edges.find(b) != dedup_edges.end())
                        {
                            res.push_back(node1);
                            res.push_back(node2);
                            return res;
                        }
                    }
                }
            }
            return res;
        }
    private:
        int m_node_length;
        vector<struct node> m_nodes;
        vector<int> m_in_use;
};

void test(int n, vector<pair<int, int>> &edges)
{
    cout << n << " nodes\n";
    for (auto edge: edges)
    {
        cout << "(" << edge.first << "," << edge.second << ") ";
    }
    cout << endl;
    Solution sol;
    auto res = sol.findMinHeightTrees(n, edges);
    cout << "Result: ";
    for (auto node: res)
    {
        cout << node << " ";
    }
    cout << endl;
}

int main()
{
    vector<pair<int, int>> test_input;
#if 1
    test_input = {{0, 1}};
    test(2, test_input);
    test_input = {{0, 1}, {1, 2}, {1, 3}};
    test(4, test_input);
    test_input = {{0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 4}};
    test(6, test_input);
    test_input = {};
    test(1, test_input);
    test_input = {};
    test(0, test_input);
#endif
    test_input = {{0,1},{0,2},{0,3},{3,4},{4,5}};
    test(6, test_input);
    return 0;
}
