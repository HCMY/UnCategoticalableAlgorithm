
/**
We define a harmonious array is an array where the difference between its maximum value
and its minimum value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence
among all its possible subsequences.

Example 1:
Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
Note: The length of the input array will not exceed 20,000.

*/

#include <iostream>
#include <vector>
#include<map>
#include <algorithm>

using namespace std;

/**
solution: 建立一个哈希表，存储每个元素出现的次数
之后找到相差值为1的2个数直接相加
*/

bool myfunction (int i,int j) { return (i<j); }

class Solution {
public:
    int findLHS(vector<int>& nums) {
        if (nums.empty()) return 0;
        int res = 0;
        map<int, int> m;
        for (int num : nums) ++m[num];
        for (auto it = next(m.begin()); it != m.end(); ++it) {
            auto pre = prev(it);
            if (it->first == pre->first + 1) {
                res = max(res, it->second + pre->second);
            }
        }
        return res;
    }
};



int main(int argc, char const *argv[])
{
	Solution solu;
	std::vector<int> v={1,3,2,2,5,2,3,7};
	cout<<solu.findLHS(v)<<endl;
	return 0;
}
