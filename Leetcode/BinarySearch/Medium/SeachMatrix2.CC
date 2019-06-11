#include <iostream>
#include <vector>

using namespace std;



class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0||matrix[0].empty())
    		    return false;
        
        int row = 0;
        int col = matrix[0].size()-1;
        
        while(row<matrix.size() && col>=0){
          	if(matrix[row][col]==target)
          		return true;
          	else if(matrix[row][col]<target)
          		row++;
          	else if(matrix[row][col]>target)
          		col--;
          }

          return false;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;

	vector<vector<int>> mat = {{1,4,7,11,15},
								{2,5,8,12,19},
								{3,6,9,16,22},
								{10,13,14,17,24},
								{18,21,23,26,30}};
vector<vector<int>> mat2 = {{-1},{-1}};
	cout<<solu.searchMatrix(mat2,-2)<<endl;
	return 0;
}
