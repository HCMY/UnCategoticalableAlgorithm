/*
Find the minimum length word from a given dictionary words, which has all the letters
from the string licensePlate.
Such a word is said to complete the given string licensePlate

Here, for letters we ignore case. For example, "P" on the licensePlate still matches "p" on the word.

It is guaranteed an answer exists. If there are multiple answers,
return the one that occurs first in the array.

The license plate might have the same letter occurring multiple times.
For example, given a licensePlate of "PP", the word "pair" does not complete the licensePlate,
but the word "supper" does.

Example 1:
Input: licensePlate = "1s3 PSt", words = ["step", "steps", "stripe", "stepple"]
Output: "steps"
Explanation: The smallest length word that contains the letters "S", "P", "S", and "T".
Note that the answer is not "step", because the letter "s" must occur in the word twice.
Also note that we ignored case for the purposes of comparing whether a letter exists in the word.
Example 2:
Input: licensePlate = "1s3 456", words = ["looks", "pest", "stew", "show"]
Output: "pest"
Explanation: There are 3 smallest length words that contains the letters "s".
We return the one that occurred first.
*/

#include<iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


bool isMatched(map<char, int> &std_map,  map<char, int> &current_map){
    std::vector<char> keys;
    for(map<char, int>::iterator it=std_map.begin(); it!=std_map.end();it++)
        keys.push_back(it->first);

    for(int idx=0; idx<keys.size(); idx++){
        char this_key = keys[idx];
        if(std_map[this_key]>current_map[this_key])
            return false;
    }

    return true;
}


map<char, int> generateMapFromString(const string str){
    map<char, int> my_map;

    for(int idx=0; idx<str.length(); idx++){
        if((str[idx]>='a' && str[idx]<='z')||
            (str[idx]>='A' &&str[idx]<='Z')){
            char tmp_chr = str[idx];
            if(str[idx]>='A' && str[idx]<='Z')
                tmp_chr += 32;
            my_map[tmp_chr]++;
        }
    }

    return my_map;
}

bool sorter (const string &str_1,const string &str_2){ return (str_1.length() < str_2.length()); }


class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        //create standard map
        sort(words.begin(), words.end(), sorter);
        map<char, int> std_map = generateMapFromString(licensePlate);

        for(int idx=0; idx<words.size(); idx++){
            std::map<char, int> current_map=generateMapFromString(words[idx]);
            if(isMatched(std_map, current_map))
                return words[idx];
        }

        return "";
    }
};


int main(int argc, char const *argv[])
{
    Solution solu;
    string licensePlate = "GrC8950";

    std::vector<string> v = {"measure","other","every","base","according","level","meeting","none","marriage","rest"};

    cout<<solu.shortestCompletingWord(licensePlate, v)<<endl;
    return 0;
}

