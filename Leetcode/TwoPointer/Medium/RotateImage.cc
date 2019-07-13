#include <iostream>
#include <vector>

using namespace std;

/**
 * 思路：先做矩阵转置，之后再将列兑换 1<->最后一列  2<->倒数第二列
 */


class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
    	int n = matrix[0].size();

        for(int row=0;row<n; row++){
        	for(int col=row; col<n; col++){
        		int tmp = matrix[row][col];
                matrix[row][col] = matrix[col][row];
                matrix[col][row] = tmp;
        	}
        }


        for(int row=0;row<n; row++){
            for(int col=0; col<(n/2); col++){
                int tmp = matrix[row][col];
                matrix[row][col] = matrix[row][n-col-1];
                matrix[row][n-col-1] = tmp;
            }
        }

    }
};



int main(int argc, char const *argv[])
{
	Solution solu;

	vector<vector<int>> mat = {{1,2,3},{4,5,6},{7,8,9}};

	solu.rotate(mat);

	int n =3;
	for(int row=0;row<n; row++){
        for(int col=0; col<n; col++)
        	cout<<mat[row][col]<<" ";
      	cout<<endl;
    }
	return 0;
}
