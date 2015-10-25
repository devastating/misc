#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;

// Permutation Sequence

class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> factors = {1};
        list<char> left;
        
        if (n == 1) return "1";

        for (int i = 0; i < n; i++)
        {
        	factors.push_back(factors[i] * (i + 2));
        	left.push_back('1' + i);
        }
        
        int digit = n;
        string result;
        while (k > 0)
        {
        	int digit_m_1 = factors[digit - 2];
        	if (k < digit_m_1)
        	{
        		//cout << "k " << k << " " << digit_m_1 << endl;
        		result.push_back(left.front());
        		left.pop_front();
        	}
        	else if (k >= digit_m_1)
        	{
        		int order = k / digit_m_1;
        		k -= order * digit_m_1;
        		if (k == 0)
        		{
        			order--;
        			auto pos = left.begin();
        			while (order)
        			{
        				pos++;
        				order--;
        			}
        			result.push_back(*pos);
        			left.erase(pos);
        			break;
        		}
        		else
        		{
        			auto pos = left.begin();
        			while (order)
        			{
        				pos++;
        				order--;
        			}
        			result.push_back(*pos);
        			left.erase(pos);
        		}
        	}
        	digit--;
        }
        while (left.empty() == false)
        {
        	result.push_back(left.back());
        	left.pop_back();
        }
        return result;
    }
};

int test(int n, int k)
{
	Solution sol;
	auto res = sol.getPermutation(n, k);
	cout << "n=" << n << " k=" << k << " res " << res << endl;
}

int main() {
	// your code goes here
	test(5, 1);
	test(5, 2);
	test(5, 3);
	test(5, 4);
	test(5, 5);
	test(5, 6);
	return 0;
}