
/*
Given a string s and a string t, check if s is subsequence of t.

You may assume that there is only lower case English letters in both s and t. t is potentially a very long (length ~= 500,000) string, and s is a short string (<=100).

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
s = "abc", t = "ahbgdc"

Return true.

Example 2:
s = "axc", t = "ahbgdc"

Return false.

Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one by one to see if T has its subsequence. In this scenario, how would you change your code?
*/

#include <iostream>
#include <string>
#include <map>

using namespace std;


class Solution {
public:
    bool isSubsequence(string s, string t) {
        if(s.length()<=0)
            return true;
        if(t.length()<=0)
            return false;

        if(s.length()<t.length()){
            string tmp = s;
            s = t;
            t = tmp;
        }

        string cut_str = "";
        int t_idx = 0;
        for(int idx=0;idx<s.length();idx++){
            if(s[idx]==t[t_idx]){
                cut_str += s[idx];
                t_idx++;
            }
        }

        for(int idx=0;idx<t.length();idx++){
            if(t[idx]!=cut_str[idx])
                return false;
        }

        return true;
    }
};

int main(int argc, char const *argv[])
{
	Solution solu;
	string s = "";
	string t= "ahbgdc";

	cout<<solu.isSubsequence(s,t)<<endl;
	return 0;
}
