
/**
Let's call an array A a mountain if the following properties hold:

A.length >= 3
There exists some 0 < i < A.length - 1 such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... > A[A.length - 1]
Given an array that is definitely a mountain, 
return any i such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... > A[A.length - 1].

Example 1:

Input: [0,1,0]
Output: 1
Example 2:

Input: [0,2,1,0]
Output: 1

*/
class Solution2 {
public:
    int peakIndexInMountainArray(vector<int>& A) {
       for(int idx=0; idx<A.size()-1; idx++){
       		if(A[idx]>A[idx+1])
       			return idx;
       }
    }
};


int main(int argc, char const *argv[])
{
	/*
	int left = 1;
	int right = 202;
	Solution solu;

	vector<int> result = solu.selfDividingNumbers(left, right);
	for(int idx=0; idx<result.size(); idx++)
		cout<<result[idx]<<" ";
	return 0;*/

	Solution2 solu;
	vector<int> v = {0,2,1,0};
	cout<<solu.peakIndexInMountainArray(v)<<endl;
}
