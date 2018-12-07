/**

Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Example 1:

Input: [1,3,4,2,2]
Output: 2

Example 2:

Input: [3,1,3,4,2]
Output: 3

Note:

    You must not modify the array (assume the array is read only).
    You must use only constant, O(1) extra space.
    Your runtime complexity should be less than O(n2).
    There is only one duplicate number in the array, but it could be repeated more than once.

*/

/**

solution: 
*/

#include<iostream>
#include <vector>

using namespace std;

bool search(std::vector<int> &v, int selected, int idx){
	int left=idx+1, right=v.size()-1;
	while(left<=right){
		if((v[left++]==selected) || (v[right--]==selected))
			return true;
	}
	return false;

}


class Solution {
public:
    int findDuplicate(vector<int>& nums) {
    	for(int idx=0; idx<nums.size()-1; idx++){
    		int selected = nums[idx];
    		if(search(nums, selected, idx))
    			return selected;
    	}    
    }
};



int main(int argc, char const *argv[])
{
	Solution solu;
	std::vector<int> v={3,1,3,4,2};
	cout<<solu.findDuplicate(v)<<endl;
	return 0;
}
