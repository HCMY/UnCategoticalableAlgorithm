#include <iostream>

#include <vector>

using namespace std;


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	vector<int> arr ={10,9,2,5,3,4};//{-2,-1};//{10,9,2,5,3,7,101,18};
	cout<<solu.lengthOfLIS(arr)<<endl;
	return 0;
}
