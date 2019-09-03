/**
Given an array nums of n integers and an integer target, find three integers in nums such that the sum is closest to target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

Example:

Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

#include <vector>
#include <cstdlib>
#include<iostream>

using namespace std;

int partition(vector<int> &v, int low,int high){
	int pivot = v[low];
	while(low<high){
		while((low<high) && (v[high]>=pivot))
			high--;
		v[low] = v[high];

		while((low<high) && (v[low]<=pivot))
            low++;
		v[high] = v[low];
	}v[low] = pivot;

	return low;
}

void sotter(vector<int> &v, int low,int high){
	if(low<high){
		int pi = partition(v,low,high);
		sotter(v,low,pi-1);
		sotter(v,pi+1,high);
	}
}


class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
		int distance=99999;
		int tmp_distance;
		int sum = 0;
		if(nums.size()<3)
            return 0;

        sotter(nums,0,nums.size()-1);
        //for(auto item:nums)
         //   cout<<item<<" ";

        for(int i=0;i<nums.size()-2; i++){
        	int left = i+1;
        	int right = nums.size()-1;
        	while(left<right){
        		int tmp = nums[i]+nums[left]+nums[right];
        		tmp_distance = abs(target - tmp);
        		if(tmp_distance<distance){
        			distance = tmp_distance;
        			sum = tmp;
        		}
        		if(tmp<target) left++;
        		else right--;
        	}
        }

		return sum;
    }
};



int main(int argc, char const *argv[])
{
	Solution solu;
	vector<int> v = {-1, 2, 1, -4};
	cout<<solu.threeSumClosest(v,1)<<endl;
	return 0;
}
