/**
Given an array of integers A sorted in non-decreasing order, return an array of the squares of each number, also in sorted non-decreasing order.



Example 1:

Input: [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Example 2:

Input: [-7,-3,2,3,11]
Output: [4,9,9,49,121]
**/

#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int> &v,int low, int high){
	int pivot = v[low];
	while(low<high){
		while((low<high) && (v[high]>=pivot))
			high--;
		v[low] = v[high];
		while((low<high) &&(v[low]<=pivot))
			low++;
		v[high] = v[low];
	}

	v[low] = pivot;

	return low;
}


void sorter(vector<int> &v, int low,int high){
	if(low<high){
		int pi = partition(v,low,high);
		sorter(v,low,pi-1);
		sorter(v,pi+1,high);
	}
}



class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        for(int idx=0;idx<A.size(); idx++){
        	if(A[idx]<0)
        		A[idx] = -A[idx];
        }

        sorter(A,0,A.size()-1);

        for(int idx=0;idx<A.size();idx++)
        	A[idx] = A[idx]*A[idx];


        return A;
    }


};

int main(int argc, char const *argv[])
{
	Solution solu;
	vector<int> v = {-7,-3,2,3,11};
	solu.sortedSquares(v);
	for(auto item:v)
        cout<<item<<" ";
	return 0;
}
