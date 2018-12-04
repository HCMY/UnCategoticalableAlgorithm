/**
Given a string, determine if it is a palindrome, considering only alphanumeric characters
and ignoring cases.

Note: For the purpose of this problem, we define empty string as valid palindrome.

Example 1:

Input: "A man, a plan, a canal: Panama"
Output: true

Example 2:

Input: "race a car"
Output: false
*/

/**
amanaplanacanalpanama
amanaplanacanalpanama

raceacar
racaecar

*/

#include <iostream>
#include <string>

using namespace std;



class Solution {
public:
    bool isPalindrome(string s) {
        string normal_str = "";
        string abnormal_str = "";
        for(int nor_idx=0, abnor_idx=s.length()-1;
        	nor_idx<s.length(); nor_idx++, abnor_idx--){

        	if((s[nor_idx]>='a' && s[nor_idx]<='z')||
            (s[nor_idx]>='A' && s[nor_idx]<='Z')||
            (s[nor_idx]>='0'&&s[nor_idx]<='9')){
        		char tmp_chr = s[nor_idx];
        		if(tmp_chr>='A' && tmp_chr<='Z')
        			tmp_chr += 32;
        		normal_str += tmp_chr;
        	}

        	if((s[abnor_idx]>='a'&&s[abnor_idx]<='z')||
            (s[abnor_idx]>='A'&&s[abnor_idx]<='Z')||
            (s[abnor_idx]>='0'&&s[abnor_idx]<='9')){
        		char tmp_chr = s[abnor_idx];
        		if(tmp_chr>='A' && tmp_chr<='Z')
        			tmp_chr += 32;
        		abnormal_str += tmp_chr;
        	}
        }

        for(int idx=0; idx<normal_str.length();idx++){
        	if(abnormal_str[idx]!=normal_str[idx])
        		return false;
        }

        return true;

    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	string ss1 = "0P";
	string ss2 = "p";
	cout<<solu.isPalindrome(ss1)<<endl;
	cout<<solu.isPalindrome(ss2)<<endl;
	return 0;
}
