/**
39. Combination Sum
Medium

1682

48

Favorite

Share
Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

The same repeated number may be chosen from candidates unlimited number of times.

Note:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
  [7],
  [2,2,3]
]
Example 2:

Input: candidates = [2,3,5], target = 8,
A solution set is:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]
Ac
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;



bool backtrack(vector<vector<int>> &matrix, vector<int> &tmp_arr,
				vector<int> &nums, int reminder, int start){

	if(reminder<0){return false;}
	else if(reminder==0){matrix.push_back(tmp_arr);return false;}
	else{
		for(int idx=start;idx<nums.size();idx++){
			bool flag;
			tmp_arr.push_back(nums[idx]);
			flag = backtrack(matrix,tmp_arr,nums,reminder-nums[idx],idx);
			tmp_arr.pop_back();
			if(!flag) break;
		}
		return true;
	}

}

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        std::sort(candidates.begin(),candidates.end());
        candidates.erase(std::unique(candidates.begin(),candidates.end()),
                         candidates.end());

        vector<vector<int>> res;
        vector<int> tmp_arr;
        backtrack(res,tmp_arr,candidates,target,0);

        return res;
    }
};

int main(int argc, char const *argv[])
{
	Solution solu;
	std::vector<int> candidates={2,3,6,7};
	vector<vector<int>> res = solu.combinationSum(candidates,7);

    for(int i=0;i<res.size();i++){
        for(int j=0;j<res[i].size();j++)
            cout<<res[i][j]<<" ";
        cout<<endl;
    }

	return 0;
}
