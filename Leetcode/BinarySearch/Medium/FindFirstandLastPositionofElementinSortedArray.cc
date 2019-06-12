class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {

      int left = 0;
      int right = nums.size()-1;
      bool left_flag = 1;
      bool right_flag = 1;

      int start = -1;
      int end = -1;

      vector<int> ans;
      while((left_flag||right_flag) &&(left<right))){
        if(left_flag && nums[left++]==target){start=left-1;left--;left_flag=0;}
        if(right_flag && nums[right--]==target){end=right+1;right++;right_flag=0;}
      }

      ans.push_back(start);
      ans.push_back(end);

      return ans;

    }
};

int int main(int argc, char const *argv[]) {
  Solution solu;
  vector<int> arr = {5,7,7,8,8,10};
  vector<int> ans = solu.searchRange(arr,5);
  for(auto item:arr)
    cout<<item<<" ";
  return 0;
}

