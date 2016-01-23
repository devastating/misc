#include "basic_includes.hpp"

using namespace std;

int word_distance(const vector<string> &list, string w1, string w2)
{
    int res = INT_MAX;
    string current_word;
    unsigned cur_idx;
    for (unsigned i = 0; i < list.size(); i++)
    {
        if (list[i] != w1 && list[i] != w2) continue;

        if (current_word.length() == 0)
        {
            current_word = list[i];
            cur_idx = i;
            continue;
        }
        if (current_word == list[i])
        {
            cur_idx = i;
            continue;
        }
        else
        {
            int new_dist = i - cur_idx;
            if (new_dist < res)
            {
                res = new_dist;
            }
            current_word = list[i];
            cur_idx = i;
        }
    }
    return (res == INT_MAX)? 0: res;
}

void test(const vector<string> &list, string w1, string w2)
{
    print_vector<string>(list);
    cout << "word distance " << word_distance(list, w1, w2) << endl;
}

int main()
{
    vector<string> list;
    list = {"make", "love"};
    test(list, "make", "love");
    list = {"make", "love", "fuck", "me", "make"};
    test(list, "make", "me");
    return 0;
}
