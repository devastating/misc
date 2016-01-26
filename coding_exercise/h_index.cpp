#include "basic_includes.hpp"

using namespace std;

class Solution {
    public:
        int hIndex(vector<int>& citations) 
        {
            int papers = citations.size();

            sort(citations.begin(), citations.end(), greater<int>());
            for (int i = papers - 1; i >= 0; i--)
            {
                if (citations[i] >= i + 1) return i + 1;
            }

            return 0;
        }
};

void test(vector<int> &citations)
{
    print_vector<int>(citations);
    Solution sol;
    cout << "h-index " << sol.hIndex(citations) << endl;
}

int main()
{
    vector<int> in;

    in = {3, 0, 6, 1, 5};
    test(in);
    in = {3, 3, 3, 3, 5};
    test(in);
    in = {1};
    test(in);
    in = {0};
    test(in);
    in = {1, 1};
    test(in);
    in = {};
    test(in);
    in = {0, 0, 0, 0};
    test(in);
    return 0;
}
