/**
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of O(log n).

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

*/
#include<iostream>
#include<vector>

using namespace std;


int binary_search(std::vector<int> arr, int left, int right,int target){
	while(left<=right){
		int mid = (left+right)/2;
		if(arr[mid]==target)
			return mid;
		else if(target>arr[mid])
			left = mid+1;
		else
			right = mid-1;
	}

	return -1;
}


class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.empty())
            return -1;
        if(nums[0]<nums[nums.size()-1])
        	return binary_search(nums,0,nums.size()-1,target);

        int theta = 0;
        for(int idx=0;idx<nums.size()-1;idx++){
            if(nums[idx]==target)
                return idx;
        	if(nums[idx]>nums[idx+1]){
        		theta = idx;
        		break;
        	}
        }

        int left = theta+1;
        int right = nums.size()-1;
        return binary_search(nums,left,right,target);
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	std::vector<int> v={3,5,1};
	cout<<solu.search(v,3)<<endl;
	return 0;
}
