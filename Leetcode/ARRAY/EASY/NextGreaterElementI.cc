/**
You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2. Find all the next greater numbers for nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, output -1 for this number.

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
    For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
    For number 1 in the first array, the next greater number for it in the second array is 3.
    For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
    For number 2 in the first array, the next greater number for it in the second array is 3.
    For number 4 in the first array, there is no next greater number for it in the second array, so output -1.

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int find(const int number, const std::vector<int> v){
    int stable_idx = 0;
    for(int idx=0; idx<v.size();idx++){
        if(v[idx]==number)
            stable_idx = idx;
    }

    for(int idx=stable_idx; idx<v.size(); idx++){
        if(v[idx]>number)
            return v[idx];
    }

    return -1;
}


class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        std::vector<int> result;
        for(int idx=0; idx<findNums.size(); idx++){
            int flag = find(findNums[idx], nums);
            result.push_back(flag);
        }

        return result;
    }
};

int main(int argc, char const *argv[])
{
    Solution solu;
    std::vector<int> findNums={4,1,2};
    std::vector<int> nums={1,3,4,2};
    vector<int> result = solu.nextGreaterElement(findNums, nums);
    for(int idx=0; idx<result.size(); idx++)
        cout<<result[idx]<<" ";
    cout<<endl;
    return 0;
}

