/*

Given an integer n, return the number of trailing zeroes in n!.

Example 1:

Input: 3
Output: 0
Explanation: 3! = 6, no trailing zero.
Example 2:

Input: 5
Output: 1
Explanation: 5! = 120, one trailing zero.
*/


/**
质因数分解：
4! = 24=2*2*2*3--->0
5! = 120=2*2**2*3*5-->1
0由2和5产生，而2的个数必定多于5的个数
所以

只需要计算5的个数就行

*/
#include <iostream>

using namespace std;




class Solution {
public:
    int trailingZeroes(int n) {
		int count_zero = 0;

		while(n){
			count_zero+=n/5;
			n/=5;
		}

		return count_zero;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	cout<<solu.trailingZeroes(40)<<endl;
	//cout<<solu.trailingZeroes(3)<<endl;
	//cout<<solu.trailingZeroes(5)<<endl;

	return 0;
}
