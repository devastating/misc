#include <iostream>
#include <string>
#include <set>
#include <map>
#include <list>
using namespace std;

// Minimum Window Substring
#if 0
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"

Minimum window is "BANC".
#endif

class Solution
{
    public:
        string minWindow(string s, string t)
        {
            map<char, int> t_cnt_map;

            // Create t char to counter map
            for (auto t_iter: t)
            {
                if (t_cnt_map.find(t_iter) == t_cnt_map.end())
                {
                    t_cnt_map[t_iter] = 1;
                }
                else
                {
                    t_cnt_map[t_iter] += 1;
                }
            }

            map<char, int> s_cnt_map;
            auto t_cnt_map_copy = t_cnt_map;
            int begin_idx = -1, win_sz = 0;
            size_t s_idx;
            for (s_idx = 0; s_idx < s.length(); s_idx++)
            {
                // Skip irrevalent
                if (t_cnt_map.find(s[s_idx]) == t_cnt_map.end()) continue;

                if (s_cnt_map.find(s[s_idx]) == s_cnt_map.end())
                {
                    s_cnt_map[s[s_idx]] = 1;
                }
                else
                {
                    s_cnt_map[s[s_idx]] += 1;
                }

                if (begin_idx == -1)
                {
                    begin_idx = s_idx;
                }
                if (s[s_idx] == s[begin_idx])
                {
                    while (t_cnt_map.find(s[begin_idx]) == t_cnt_map.end() || s_cnt_map[s[begin_idx]] > t_cnt_map[s[begin_idx]])
                    {
                        if (s_cnt_map.find(s[begin_idx]) != s_cnt_map.end())
                        {
                            s_cnt_map[s[begin_idx]] -= 1;
                        }
                        begin_idx++;
                    }
                }
                if (t_cnt_map_copy.find(s[s_idx]) != t_cnt_map_copy.end())
                {
                    t_cnt_map_copy[s[s_idx]] -= 1;
                    if (t_cnt_map_copy[s[s_idx]] == 0)
                    {
                        t_cnt_map_copy.erase(s[s_idx]);
                    }
                    if (t_cnt_map_copy.empty())
                    {
                        // Found a starting win!
                        win_sz = s_idx - begin_idx + 1;
                        cout << "begin win: " << begin_idx << " size " << win_sz << endl;
                        break;
                    }
                }
            }
            // No even a window
            if (win_sz == 0) return string("");

            int win_begin = begin_idx;
            // Scan rest of s string
            s_idx++;
            for (; s_idx < s.length(); s_idx++)
            {
                // Skip irrevalent
                if (t_cnt_map.find(s[s_idx]) == t_cnt_map.end()) continue;

                if (s_cnt_map.find(s[s_idx]) == s_cnt_map.end())
                {
                    s_cnt_map[s[s_idx]] = 1;
                }
                else
                {
                    s_cnt_map[s[s_idx]] += 1;
                }                
                if (s[s_idx] == s[begin_idx])
                {
                    while (t_cnt_map.find(s[begin_idx]) == t_cnt_map.end() || s_cnt_map[s[begin_idx]] > t_cnt_map[s[begin_idx]])
                    {
                        if (s_cnt_map.find(s[begin_idx]) != s_cnt_map.end())
                        {
                            s_cnt_map[s[begin_idx]] -= 1;
                        }
                        begin_idx++;
                    }
                    // Calculate new window length
                    int new_win_len = s_idx - begin_idx + 1;
                    if (new_win_len < win_sz)
                    {
                        win_begin = begin_idx;
                        win_sz = new_win_len;
                        cout << "new win: " << begin_idx << " size " << win_sz << endl;
                    }
                }
            }
            return s.substr(win_begin, win_sz);
        }
};

int test_1()
{
	string s("ADOBECODEBANC");
	string t("ABC");
	Solution sol;
	cout << __func__ << " " << sol.minWindow(s, t) << endl;;
}

int test_2()
{
	string s("AODBDCCBA");
	string t("ABC");
	Solution sol;
	cout << __func__ << " " << sol.minWindow(s, t) << endl;;
}

int test_3()
{
	string s("AB");
	string t("B");
	Solution sol;
	cout << __func__ << " " << sol.minWindow(s, t) << endl;;
}

int test_4()
{
	string s("BBA");
	string t("AB");
	Solution sol;
	cout << __func__ << " " << sol.minWindow(s, t) << endl;;
}

int test_5()
{
	string s("AA");
	string t("AA");
	Solution sol;
	cout << __func__ << " " << sol.minWindow(s, t) << endl;;
}

int test_6()
{
	string s("ACBBACA");
	string t("ABA");
	Solution sol;
	cout << __func__ << " " << sol.minWindow(s, t) << endl;;
}

int test_7()
{
	string s("vlssjudabstgkzxzcpglfgogiwkowyvulnmujpwkjrqvsnwvdcikjwqtsdhrdclorxkaoikazbvuqspvwxhhvybndieglrucqgfhophpsejlwagtzoauobkrmqzzivdybifpyoestqdrqkmqapkoquhenidvdhvepdvprbimrneizsyzhkpyhyeugirjropgrmyloixfvdnvwnwdamdhmidtsuejiwrcipnwzmevqrsohqrhexqrhtkzpqkzobbxtqvsdzpvtjjcacjezbxiwhjlatmoxonqejkhkcednnfnqqurrrcnbladfntcdhuhserciviwlnldgfwxzynakpfpcythfnrxtkcchkaszlvftsfsqsuajbrozkvhzmgtwixesxwukuzdoexgytjiuawuntbmghhcseimbhgobgrrmrxnkgxfhvbwoeiulqzdwhsaoyorghityggjmdqvyttoxclkukqqtiqkggbnomimuqxitpgtizjfduqxggqaoimwppjdbrrvjpgeemxpljupdmokseminyfenqjrkaotruyygxnsgjjmwxwqckzrigxxygoigdcaxcyeznyiwhuueslicmbmuyjseybnbfnahleiaeqwlmrseeaiqcukaecfefsfmhhtumeuqwqejjwpnyyfaupdyukebejoltjffnzxmrdvdzksykyafpdflnknrvbeomlvckvoeyjjyvbyizypreucrgplcsrsfdohpjvvh");
	string t("gehdgflhgaykx");
	Solution sol;
	cout << __func__ << " " << sol.minWindow(s, t) << endl;;
}


int main() {
	// your code goes here
	//test_8();
	//return 0;
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();
	test_6();
	return 0;
}
