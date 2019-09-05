"""
S and T are strings composed of lowercase letters. In S, no letter occurs more than once.

S was sorted in some custom order previously. We want to permute the characters of T so that they match the order that S was sorted. More specifically, if x occurs before y in S, then x should occur before y in the returned string.

Return any permutation of T (as a string) that satisfies this property.

Example :
Input: 
S = "cba"
T = "abcd"
Output: "cbad"
Explanation: 
"a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a". 
Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.
"""


class Solution:
	def customSortString(self, S: str, T: str) -> str:
		t_dict = {}
		

		for item in list(T):
			t_dict[item]=1

		for item in list(T):
			t_dict[item]+=1

		res = ""
		
		for item in list(S):
			if item in t_dict:
				for i in range(1,t_dict[item]):
					res += item
				t_dict[item] = 0

		for k,v in t_dict.items():
			if v!=0:
				for i in range(1,v):
					res += k	

		return res


if __name__ == '__main__':
	solu = Solution()
	print(solu.customSortString("cbaf","cbad"))
	print(solu.customSortString("cba","cbad"))
	print(solu.customSortString("cba","abcd"))
	print(solu.customSortString("kqep","pekeqccc"))
