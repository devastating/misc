#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
static const double NOT_FOUND = (double)-1000000;

double findMedianSortedArraysInN1(vector<int>& nums1, vector<int>& nums2)
{
    if (nums1.empty() == true && nums2.empty() == true)
    {
        // WTF?
        return 0;
    }

    int target_mid = (nums1.size() + nums2.size()) / 2;
    // First go through nums1 array
    int begin_idx = 0, end_idx = nums1.size() - 1;
    int mid_idx;
    bool found = false;

    while(end_idx >= begin_idx)
    {
        mid_idx = begin_idx + (end_idx - begin_idx + 1) / 2;
        //cout << begin_idx << " - " << end_idx << ", " << mid_idx << endl;
        int left_cnt = target_mid - mid_idx;

        int mid_val = nums1[mid_idx];

		if (left_cnt < 0)
		{
			end_idx = mid_idx - 1;
			continue;
		}
		
		if (left_cnt == 0)
		{
			if (nums1[mid_idx] <= nums2[0])
			{
				found = true;
				//cout << __LINE__ << endl;
				break;
			}
			else
			{
				end_idx = mid_idx - 1;
				//cout << __LINE__ << endl;
				continue;
			}
		}
		
        if (left_cnt == nums2.size())
        {
            if (nums2[left_cnt - 1] <= mid_val)
            {
                // Found it
                found = true;
                //cout << __LINE__ << endl;
                break;
            }
            else
            {
            	begin_idx = mid_idx + 1;
            	//cout << __LINE__ << endl;
            	continue;
            }
        }
        else if (left_cnt > nums2.size())
        {
        	begin_idx = mid_idx + 1;
        	//cout << __LINE__ << endl;
        	continue;
        }

        int before_mid_val = nums2[left_cnt - 1];
        int after_mid_val = nums2[left_cnt];
        if (before_mid_val <= mid_val && after_mid_val >= mid_val)
        {
            // Found
            found = true;
            //cout << __LINE__ << endl;
            break;
        }
        if (before_mid_val > mid_val && after_mid_val > mid_val)
        {
            begin_idx = mid_idx + 1;
            //cout << "AFt " << begin_idx << " - " << end_idx << ", " << mid_idx << endl;
            //cout << __LINE__ << endl;
        }
        else if (before_mid_val < mid_val && after_mid_val < mid_val)
        {
            end_idx = mid_idx - 1;
            //cout << "AFt " << begin_idx << " - " << end_idx << ", " << mid_idx << endl;
            //cout << __LINE__ << endl;
        }
    }

    if (found)
    {
    	//cout << mid_idx << endl;
        if ((nums1.size() + nums2.size()) & 0x1)
        {
            return nums1[mid_idx];
        }
        else
        {
            int left_cnt = target_mid - mid_idx;

            if (mid_idx == 0)
            {
                return (double)(nums2[left_cnt - 1] + nums1[mid_idx]) / 2;
            }
            else if (left_cnt == 0)
            {
            	return (double)(nums1[mid_idx - 1] + nums1[mid_idx]) / 2;
            }
            else
            {
                int left_val = nums1[mid_idx - 1] > nums2[left_cnt - 1] ?
                    nums1[mid_idx - 1]: nums2[left_cnt - 1];
                return (double)(left_val + nums1[mid_idx]) / 2;
            }
        }
    }
    return -1000000;
}

int main()
{
	vector<int>	in1 = {5};
	vector<int> in2 = {1, 2, 3, 4, 6};
	double ret = findMedianSortedArraysInN1(in1, in2);
	if (ret == NOT_FOUND)
	{
		ret = findMedianSortedArraysInN1(in2, in1);
	}
	if (ret != NOT_FOUND)
	{
		cout << "Median is " << ret << endl;
	}
	return 0;
}