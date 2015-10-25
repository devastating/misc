#include <iostream>
#include <unordered_set>
#include <vector>
#include <deque>

using namespace std;

// word ladder
// key - the original approach is enough. But I forgot the critical "queue_dedup",
// which is used to detect whether a work has been to queue or not.
// NOTE: BFS need to to dedup, otherwise you will go into infinite loop !!!

class Solution {
	struct BFSNode
	{
		//unordered_set<string> included_items;
		int level;
		string last_item;
	};
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
    	deque<struct BFSNode> g_queue;

		BFSNode init_node;
		unordered_set<string> q_dedup;
		//init_node.included_items.insert(beginWord);
		init_node.level = 1;
		init_node.last_item = beginWord;
		g_queue.push_back(init_node);
		
		int total = 0;
    	while (g_queue.empty() == false)
    	{
    		auto node = g_queue.front();
    		g_queue.pop_front();
    		print_node(node);
        	// Already included
    		if (valid_next(node.last_item, endWord))
    		{
    			//cout << "Found! " << endl;
    			print_node(node);
    			//total = node.included_items.size() + 1;
    			total = node.level + 1;
    			break;
    		}
    		vector<string> candidates;
    		find_possible_next(node.last_item, wordList, candidates);
    		for (auto dict_iter: candidates)
    		{
    			//if (node.included_items.find(dict_iter) != node.included_items.end()) continue;
    			if (q_dedup.find(dict_iter) != q_dedup.end()) continue;
    			//if (valid_next(node.last_item, dict_iter))
    			//{
    				q_dedup.insert(dict_iter);
    				//auto last_item = node.last_item;
    				//node.included_items.insert(dict_iter);
    				node.level += 1;
    				node.last_item = dict_iter;
    				print_node(node);
    				g_queue.push_back(node);
    				// Recover
    				//node.included_items.erase(dict_iter);
    				node.level -= 1;
    				//node.last_item = last_item;
    			//}
    		}
    		if (total) break;
    	}
    	return total;
    }
private:
	void print_node(BFSNode &node)
	{
		//return;
		//cout << "included: ";
		//for (auto iter: node.included_items)
		//{
		//	cout << iter << " ";
		//}
		//cout << "last: " << node.last_item << " lvl: " << node.level << endl;
	}
    bool valid_next(string &a, string &b)
	{
		if (a.length() != b.length()) return false;
		int diff = 0;
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] != b[i]) diff++;
			if (diff > 1) break;
		}
		return (diff == 1);
	}
	void find_possible_next(string &a, unordered_set<string>& dict, vector<string>& out)
	{
		out.clear();
		for (int i = 0; i < a.size(); i++)
		{
			string new_word = a;
			for (int j = 0; j < 26; j++)
			{
				new_word[i] = 'a' + j;
				if (dict.find(new_word) != dict.end()) out.push_back(new_word);
			}
		}
	}
};

class SolutionDFS {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
    	vector<string> candidates;
    	
    	if (valid_next(beginWord, endWord))
    	{
    		// Found it!
    		return 2;
    	}
        for (auto w_iter: wordList)
        {
        	if (valid_next(w_iter, beginWord))
        	{
        		candidates.push_back(w_iter);
        	}
        }
        if (candidates.empty()) return 0;
        
        int min_length = wordList.size() + 1;
        for (auto can_iter: candidates)
        {
        	wordList.erase(can_iter);
        	int from_here = ladderLength(can_iter, endWord, wordList);
        	if (from_here != 0 && from_here < min_length)
        	{
        		min_length = from_here;
        	}
        	wordList.insert(can_iter);
        }
        return (min_length == wordList.size() + 1)? 0: min_length + 1;
    }
private:
	bool valid_next(string &a, string &b)
	{
		if (a.length() != b.length()) return false;
		int diff = 0;
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] != b[i]) diff++;
		}
		return (diff == 1);
	}
};

void test_basic()
{
	string begin = "hit";
	string end = "cog";
	unordered_set<string> dict;
	dict.insert("hot");
	dict.insert("dot");
	dict.insert("dog");
	dict.insert("lot");
	dict.insert("log");
	Solution sol;
	cout << "out: " << sol.ladderLength(begin, end, dict) << endl;
}

void test_leetcode()
{
	string begin = "cet";
	string end = "ism";
	vector<string> dict_v = {"kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her","nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob"};
	unordered_set<string> dict;
	for (auto iter: dict_v)
	{
		dict.insert(iter);
	}
	Solution sol;
	cout << "out: " << sol.ladderLength(begin, end, dict) << endl;
}

int main() {
	// your code goes here
	test_basic();
	test_leetcode();
	return 0;
}