#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        bool BFSRecur(int v, map<int, vector<int>> &graph, set<int> &in_progress)
        {
            //cout << "current " << v << endl;
            if (graph.empty()) return true;
            auto graph_iter = graph.find(v);
            if (graph_iter == graph.end())
            {
                // We hit a vertex that does not have outgoing edges
                //cout << "done with " << v << endl;
                return true;
            }
            in_progress.insert(v);
            bool ret = true;
            for (auto edge: graph_iter->second)
            {
                if (in_progress.find(edge) != in_progress.end())
                {
                    //cout << "2 fail " << edge << endl;
                    ret = false;
                    break;
                }
                if (BFSRecur(edge, graph, in_progress) == false)
                {
                    //cout << "3 fail " << edge << endl;
                    ret = false;
                    break;
                }
            }
            graph.erase(v);
            in_progress.erase(v);
            return ret;
        }
        bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) 
        {
            // First construct the graph
            map<int, vector<int>> graph;
            for (auto prere: prerequisites)
            {
                auto g_vertex = graph.find(prere.first);
                if (g_vertex == graph.end())
                {
                    vector<int> tmp_vector = {prere.second};
                    graph[prere.first] = tmp_vector;
                }
                else
                {
                    g_vertex->second.push_back(prere.second);
                }
            }
            // Begin to run DFS
            set<int> in_progress;
            while (graph.empty() == false)
            {
                auto g_iter = graph.begin();
                auto can = BFSRecur(g_iter->first, graph, in_progress);
                if (can == false)
                {
                    return false;
                }
            }
            return true;
        }
};

void test(int num, vector<pair<int, int>> & preqe)
{
    for (auto preqe_iter: preqe)
    {
        cout << "(" << preqe_iter.first << ", "
        << preqe_iter.second << "), ";
    }
    cout << endl;

    Solution sol;
    if (sol.canFinish(num, preqe))
    {
        cout << "Can finish\n";
    }
    else
    {
        cout << "Cannot finish\n";
    }
}

int main()
{
    vector<pair<int, int>> input1 = {{0, 1}, {1, 0}};
    test(2, input1);
    vector<pair<int, int>> input2 = {{0, 1}, {0, 2}, {1, 2}};
    test(3, input2);
    vector<pair<int, int>> input3 = {{0, 1}, {0, 2}, {1, 2}, {3, 4}, {2, 3}};
    test(5, input3);
    vector<pair<int, int>> input4 = {{0, 1}, {0, 2}, {1, 2}, {3, 4}, {2,
        3}, {4, 0}};
    test(5, input4);
    return 0;
}
