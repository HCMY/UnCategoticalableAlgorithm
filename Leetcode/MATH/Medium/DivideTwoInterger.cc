
/**
Divide Two Integers
Medium

566

2716

Favorite

Share
Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero.

Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Example 2:

Input: dividend = 7, divisor = -3
Output: -2

/



#include <iostream>

using namespace std;


class Solution {
public:
    int divide(int dividend, int divisor) {
    	long long copy_divisor = abs((long long) divisor);
    	long long copy_dividend = abs((long long) dividend);

        if(copy_dividend<copy_divisor)
            return 0;

		long long count = 0;
		while(copy_dividend>=copy_divisor){
			long long tmp_divisor = copy_divisor;
			long long p =1;
			while(copy_dividend>(tmp_divisor<<1)){
				p<<=1;
				tmp_divisor<<=1;
			}
			count+=p;
			copy_dividend-=tmp_divisor;
		}

		if((divisor<0 && dividend>0)||(dividend<0 && divisor>0))
			count = -count;
		return count > INT_MAX ? INT_MAX : count;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;

    cout<<solu.divide(10,3)<<endl;
	cout<<solu.divide(7,-3)<<endl;
	cout<<solu.divide(-19,8)<<endl;

	return 0;
}
