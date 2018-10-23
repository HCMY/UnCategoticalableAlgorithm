#include <iostream>
#include <string>
#include <vector>
#include <map>


/**
International Morse Code defines a standard encoding where each letter is mapped to a series
of dots and dashes, as follows: "a" maps to ".-", "b" maps to "-...", "c" maps to "-.-.", and so on.

For convenience, the full table for the 26 letters of the English alphabet is given below:

[".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--",
"-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]

Now, given a list of words, each word can be written as a concatenation of the
Morse code of each letter. For example, "cab" can be written as "-.-.-....-",
(which is the concatenation "-.-." + "-..." + ".-"). We'll call such a concatenation,
the transformation of a word.

Return the number of different transformations among all words we have.

Example:
Input: words = ["gin", "zen", "gig", "msg"]
Output: 2
Explanation:
The transformation of each word is:
"gin" -> "--...-."
"zen" -> "--...-."
"gig" -> "--...--."
"msg" -> "--...--."

There are 2 different transformations, "--...-." and "--...--.".

*/




using namespace std;

const vector<string> morse_vec = {".-","-...","-.-.","-..",".","..-.",
							"--.","....","..",".---","-.-",
							".-..","--","-.","---",".--.",
							"--.-",".-.","...","-","..-",
							"...-",".--","-..-","-.--",
							"--.."};

/**
主要思路还是ASIC||得使用，在对26个字母进行编码得时候/
*/
const map<char, string> mapper(){
	map<char, string> my_map;
	for(int asc_start=97, idx=0; asc_start<=122; asc_start++,idx++)
		my_map[asc_start] = morse_vec[idx];

	return my_map;
}

map<char, string> MORSE_MAP = mapper();
bool compare(const string target_str, const vector<string> &result_vec){
	for(int idx=0; idx<result_vec.size(); idx++){
		if(target_str.compare(result_vec[idx])==0)
			return false;
	}

	return true;
}

const string convert2MorseCode(string convert_str){
	string encoded_str = "";
	for(int idx=0; idx<convert_str.length(); idx++){
		char tmp_char = convert_str[idx];
		if(tmp_char>='A' && tmp_char<='Z')
			tmp_char += 32;
		encoded_str += MORSE_MAP[tmp_char];
	}

	return encoded_str;
}


class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
    	if(words.size()<1)
    		return 0;

        vector<string> result_vec;

        for(int idx=0; idx<words.size(); idx++){
        	string encoded_str = convert2MorseCode(words[idx]);
        	if(compare(encoded_str, result_vec))
        		result_vec.push_back(encoded_str);
        }

        return result_vec.size();
    }
};


int main(int argc, char const *argv[])
{
	Solution solu;
	vector<string> words = {"gin", "zen", "gig", "msg"};
	cout<<solu.uniqueMorseRepresentations(words)<<endl;
	return 0;
}
