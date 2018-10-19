#include <iostream>

using namespace std;

/**
本质上是异或运算，先按位与，取出两数对应位置的二进制，再进行异或
*/


class Solution {
public:
    int hammingDistance(int x, int y) {
        int res = 0;
        for (int i = 0; i < 32; ++i) {
            if ((x & (1 << i)) ^ (y & (1 << i))) {
                ++res;
            }
        }
        return res;
    }
};


int main(int argc, char const *argv[])
{
    /*
    int x2=4;
    int m = 1<<1;
    cout<<m<<endl;
    m  = 1<<2;
    cout<<m<<endl;


    cout<<(x2&2)<<endl;

    cout<<(x2&4)<<endl;
	*/

	int x1=1,x2=4;
	Solution solu;
	cout<<solu.hammingDistance(x1,x2)<<endl;
	return 0;

}
