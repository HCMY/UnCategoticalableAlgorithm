#include <iostream>
#include <vector>
#include <stack>

using namespace std;


class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> ans(T.size(),0);
        stack<int> loc_stack;

        for(int idx=0; idx<T.size();idx++){
        	while(!loc_stack.empty() && T[idx]>=T[loc_stack.top()]){
        		int top = loc_stack.top();
        		ans[top] = idx-top;
        		loc_stack.pop();
        	}
        	loc_stack.push(idx);
        }

        return ans;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;

	vector<int> T = {73, 74, 75, 71, 69, 72, 76, 73};
	vector<int> ans = solu.dailyTemperatures(T);

	for(auto item:ans)
		cout<<item<<" ";
	return 0;
}
