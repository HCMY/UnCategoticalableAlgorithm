/*
Given a set of distinct integers, S, return all possible subsets.

Note:

Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.


For example,
If S = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/

#include <iostream>
#include<vector>
#include <algorithm>

using namespace std;


void backtrack(vector<vector<int>> &result, vector<int> &tmp,vector<int> &s, int start){
	result.push_back(tmp);
	for(int i=start;i<s.size();i++){
		tmp.push_back(s[i]);
		backtrack(result,tmp,s,i+1);
		tmp.pop_back();
	}
}

class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        vector<vector<int> > res;
        vector<int> tmp;
        sort(S.begin(), S.end());
        backtrack(res,tmp,S,0);
        return res;
    }
};


int main(int argc, char const *argv[]){
	Solution solu;
	std::vector<int> v={1,2,3};
	vector<vector<int>> result  = solu.subsets(v);
	for(int idx=0;idx<result.size();idx++){
		for(auto item:result[idx])
			cout<<item<<endl;
		cout<<endl;
	}
	return 0;
}
