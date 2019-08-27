
#include <iostream>
#include <stack>
#include<string>
#include<algorithm>

using namespace std;

string printer(stack<int> s){
    string S = "";
	if(s.empty())
        return "0";

	while(!s.empty()){
        string tmp = to_string(s.top());
        S = tmp+S;
        s.pop();
	}

	return S;
}



class Solution {
public:
    string removeKdigits(string num, int k) {
		stack<int> res_stack;
		int push_count = 0;

		if(k==1 && num.length()==1)
			return "0";

		for(int idx=0;idx<num.length();idx++){
			int push_component = num[idx]-'0';


			if(push_count==k)
				res_stack.push(push_component);


			else if(!res_stack.empty()){
				int top = res_stack.top();
				if(push_component>=top){
					push_count++;
					continue;
				}else{
				    res_stack.pop();
				    push_count++;
				    if(push_component==0 && res_stack.empty())
                        continue;
					res_stack.push(push_component);
				}

			}else{
				res_stack.push(push_component);
			}
		}

		return printer(res_stack);
    }
};





int main(int argc, char const *argv[])
{
	Solution solu;
	string s="112";
	cout<<solu.removeKdigits(s,1)<<endl;
	return 0;
}

/**
class Solution {
public:
    string removeKdigits(string num, int k) {
        string res = "";
        int n = num.size(), keep = n - k;
        for (char c : num) {
            while (k && res.size() && res.back() > c) {
                res.pop_back();
                --k;
            }
            res.push_back(c);
        }
        res.resize(keep);
        while (!res.empty() && res[0] == '0') res.erase(res.begin());
        return res.empty() ? "0" : res;
    }
};
**/
