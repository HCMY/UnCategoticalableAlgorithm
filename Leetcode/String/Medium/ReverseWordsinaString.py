'''
151. Reverse Words in a String
Medium

636

2397

Favorite

Share
Given an input string, reverse the string word by word.

 

Example 1:

Input: "the sky is blue"
Output: "blue is sky the"
Example 2:

Input: "  hello world!  "
Output: "world! hello"
Explanation: Your reversed string should not contain leading or trailing spaces.
Example 3:

Input: "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
 

Note:

A word is defined as a sequence of non-space characters.
Input string may contain leading or trailing spaces. However, your reversed string should not contain leading or trailing spaces.
You need to reduce multiple spaces between two words to a single space in the reversed string.
'''

class Solution:

    def reverseWords(self, s: str) -> str:
        s = s.strip(' ')
        s = s.split(' ')

        s = list(filter(None,s))
        s = s[::-1]
        s = " ".join(s)

        return s



if __name__ == '__main__':
	solu = Solution()
	s= solu.reverseWords("a good   example")
	print(s)