#include "basic_includes.hpp"

using namespace std;

class Solution {
public:
    void reverseWord(string &s, int begin, size_t size)
    {
        for (size_t i = 0; i < size / 2; i++)
        {
            swap(s[i + begin], s[begin + size - 1 - i]);
        }
    }
    void clearExtraSpace(string &s)
    {
        auto begin = s.find_first_not_of(" ");
        if (begin == string::npos)
        {
            s = "";
            return;
        }
        if (begin != 0)
        {
            s = s.substr(begin);
        }
        begin = s.find(" ");
        while (begin < s.length() - 1)
        {
            if (s[begin + 1] == ' ')
            {
                // Begin to remove extra space
                int extra = 0;
                while (s[begin + extra + 1] == ' ') extra++;
                //cout << "original: " << s << " " << begin << endl;
                s = s.substr(0, begin + 1) + s.substr(begin + extra + 1);
                //cout << "extra " << extra << " " << s << "\n";
            }
            begin = s.find(" ", begin + 1);
        }
        size_t end_space = 0;
        while (s[s.length() - 1 - end_space] == ' ') end_space++;
        if (end_space > 0)
        {
            s = s.substr(0, s.length() - end_space);
        }
    }
    void reverseWords(string &s)
    {
        size_t s_len = s.length();
        reverseWord(s, 0, s_len);
        clearExtraSpace(s);

        size_t sub_word = 0;
        //cout << "initial " << s << endl;
        while (sub_word < s.length())
        {
            auto next_empty = s.find(" ", sub_word);
            size_t sub_word_size;
            if (next_empty == string::npos)
            {
                // last word to reverse
                sub_word_size = s.length() - sub_word;
                cout << "to end\n";
            }
            else
            {
                sub_word_size = next_empty - sub_word;
                //cout << "subword " << sub_word << " " << sub_word_size <<
                //    endl;
            }
            reverseWord(s, sub_word, sub_word_size);
            //cout << "looping " << s << endl;
            sub_word = next_empty + 1;
            if (next_empty == string::npos)
            {
                break;
            }
        }
    }
};

void test(string s)
{
    Solution sol;
    cout << "Input: " << s << endl;
    sol.reverseWords(s);
    cout << "Output: " << s << endl;
}

void test_remove_space()
{
    Solution sol;
    string input;
    input = "   ";
    sol.clearExtraSpace(input);
    cout << input << endl;
    input = " i  ";
    sol.clearExtraSpace(input);
    cout << input << endl;
    input = " i  bd ";
    sol.clearExtraSpace(input);
    cout << input << endl;
    input = "   a   b  c d   e  ";
    sol.clearExtraSpace(input);
    cout << input << endl;
}

int main()
{
    //test_remove_space();
    //return 0;
    string s1("I love you");
    test(s1);
    s1 = "love";
    test(s1);
    s1 = " love ";
    test(s1);
    s1 = "   a   b  c d   e  ";
    test(s1);
    return 0;
}
