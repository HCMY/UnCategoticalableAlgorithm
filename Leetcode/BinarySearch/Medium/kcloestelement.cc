#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int find_nearst_element(vector<int> arr, int x){
	int min_gap = 9999;
	int target_idx;
	x = abs(x);

	for(int idx=0;idx<arr.size();idx++){
		int gap = x - arr[idx];
		if(gap==0)
			return idx;
		min_gap = min(min_gap,gap);
		if(min_gap==gap)
			target_idx = idx;
	}

	return target_idx;
}

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int target_idx = find_nearst_element(arr,x);
        int left = target_idx;
        int right = target_idx+1;
        vector<int> res;

        int left_gap = 9999;
        int right_gap = 9999;
        x = abs(x);

        while(res.size()!=k){
        	left_gap = abs(x - arr[left]);
        	right_gap = abs(x - arr[right]);

        	if((left_gap<=right_gap) && (left>=0)){
        		res.push_back(arr[left]);
        		left--;
        	}else if(right<arr.size()){
        		res.push_back(arr[right]);
        		right++;
        	}else{
                res.push_back(arr[right]);
        		left--;
        	}
        }

        sort(res.begin(),res.end());
        return res;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	vector<int> arr = {1,2,3,4,5};
	//cout<<find_nearst_element(arr,1)<<endl;
	vector<int> res = solu.findClosestElements(arr,4,3);

	for(auto item:res)
		cout<<item<<" ";
	return 0;
}
