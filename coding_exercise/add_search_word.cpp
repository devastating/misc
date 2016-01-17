#include "basic_includes.hpp"

using namespace std;

class Trie
{
    struct trie_node
    {
        char m_val;
        bool m_has_word;
        map<char, trie_node *> m_next;
        void add_child(string word)
        {
            if (word.length() == 0)
            {
                m_has_word = true;
            }
            else
            {
                if (m_next.find(word[0]) == m_next.end())
                {
                    auto new_node = new trie_node;
                    new_node->m_val = word[0];
                    new_node->m_has_word = false;
                    m_next[word[0]] = new_node;
                }
                m_next[word[0]]->add_child(word.substr(1));
            }
        }
        bool find_child(string word)
        {
            if (word.length() == 0)
            {
                return m_has_word? true: false;
            }
            if (word[0] == '.')
            {
                for (auto child: m_next)
                {
                    if (child.second->find_child(word.substr(1)))
                    {
                        return true;
                    }
                }
                return false;
            }

            if (m_next.find(word[0]) == m_next.end())
            {
                return false;
            }
            return m_next[word[0]]->find_child(word.substr(1));
        }
    };

    public:
        void insert(string word)
        {
            if (word.length() == 0)
            {
                return;
            }
            if (m_root.m_next.find(word[0]) == m_root.m_next.end())
            {
                auto new_node = new trie_node;
                new_node->m_val = word[0];
                new_node->m_has_word = false;
                m_root.m_next[word[0]] = new_node;
            }
            m_root.m_next[word[0]]->add_child(word.substr(1));
        }
        bool search(string word)
        {
            if (word.length() == 0)
            {
                return false;
            }
            if (m_root.m_next.find(word[0]) == m_root.m_next.end())
            {
                return false;
            }
            return m_root.m_next[word[0]]->find_child(word.substr(1));
        }
        bool search_re(string word)
        {
            if (word.length() == 0)
            {
                return false;
            }

            if (word[0] == '.')
            {
                for (auto child: m_root.m_next)
                {
                    if (child.second->find_child(word.substr(1)))
                    {
                        return true;
                    }
                }
                return false;
            }

            if (m_root.m_next.find(word[0]) == m_root.m_next.end())
            {
                return false;
            }
            return m_root.m_next[word[0]]->find_child(word.substr(1));
        }
    private:
        trie_node m_root;
};

class WordDictionary {
    public:

        // Adds a word into the data structure.
        void addWord(string word) {
            m_trie.insert(word);
        }

        // Returns if the word is in the data structure. A word could
        // contain the dot character '.' to represent any one letter.
        bool search(string word) {
            return m_trie.search_re(word);
        }
    private:
        Trie m_trie;
};

void test_word_dict()
{
    WordDictionary dict;
	string str1("bad");
	string str2("dad");
	string str3("mad");

    dict.addWord(str1);
    dict.addWord(str2);
    dict.addWord(str3);
    cout << str1 << " insert in dict\n";
    cout << str2 << " insert in ditc\n";
    cout << str3 << " insert in dict\n";
    str1 = "pad";
    cout << str1 << " in dict? " << dict.search(str1) << endl;
    str1 = "bad";
    cout << str1 << " in dict? " << dict.search(str1) << endl;
    str1 = ".ad";
    cout << str1 << " in dict? " << dict.search(str1) << endl;
    str1 = "b..";
    cout << str1 << " in dict? " << dict.search(str1) << endl;
}

void test_trie()
{
	Trie trie;
	string str1("sometimes");
	string str2("somet");
	string str3("someday");
	
	trie.insert(str1);
    cout << str1 << " insert in trie\n";
    cout << str2 << " insert in trie\n";
    cout << str3 << " insert in trie\n";
    trie.insert(str2);trie.insert(str3);
	//cout << str1 << " in trie? " << trie.search(str1) << endl;
	cout << str1 << " in trie? " << trie.search(str1) << endl;
	cout << str2 << " in trie? " << trie.search(str2) << endl;
	cout << str3 << " in trie? " << trie.search(str3) << endl;
	string str4("some");
	cout << str4 << " in trie? " << trie.search(str4) <<endl;
    str4 = "so.et";
	cout << str4 << " in trie? " << trie.search_re(str4) <<endl;
    str4 = ".o...";
	cout << str4 << " in trie? " << trie.search_re(str4) <<endl;
}

int main()
{
    //test_trie();
    test_word_dict();
    return 0;
}
