#include <iostream>
#include <vector>
#include <map>

using namespace std;


class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
  		std::map<int, int> left_mat;
  		for(int i=0; i<A.size(); i++)
  			for(int j=0; j<B.size(); j++)
  			 left_mat[A[i]+B[j]]++;

  		int res = 0;
  		for(int i=0;i<C.size();i++){
  			for(int j=0; j<D.size();j++){
  				int target = (-1)*(C[i]+D[j]);
  				res += left_mat[target];
  			}
  		}

  		return res;      
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	std::vector<int> A={1,2};
	std::vector<int> B={2,-1};
	std::vector<int> C={-1,2};
	std::vector<int> D={0,2};
	
	cout<<solu.fourSumCount(A,B,C,D)<<endl;
	return 0;
}
