#include <iostream>
#include<vector>
#include <string>

using namespace std;

void back_tracting(vector<string> &result, int left, int right,string &tmp_result){
	if(left==0&right==0){
		result.push_back(tmp_result);
		return;
	}
	if(left>0){
		tmp_result += '(';
		back_tracting(result,left-1,right,tmp_result);
		tmp_result.pop_back();
	}

	if(right>left){
		tmp_result+=')';
		back_tracting(result,left,right-1,tmp_result);
		tmp_result.pop_back();
	}
}

class Solution {
public:
    vector<string> generateParenthesis(int n) {

    std::vector<string> result;
    if(n==0)return result;

    string tmp_result;
    back_tracting(result,n,n,tmp_result);

    return result;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	std::vector<string> v= solu.generateParenthesis(3);

	for(auto item:v)
		cout<<item<<endl;
	return 0;
}



