
#include <iostream>
#include <vector>

using namespace std;



void back_tracking(vector<vector<int>> &result, vector<int> &tmp_result,int k,int n,int start){
	if(tmp_result.size()==k){
		result.push_back(tmp_result);
		return;
	}

	for(int idx=start;idx<=n;idx++){
        tmp_result.push_back(idx);
        back_tracking(result,tmp_result,k,n,start+1);
        tmp_result.pop_back();
        start+=1;
		}
}

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
    	vector<int> nums;
    	vector<int> tmp_result;
    	vector<vector<int>> result;
    	vector<bool> visited(n,false);

    	for(int idx=1;idx<=n;idx++)
    		nums.push_back(idx);

    	back_tracking(result,tmp_result,k,n,1);

    	return result;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	vector<vector<int>> result = solu.combine(4,2);
	for(int i=0;i<result.size();i++){
		for(int j=0; j<result[i].size();j++)
			cout<<result[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}
