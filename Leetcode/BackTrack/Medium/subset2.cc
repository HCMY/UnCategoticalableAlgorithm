class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) 
    {
        
        vector<vector<int>> result;
        vector<int> temp;
        if(nums.empty())return result;
        sort(nums.begin(),nums.end());
        
        result.push_back(temp);//存入空集
        
        for(int i=1;i<=nums.size();i++)//深度搜索，深度分别为[1,N]
        {
            DFS(nums, result, temp, i,0);
        }
        return result;
        
    }
private:
    void DFS(vector<int>& nums,vector<vector<int>>& result,vector<int>& temp,int deepth,int start)
    {
        if(temp.size()==deepth)//搜索深度到达，存储可行解，返回上一层继续搜索
        {
            result.push_back(temp);
            return;
        }
        else
        {
            for(int i=start;i<nums.size();i++)
            {
                if(i!=start&&nums[i]==nums[i-1])continue;//剪枝去重复，对于搜索的任何一层决不能在本层出现重复
                
                temp.push_back(nums[i]);//存储到可行解路径中
                DFS(nums, result, temp, deepth,i+1);//搜索下一层，注意其搜索起点i+1，避免数据重复使用
                temp.pop_back();//某一层搜索结束顶层出栈，或者某一层数据搜索到可行解，继续该层下一次搜索
            }
        }
    }
};
