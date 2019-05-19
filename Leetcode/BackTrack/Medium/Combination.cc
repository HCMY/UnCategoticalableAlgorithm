
#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> cur;
        tracking(res,cur,n,k);
        return res;
    }
    void tracking(vector<vector<int>> &res,vector<int> &cur,int n,int k){
        if(k == 0){
            res.push_back(cur);
        }
        else{
            for(int i=n;i>0;i--){
                cur.push_back(i);
                tracking(res,cur,i-1,k-1);
                cur.pop_back();
            }
        }

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
