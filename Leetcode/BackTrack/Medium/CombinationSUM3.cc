int sum(vector<int> v){
    int sum=0;
    for(auto item:v)
        sum+=item;
    return sum;
}

void back_tracking(vector<vector<int>> &result, vector<int> tmp_result, int n, int k,int start){
    if(tmp_result.size()==k){
        if(sum(tmp_result)==n)
            result.push_back(tmp_result);
        return;
    }


    for(int idx=start; idx<=9;idx++){
        tmp_result.push_back(idx);
        back_tracking(result,tmp_result,n,k,start+1);
        tmp_result.pop_back();
        start+=1;
    }
}

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> tmp_result;
        back_tracking(result,tmp_result,n,k,1);

        return result;
    }
};

