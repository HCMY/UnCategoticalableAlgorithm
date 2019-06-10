
#include <iostream>
#include <vector>

using namespace std;


bool bi_search(vector<int> arr, int target){
	int left = 0;
	int right = arr.size()-1;

	while(left<=right){
		int mid = (left+right)/2;
		if(arr[mid]==target) return true;
		else if(arr[mid]>target)
			right = mid-1;
		else
			left = mid+1;
	}

	return false;

}


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {

    	if(matrix.size()==0||matrix[0].empty())
    		return false;
        int row = matrix.size();
        int col = matrix[0].size();

        for(int i=0;i<row;i++){
            if(target==matrix[i][col-1])
                return 1;
        	if(target<matrix[i][col-1])
        		return bi_search(matrix[i],target);
        }

       return false;
    }
};

int main(int argc, char const *argv[])
{
	Solution solu;
	vector<vector<int>> mat = {{1,3,5}};

	cout<<solu.searchMatrix(mat,5)<<endl;

	return 0;
}
