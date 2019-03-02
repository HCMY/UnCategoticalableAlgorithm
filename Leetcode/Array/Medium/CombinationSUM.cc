bool backtrack(vector<vector<int>> matrix, vector<int> tmp_arr,
				vector<int> nums, int reminder, int start){

	if(reminder<0){return false;}
	else if(reminder==0){matrix.push_back(tmp_arr);return false;}
	else{
		for(int idx=start;idx<nums.size();idx++){
			bool flag;
			tmp_arr.push_back(nums[idx]);
			flag = backtrack(matrix,tmp_arr,nums,reminder-nums[idx],idx);
			tmp_arr.clear();
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
