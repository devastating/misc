#include "basic_includes.hpp"

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
            for (auto char_t: t)
            {
                if (t_cnt_map.find(char_t) == t_cnt_map.end())
                {
                    t_cnt_map[char_t] = 1;
                }
                else
                {
                    t_cnt_map[char_t] += 1;
                }
            }
            // First find a substring with all t
            auto check_t_cnt_map = t_cnt_map;
            // Used to make sure we maintain subset
            map<char, int> current_set;
            int begin = -1, final_begin = 0, len = 0;
            for (size_t i = 0; i < s.size(); i++)
            {
                auto this_char = s[i];
                // Irrelavant
                if (t_cnt_map.find(this_char) == t_cnt_map.end()) continue;
                else
                {
                    if (begin == -1 && !check_t_cnt_map.empty())
                    {
                        begin = i;
                        final_begin = begin;
                    }
                }

                if (current_set.find(this_char) == current_set.end())
                {
                    current_set[this_char] = 1;
                }
                else
                {
                    current_set[this_char] += 1;
                }

                if (check_t_cnt_map.empty() == false)
                {
                    // Still trying to find set
                    if (check_t_cnt_map.find(this_char) != check_t_cnt_map.end())
                    {
                        check_t_cnt_map[this_char] -= 1;
                        if (check_t_cnt_map[this_char] == 0)
                        {
                            check_t_cnt_map.erase(this_char);
                        }
                        if (check_t_cnt_map.empty())
                        {
                            // Find first qualified substr
                            len = i - begin + 1;
                        }
                    }
                }

                if (check_t_cnt_map.empty() == true)
                {
                    for (; begin < s.length(); begin++)
                    {
                        if (t_cnt_map.find(s[begin]) == t_cnt_map.end())
                        {
                            continue;
                        }
                        if (current_set[s[begin]] <= t_cnt_map[s[begin]])
                        {
                            break;
                        }
                        current_set[s[begin]] -= 1;
                    }
                    int new_len = i - begin + 1;
                    if (new_len < len)
                    {
                        len = new_len;
                        final_begin = begin;
                    }
                }
            }
            if (len)
            {
                return s.substr(final_begin, len);
            }
            else
            {
                return string();
            }
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
    test_7();
	return 0;
}
