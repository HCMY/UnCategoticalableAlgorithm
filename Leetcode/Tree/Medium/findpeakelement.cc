/*
A peak element is an element that is greater than its neighbors.

Given an input array nums, where nums[i] ≠ nums[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that nums[-1] = nums[n] = -∞.

Example 1:

Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.
Example 2:

Input: nums = [1,2,1,3,5,6,4]
Output: 1 or 5 
Explanation: Your function can return either index number 1 where the peak element is 2, 
             or index number 5 where the peak element is 6.
N
/



#include <iostream>
#include <vector>

using namespace std;


typedef struct Node{
	int key;
	struct Node *left,*right;
}Node;


Node *new_node(int key){
	Node *tmp_node = (Node *)malloc(sizeof(Node));
	tmp_node->key = key;
	tmp_node->left=tmp_node->right=NULL;

	return tmp_node;
}

Node *insert(Node *root, int key){
	if(root==NULL) return new_node(key);
	if(key<root->key)
		root->left = insert(root->left,key);
	else
		root->right = insert(root->left, key);

	return root;
}

int find_peak(Node *root){
    if(root!=NULL){
        if(root->left!=NULL && root->right!=NULL)
            return root->key;
        find_peak(root->left);
        find_peak(root->right);
    }

    //return 0;
}

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        nums.insert(nums.begin(), INT_MIN);
        nums.push_back(INT_MIN);
        for (int i = 1; i < (int)nums.size() - 1; ++i) {
            if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) return i - 1;
        }
        return -1;
    }
};



class Solution2 {
public:
    int findPeakElement(vector<int>& nums) {
		if(nums.size()==0)
            return 0;

		Node *root = NULL;
		root = insert(root,nums[0]);
		for(int idx=1;idx<nums.size();idx++)
			insert(root,nums[idx]);

        int peak = find_peak(root);
        cout<<"peak="<<peak<<endl;
        for(int idx=0; idx<nums.size();idx++){
            if(nums[idx]==peak)
                return idx;
        }
    }
};


int main()
{
    Solution solu;
    vector<int> v = {1,2,3,1};
    cout<<solu.findPeakElement(v)<<endl;
    return 0;
}
