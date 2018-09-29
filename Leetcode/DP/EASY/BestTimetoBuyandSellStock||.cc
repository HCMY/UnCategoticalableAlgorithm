
/**
122.
Best Time to Buy and Sell Stock II

i.e. [7,1,5,3,6,4] 属于动态规划算法，但状态转移方程并不是很明显
根据题意：每次只能持有一支股票，不能连续买，之后再卖出。
这里计算能获得的最大利润：只要第二天的股票价格比前一天的高，就卖出去
累加利润即可
*/



class Solution {
public:
    int maxProfit(vector<int>& prices) {
    	if(prices.empty())
    		return 0;

		int total_profit = 0;
		for(int idx=0; idx<prices.size()-1; idx++){
			if(prices[idx]<prices[idx+1])
				total_profit += (prices[idx+1]-prices[idx]);
		}

		return total_profit;        
    }
};





int main(int argc, char const *argv[])
{
	Solution solu;
	int arr[] = {7,1,5,3,6,4};

	std::vector<int> v;
	v.insert(v.begin(), arr, arr+6);
	cout<<solu.maxProfit(v)<<endl;
	return 0;
}
