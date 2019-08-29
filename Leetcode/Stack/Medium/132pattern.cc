/**
Given a sequence of n integers a1, a2, ..., an, a 132 pattern is a subsequence ai, aj, ak such that i < j < k and ai < ak < aj. Design an algorithm that takes a list of n numbers as input and checks whether there is a 132 pattern in the list.

Note: n will be less than 15,000.

Example 1:
Input: [1, 2, 3, 4]

Output: False

Explanation: There is no 132 pattern in the sequence.
Example 2:
Input: [3, 1, 4, 2]

Output: True

Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
Example 3:
Input: [-1, 3, 2, 0]

Output: True

Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].
*/

#include <iostream>
#include <stack>
#include <vector>

using namespace std;
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int help = -100000;
        stack<int> my_stack;
        for (auto item:nums) {
            if (item < help) return true;
            while (!my_stack.empty() && item < my_stack.top()) {
                help = my_stack.top(); 
                my_stack.pop();
            }
            my_stack.push(item);
        }
        return false;
    }
};


int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}