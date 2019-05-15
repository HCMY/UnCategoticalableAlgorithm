#include <iostream>
#include <vector>

using namespace std;



void back_tracking(vector<vector<int>> &result, vector<int>& nums,
					vector<int> &tmp_result, vector<bool> &visited){

	if(tmp_result.size()==nums.size()){
		result.push_back(tmp_result);
		return;
	}

	for(int idx=0; idx<nums.size(); idx++){
		if(!visited[idx]){
			visited[idx] = true;
			tmp_result.push_back(nums[idx]);
			back_tracking(result, nums, tmp_result, visited);
			visited[idx] = false;
			tmp_result.pop_back();
		}
	}
}


class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> visited(nums.size(),false);
        vector<int> tmp_result;
        vector<vector<int>> result;
        back_tracking(result, nums, tmp_result, visited);

        return result;
    }
};




int main(int argc, char const *argv[])
{
	Solution solu;
	vector<int> nums={1,2,3};
	vector<vector<int>> result = solu.permute(nums);

	for(int i=0;i<result.size();i++){
		for(int j=0; j<result[i].size();j++)
			cout<<result[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}
