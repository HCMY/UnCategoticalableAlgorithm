

/**
A self-dividing number is a number that is divisible by every digit it contains.

For example, 128 is a self-dividing number because 128 % 1 == 0, 128 % 2 == 0, and 128 % 8 == 0.

Also, a self-dividing number is not allowed to contain the digit zero.

Given a lower and upper number bound, output a list of every possible self dividing number,
including the bounds if possible.

Example 1:
Input:
left = 1, right = 22
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22]
Note:

The boundaries of each input argument are 1 <= left <= right <= 10000.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//string convertINT2String(){}

bool isSelfDivideNumber(const int original_number){
	if(original_number%10==0)
		return false;

	string str_number = std::to_string(original_number);
	for(int idx=0; idx<str_number.length(); idx++){
		int local_value = str_number[idx]-'0';
		if(local_value==0)
			return false;
		if(original_number%local_value!=0)
			return false;
	}

	return true;
}


class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
  		vector<int> result;
  		for(int idx=left; idx<=right; idx++){
  			if(idx>=1 && idx<10)
  				result.push_back(idx);
  			else if(isSelfDivideNumber(idx))
  				result.push_back(idx);
  			else
  				continue;
    	}

    	return result;
  	}
};

int main(int argc, char const *argv[])
{
	int left = 1;
	int right = 202;
	Solution solu;

	vector<int> result = solu.selfDividingNumbers(left, right);
	for(int idx=0; idx<result.size(); idx++)
		cout<<result[idx]<<" ";
	return 0;
}
