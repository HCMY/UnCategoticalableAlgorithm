/**
可以按照如下方法确定某人的H指数：1、将其发表的所有SCI论文按被引次数从高到低排序；
2、从前往后查找排序后的列表，直到某篇论文的序号大于该论文被引次数。所得序号减一即为H指数
*/

#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end(), greater<int>());
        for (int i = 0; i < citations.size(); ++i) {
            if (i >= citations[i]) return i;
        }
        return citations.size();
    }
};

int main(int argc, char const *argv[])
{
	Solution solu;
	vector<int > arr={3,0,6,1,5};
	cout<<solu.hIndex(arr)<<endl;
	return 0;
}
