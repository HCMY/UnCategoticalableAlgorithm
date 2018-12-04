
/**
Given n non-negative integers a1, a2, ..., an , 
where each represents a point at coordinate (i, ai). 
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
Find two lines, which together with x-axis forms a container,
 such that the container contains the most water.
*/

/**
Example:

Input: [1,8,6,2,5,4,8,3,7]
Output: 49

*/

/**
solution:set double pointer,left and right.
one search from left to right, another search from right to left one shot,
if left attitude is more than right, then right-1
*/

#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size()-1;
        int attitude = 0;
        int max_area = 0;

        while(left<right){
            attitude = (height[right]>height[left]) ? height[left]:height[right];
            int tmp_area = attitude*(right - left);
            max_area = (max_area<tmp_area) ? tmp_area:max_area;
            (height[right]>height[left])? left++ : right--;
        }        

        return max_area;
    }
};


int main(int argc, char const *argv[])
{
    Solution solu;
    std::vector<int> v={1,8,6,2,5,4,8,3,7};

    cout<<solu.maxArea(v)<<endl;
    return 0;
}
