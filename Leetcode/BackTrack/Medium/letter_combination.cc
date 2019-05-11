#include <iostream>
#include <string>
#include <vector>

using namespace std;


void back_tracking(std::vector<string> &result, string &digits,
					int index, string &tmp_result,
					std::vector<string> &phone_number){

	if(index==digits.length()){
		result.push_back(tmp_result);
		return;
	}

	for(int i=0; i<phone_number[digits[index]-'0'].length(); i++){
		tmp_result += phone_number[digits[index]-'0'][i];
		back_tracking(result,digits,index+1,tmp_result,phone_number);
		tmp_result.pop_back();
	}
}


class Solution {
public:
    vector<string> letterCombinations(string digits) {
    	std::vector<string> result;
    	if(digits.size()==0)
    		return result;
    	//define letters
    	std::vector<string> phone_number;
    	phone_number.push_back("");
    	phone_number.push_back("");//cause 0 and 1 have not any letters
    	phone_number.push_back("abc");
    	phone_number.push_back("def");
    	phone_number.push_back("ghi");
    	phone_number.push_back("jkl");
    	phone_number.push_back("mno");
    	phone_number.push_back("pqrs");
    	phone_number.push_back("tuv");
    	phone_number.push_back("wxyz");

    	

    	string tmp_result = "";
    	back_tracking(result,digits,0,tmp_result,phone_number);

    	return result;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	string digits = "23";
	std::vector<string> result = solu.letterCombinations(digits);

	for(auto item:result)
		cout<<item<<"--";
	cout<<endl;
	return 0;
}



