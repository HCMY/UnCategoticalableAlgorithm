void back_tracking(int &result, vector<int> &tmp, int k,int start){
	if(tmp.size()==k){
	    if((tmp[0]!=0) &&(tmp[k-1]!=tmp[k-2]))
			result++;
		return;
	}

	for(int i=0;i<=9;i++){
		if(i==start) continue;
		tmp.push_back(i);
		back_tracking(result,tmp,k,start+1);
		tmp.pop_back();
	}
}

class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        int total_result = 0;

        for(int i=1;i<=n;i++){
			vector<int> tmp;
			int result = 0;
        	back_tracking(result,tmp,i,0);
        	total_result +=result;
        }

        return total_result+1;
    }
};
