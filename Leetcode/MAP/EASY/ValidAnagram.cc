/*
Given two strings s and t , write a function to determine if t is an anagram of s.

Example 1:

Input: s = "anagram", t = "nagaram"
Output: true
Example 2:

Input: s = "rat", t = "car"
Output: false
*/

#include<iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


/**

思路：看对应的字符数量是否相同就可以了
*/

class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.length()!=t.length())
            return false;

        std::map<char, int> s_map;
        std::map<char, int> t_map;

        for(char word:s)
            s_map[word]++;
        for(char word:t)
            t_map[word]++;

        std::vector<char> unique_words;
        for(std::map<char, int>::iterator it=s_map.begin();it!=s_map.end(); it++)
            unique_words.push_back(it->first);

        for(char word:unique_words){
            if(s_map[word]!=t_map[word])
                return false;
        }

        return true;
    }
};


int main(int argc, char const *argv[])
{
    Solution solu;
    string s = "rat";
    string t = "car";
    cout<<solu.isAnagram(s, t)<<endl;
    return 0;
}
