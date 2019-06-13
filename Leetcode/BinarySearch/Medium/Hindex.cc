#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int hIndex(vector<int>& citations) {
		if(citations.empty())
			return 0;

		int length = citations.size();
		int max_ans = -1;

		for(int idx=0;idx<length-1;idx++){
			int h = citations[idx];
			if((length-idx)>=h && (length-h)<=h){
				max_ans = max_ans<h ? h:max_ans;
			}
		}

		return max_ans;
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	vector<int > arr={3,0,6,1,5};
	cout<<solu.hIndex(arr)<<endl;
	return 0;
}
