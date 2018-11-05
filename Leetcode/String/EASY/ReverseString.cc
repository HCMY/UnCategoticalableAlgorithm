#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


/**
Write a function that takes a string as input and returns the string reversed.

Example 1:

Input: "hello"
Output: "olleh"
Example 2:

Input: "A man, a plan, a canal: Panama"
Output: "amanaP :lanac a ,nalp a ,nam A"
*/


/**
思路：设置左右指针，依此交换两个指针的位置
*/
class Solution {

public:
    string reverseString(string s) {
     int left = 0;
     int right = s.length()-1;
     char tmp;

     while(left<=right){
     	swap(s[left], s[right]);
     	left++;
     	right--;
     }

     return s;

    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	string s1 = "hello";
	string s2 = "healoc";
	string s3 = "A man, a plan, a canal: Panama";
	cout<<solu.reverseString(s1)<<endl;
	cout<<solu.reverseString(s2)<<endl;
	cout<<solu.reverseString(s3)<<endl;
	return 0;
}
