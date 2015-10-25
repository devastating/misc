#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// Comparing version number

class Solution {
public:
    void get_version_values(string version, vector<int> &result)
    {
        int pos = 0;
        while(pos != version.length())
        {
            int dot_pos = version.find(".", pos);
            string digit_str;
            if (dot_pos != version.npos)
            {
                digit_str = version.substr(pos, dot_pos - pos);
                pos = dot_pos + 1;
                //cout << digit_str << endl;
            }
            else
            {
                digit_str = version.substr(pos);
                pos = version.length();
                //cout << digit_str << endl;
            }
            stringstream ss(digit_str);
            int val; ss >> val;
            //cout << val << endl;
            result.push_back(val);
        }
    }
    int compareVersion(string version1, string version2) {
    	vector<int> ver1_nums, ver2_nums;
        get_version_values(version1, ver1_nums);
        get_version_values(version2, ver2_nums);
        int iter = ver1_nums.size() < ver2_nums.size()? ver1_nums.size(): ver2_nums.size();
        for (int i = 0; i < iter; i++)
        {
        	//cout << ver1_nums[i] << " " << version2[i] << endl;
        	if (ver1_nums[i] > ver2_nums[i]) return 1;
        	else if (ver1_nums[i] < ver2_nums[i]) return -1;
        }
        //cout << ver1_nums.size() << " " << ver2_nums.size() << endl;
        if (ver1_nums.size() == ver2_nums.size()) return 0;
        auto left_nums = ver1_nums.size() > ver2_nums.size()? &ver1_nums: &ver2_nums;
        for (auto left_iter = iter; left_iter < left_nums->size(); left_iter++)
        {
        	if (left_nums->at(left_iter) != 0)
        	{
        		return left_nums == &ver1_nums? 1: -1;
        	}
        }
        return 0;
        //cout << "WTF?" << endl;
    }
};

void test_case1()
{
	string v1("01"), v2("1");
	Solution sol;
	cout << sol.compareVersion(v1, v2) << endl;
}

void test_case2()
{
	string v1("1"), v2("1.0");
	Solution sol;
	cout << sol.compareVersion(v1, v2) << endl;
}

int main() {
	// your code goes here
	test_case1();
	test_case2();
	return 0;
}