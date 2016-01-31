#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        vector<int> findSubstring(string s, vector<string>& words)
        {
            vector<int> res;
            unordered_map<string, int> words_map;

            if (s.empty() || words.empty()) return res;

            for (auto word: words)
            {
                if (words_map.find(word) == words_map.end())
                {
                    words_map[word] = 1;
                }
                else
                {
                    words_map[word] += 1;
                }
            }

            int word_len = words[0].length();
            int min_len = word_len * words.size();
            if (s.length() < min_len) return res;
            for (int i = 0; i <= s.length() - min_len; i++)
            {
                auto s_str = s.substr(i, word_len);
                if (words_map.find(s_str) != words_map.end())
                {
                    auto cloned_words_map = words_map;
                    cloned_words_map[s_str] -= 1;
                    if (cloned_words_map[s_str] == 0)
                    {
                        cloned_words_map.erase(s_str);
                        if (cloned_words_map.empty())
                        {
                            // Find one
                            res.push_back(i);
                            continue;
                        }
                    }
                    unsigned substr_idx = i + word_len;
                    while (substr_idx < s.length())
                    {
                        auto s_str = s.substr(substr_idx, word_len);
                        if (cloned_words_map.find(s_str) != cloned_words_map.end())
                        {
                            cloned_words_map[s_str] -= 1;
                            if (cloned_words_map[s_str] == 0)
                            {
                                cloned_words_map.erase(s_str);
                                if (cloned_words_map.empty())
                                {
                                    // Find one
                                    res.push_back(i);
                                    break;
                                }
                            }
                        }
                        else break;

                        substr_idx += word_len;
                    }
                }
            }
            return res;
        }
};

void test(string s, vector<string>& words)
{
    print_vector<string>(words, "dict");
    cout << "S: " << s << endl;
    Solution sol;
    auto index = sol.findSubstring(s, words);
    print_vector<int>(index, "index");
}

int main()
{
    string s;
    vector<string> words;

    s = "barfoothefoobarman";
    words = {"foo", "bar"};
    test(s, words);
    s = "barfoofoothefoobarman";
    words = {"foo", "bar", "foo"};
    test(s, words);
    s = "barfoofoothefoobarfo";
    words = {"foo"};
    test(s, words);
    s = "a";
    words = {"a", "a"};
    test(s, words);
    return 0;
}
