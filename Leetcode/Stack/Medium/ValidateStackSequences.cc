#include <iostream>
#include <vector>
#include <stack>

using namespace std;


class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
  		stack<int> my_stack;

  		for(auto item:pushed){
  			my_stack.push(item);
  			while(!my_stack.empty() && popped[0]==my_stack.top()){
  				my_stack.pop();
  				popped.erase(popped.begin());
  			}
  		}

  		return my_stack.empty();
    }
};



int main(int argc, char const *argv[])
{
	Solution solu;
	vector<int> pushed = {1,2,3,4,5};
	vector<int> popped = {4,3,5,1,2};

	cout<<solu.validateStackSequences(pushed,popped)<<endl;
	return 0;
}
