/*
A string S of lowercase letters is given.
We want to partition this string into as many parts as possible
so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
 */


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include<unordered_map>
#include<algorithm>

using namespace std;



class Solution {
public:
    vector<int> partitionLabels(string S) {
		unordered_map<char,int> last_appear_index_map;
		vector<int> partition;
		int s_length = S.length();
		int end=0;

		for(int idx=0;idx<s_length;idx++)
			last_appear_index_map[S[idx]] = idx;
		for(int start=0; start<s_length;start++){
			end = max(end,last_appear_index_map[S[start]]);

			if(start==end)
				partition.push_back(start+1);
		}
        if(partition.size()<=1)
            return partition;
        else{
            for(int idx=partition.size()-1; idx>0; idx--)
                partition[idx] = partition[idx]-partition[idx-1];

            return partition;
        }

    }
};



int main(int argc, char const *argv[])
{
	Solution solu;
	string S = "caedbdedda";
	vector<int> ans = solu.partitionLabels(S);

	for(auto item:ans)
		cout<<item<<" ";
	return 0;
}
