#include <iostream>
#include <vector>

using namespace std;


/**
一开始的思路如注释掉的代码，
新的思路是以行为基点，每次只是往下比较一个，直到全部比较完为止

*/

class Solution {
public:

	/** here is the error code, dum idiot....*/

    /*bool isToeplitzMatrix(vector<vector<int>>& matrix) {
		int rows = matrix.size();
		int cols = matrix[0].size();
        cout<<rows<<" "<<cols<<endl;
		if(rows<=2||cols<=2)
            return false;
		for(int round=0; round<cols-2; round++){
			for(int init_rows=0, init_cols=round;
			init_rows<=rows-1, init_cols<=cols-1;
			init_rows++, init_cols++){
				if(matrix[init_rows][init_cols]!=matrix[init_rows+1][init_cols+1])
					return false;
			}
		}
		return true;
    }*/


    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        for(int i=0;i<matrix.size()-1;i++) {
            for(int j=0;j<matrix[0].size()-1;j++) {
                if(matrix[i][j] != matrix[i+1][j+1]) {
                    return false;
                }
            }
        }
        return true;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	vector<vector<int>> v={{53,64,90,98,34},{91,53,64,90,98},{17,91,53,64,90}};

	cout<<solu.isToeplitzMatrix(v)<<endl;
	return 0;
}

