#include <iostream>
#include <vector>

using namespace std;




class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
		vector<int> ans = arr;

		while(ans.size()>k){
			if(x-ans.front()<=ans.back()-x)
				ans.pop_back();
			else
				ans.erase(ans.begin());
		}

		return ans;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	vector<int> arr = {1,2,3,4,5};
	vector<int> ans = solu.findClosestElements(arr, 4,3);

	for(auto item:ans)
		cout<<item<<" ";
	return 0;
}
