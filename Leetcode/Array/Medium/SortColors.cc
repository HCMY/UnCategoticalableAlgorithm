/*
Given an array with n objects colored red, white or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note: You are not suppose to use the library's sort function for this problem.

Example:

Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Follow up:

A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.
Could you come up with a one-pass algorithm using only constant space?
*/

///插入排序就可以了，时间复杂度O(n^2),空间O(1)
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        for(int i=1;i<nums.size();i++){
        	int key = nums[i];
        	int j = i-1;

        	while(j>-1 && nums[j]>key){
        		nums[j+1] = nums[j];
        		j--;
        	}
        	nums[j+1] = key;
        }

    }
};


int main(int argc, char const *argv[])
{
	Solution solu;

	int vec[] = {2,0,2,1,1,0};
	vector<int> arr(vec,vec+6);
	solu.sortColors(arr);
	for(auto item:arr)
		cout<<item<<" ";
	cout<<endl;
	return 0;
}
