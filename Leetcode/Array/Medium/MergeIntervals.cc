#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

/**
Example 1:

Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:

Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
)/


/**
 * Definition for an interval.
 */
 struct Interval {
      int start;
      int end;
      Interval() : start(0), end(0) {}
      Interval(int s, int e) : start(s), end(e) {}
 };

bool cmp(const Interval &a, const Interval &b){
	return a.start<b.start;
}

class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> res;
        if(intervals.size()==0)
            return res;
        //理解的太复杂反而会出错
        //扫描过去就行了
        sort(intervals.begin(), intervals.end(), cmp);
        int intervals_size = intervals.size();

        Interval this_one = intervals[0];
        Interval next;
        for(int idx=1; idx<intervals_size;idx++){
        	next = intervals[idx];
        	if(this_one.end<next.start){
        		res.push_back(this_one);
        		this_one = next;
        	}else{
        		this_one.end = next.end>this_one.end ? next.end:this_one.end;
        	}
        }


        res.push_back(this_one);

        return res;
    }
};


int main(int argc, char const *argv[])
{
	vector<Interval> arr;

	for(int i=0; i<4;i++){
		Interval tmp;
		cin>>tmp.start;
		cin>>tmp.end;
		arr.push_back(tmp);
	}

	Solution solu;
	vector<Interval> res = solu.merge(arr);
	for(auto i:res){
		cout<<'['<<i.start<<','<<i.end<<']'<<endl;
	}
	return 0;
}
