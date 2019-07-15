#include <iostream>

using namespace std;


double power(double x, int n){
	if(n==1)
		return x;
	else if(n==0)
		return 1;

	double half = power(x, n/2);
	if( n%2 == 0)
		return half*half;
	else
		return half*half*x;

}


class Solution {
public:
    double myPow(double x, int n){
        long N = n;
    	if(N<0){
    		x = 1/x;
    		N = -N;
    	}
    	return power(x,N);

    }
};

int main(int argc, char const *argv[])
{
	Solution solu;
	cout<<solu.myPow(2.00000,10)<<endl;
	return 0;
}
