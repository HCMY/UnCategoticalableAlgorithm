
#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;


int sum(vector<int> tmp_result){
	int sum = 0;
	for(auto item:tmp_result)
		sum += item;
	return sum;
}


void back_tracking(vector<vector<int>> &result, vector<int> &tmp_result, vector<int> &nums,
					int target,int start){
	if(tmp_result.size()==4){
		if(sum(tmp_result)==target)
			result.push_back(tmp_result);
		return;
	}

	for(int i=start;i<nums.size();i++){
		tmp_result.push_back(nums[i]);
		back_tracking(result,tmp_result,nums,target,start+1);
		tmp_result.pop_back();
		start+=1;
	}
}


void sort_it(vector<vector<int>> &c){
    for(auto item:c)
        sort(item.begin(),item.end());
}

vector<vector<int>> drop_duplicates(vector<vector<int>> myVec){
	//myVec.erase(std::unique(myVec.begin(), myVec.end()), myVec.end());
	vector<vector<int>> result_;
	for(int i=0;i<myVec.size()-1;i++){
		if((myVec[i][0]==myVec[i+1][0])&&(myVec[i][1]==myVec[i+1][1])&&(myVec[i][2]==myVec[i+1][2])&&(myVec[i][3]==myVec[i+1][3])){
            continue;
        }
        result_.push_back(myVec[i]);
	}
	result_.push_back(myVec[myVec.size()-1]);
	return result_;
}

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        vector<int> tmp_result;
        back_tracking(result,tmp_result,nums,target,0);
        sort_it(result);
        vector<vector<int>> result2;
        result2 = drop_duplicates(result);
        return result2;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	vector<int> nums={-5,5,4,-3,0,0,4,-2};
	vector<vector<int>> result = solu.fourSum(nums,4);

    for(int i=0;i<result.size();i++){
		for(int j=0;j<result[i].size();j++)
			cout<<result[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}
