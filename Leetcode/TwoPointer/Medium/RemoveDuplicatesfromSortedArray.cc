#include <iostream>
#include <vector>

using namespace std;



class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
   		int len = 0;

      for(auto item:nums){
        if(len<2 || item>nums[len-2])
          nums[len++] = item;
      }

      return len;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	vector<int> arr = {};//{1,1,1,2,2,3};//{0,0,1,1,1,1,2,3,3};
	cout<<solu.removeDuplicates(arr)<<endl;
	return 0;
}
