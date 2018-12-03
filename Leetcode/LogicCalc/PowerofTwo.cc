/**
Given an integer, write a function to determine if it is a power of two.

Example 1:

Input: 1
Output: true
Explanation: 2^0 = 1
Example 2:

Input: 16
Output: true
Explanation: 2^4 = 16
Example 3:

Input: 218
Output: false

*/


/*
1     2       4         8         16 　　....

1    10       100        1000     10000　....
按位与，2的次方数都有以上特点，最后只要统计1的个数就ok
1的数量应该为1

*/

#include <iostream>

using namespace std;

class Solution {
public:
    bool isPowerOfTwo(int n) {
        int cnt = 0;
        while (n > 0) {
            cnt += (n & 1);//1000 & 0001
            n >>= 1;
        }
        return cnt == 1;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	solu.isPowerOfTwo(8);
	return 0;
}
