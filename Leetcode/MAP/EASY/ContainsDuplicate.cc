/*

Given an array of integers, find if the array contains any duplicates.

Your function should return true if any value appears at least twice in the array,
and it should return false if every element is distinct.

Example 1:

Input: [1,2,3,1]
Output: true
Example 2:

Input: [1,2,3,4]
Output: false
Example 3:

Input: [1,1,1,3,3,4,3,2,4,2]
Output: true

*/



/**
一个哈希表直接走
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
		std::map<int, int> my_map;
		for(int idx=0;idx<nums.size(); idx++){
			if(my_map.find(nums[idx])!=my_map.end()) return true;
			my_map[nums[idx]] = 1;
		}

		return false;

    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	std::vector<int> v={1,1,1,3,3,4,3,2};
	cout<<solu.containsDuplicate(v)<<endl;
	return 0;
}
