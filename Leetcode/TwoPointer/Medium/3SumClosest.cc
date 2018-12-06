
bool compare(int i, int j){return i<j;}

int rounder(std::vector<int> &nums, int target, int selected){
    int left=0,right=nums.size()-1,sum=0;

    while(left<right){
        if(nums[left]==selected) left++;
        if(nums[right]==selected) right--;

        sum=(nums[left]+nums[right]+selected);
        (sum>target) ? right--:left++;
    }

    return sum;
}

int cloestr(std::vector<int> v, int target){
    int gap=9999, cloest = 0;
    for(int idx=0; idx<v.size(); idx++){
        int current_gap = target-v[idx];
        cloest = (current_gap<gap) ? cloest:v[idx];
        gap = (current_gap<gap)?current_gap:gap;
    }

    return cloest;
}


class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        std::vector<int> result;
        sort(nums.begin(), nums.end(), compare);

        for(auto item:nums){
            int tmp_result = rounder(nums, target, item);
            result.push_back(tmp_result);
        }

        int ans = cloestr(result, target);

        return ans;
    }
};
